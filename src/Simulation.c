/**
 * @file Simulation.c
 * @description Simülasyonu çalıştıran ve yöneten fonksiyonların kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "Simulation.h"
#include <time.h>

//yeni bir simülasyon nesnesi oluşturur
Simulation newSimulation() {
    Simulation this = (Simulation)malloc(sizeof(struct SIMULATION));
    if (!this) return NULL;
    
    this->universal_time = 0;
    this->persons = readPersons("Kisiler.txt", &this->person_count);
    this->ships = readSpaceships("Araclar.txt", &this->ship_count);
    this->planets = readPlanets("Gezegenler.txt", &this->planet_count);
    
    for (int i = 0; i < this->ship_count; i++) {
        this->ships[i]->calculateArrivalDate(this->ships[i], this->planets, this->planet_count, this->universal_time);
    }
    
    this->update = &updateSimulation;
    this->display = &displaySimulation;
    this->shouldContinue = &shouldContinue;
    this->run = &runSimulation;
    this->getPlanetPopulation = &getPlanetPopulation;
    this->delete = &deleteSimulation;
    
    return this;
}

//belirli bir gezegendeki nüfusu hesaplar
int getPlanetPopulation(const Simulation this, const Planet planet) {
    int population = 0;
    
    for (int i = 0; i < this->person_count; i++) {
        if (!this->persons[i]->is_alive) continue;
        
        for (int j = 0; j < this->ship_count; j++) {
            if (strcmp(this->persons[i]->spaceship, this->ships[j]->name) == 0) {
                if ((this->ships[j]->status == ON_DEPARTURE && 
                     strcmp(this->ships[j]->departure_planet, planet->name) == 0) ||
                    (this->ships[j]->status == ON_ARRIVAL && 
                     strcmp(this->ships[j]->arrival_planet, planet->name) == 0)) {
                    population++;
                }
                break;
            }
        }
    }
    return population;
}

//simülasyonu bir adım ileri götürür
void updateSimulation(const Simulation this) {
    this->universal_time++;
    
    for (int i = 0; i < this->ship_count; i++) {
        this->ships[i]->update(this->ships[i], this->universal_time, this->planets, this->planet_count, this->persons, this->person_count);
    }
    
    for (int i = 0; i < this->person_count; i++) {
        float agingFactor = this->persons[i]->getAgingFactor(this->persons[i], this->ships, this->ship_count, this->planets, this->planet_count);
        this->persons[i]->update(this->persons[i], agingFactor);
    }
}

//simülasyonun mevcut durumunu ekrana yazdırır
void displaySimulation(const Simulation this) {
    system("cls");
    
    //gezegenler bölümü
    printf("GEZEGENLER:\n");
    printf("%-10s ", "");
    
    //gezegen isimleri
    for (int i = 0; i < this->planet_count; i++) {
        printf("--- %-7s ", this->planets[i]->name);
    }
    printf("\n");
    
    //gezegen tarihleri
    printf("%-10s ", "Tarih");
    for (int i = 0; i < this->planet_count; i++) {
        Date localDate = newDate(0, 0, 0);
        int localHour = 0;
        
        this->planets[i]->getLocalTime(this->planets[i], this->universal_time, localDate, &localHour);
        
        printf("%02d.%02d.%04d  ", localDate->day, localDate->month, localDate->year);
        localDate->delete(localDate);
    }
    printf("\n");
    
    //gezegen nüfusları
    printf("%-10s ", "Nufus");
    for (int i = 0; i < this->planet_count; i++) {
        int population = this->getPlanetPopulation(this, this->planets[i]);
        printf("%-12d", population);
    }
    printf("\n\n");
    
    //uzay Araçları bölümü
    printf("UZAY ARACLARI:\n");
    printf("%-10s %-10s %-7s %-7s %-20s %-20s\n",
           "Arac Adi", "Durum", "Cikis", "Varis", "Hedefe Kalan Saat", "Hedefe Varacagi Tarih");
    printf("---------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < this->ship_count; i++) {
        char* statusName = this->ships[i]->getStatusString(this->ships[i]);
        
        int remaining = this->ships[i]->getRemainingHours(this->ships[i], 
                                                        this->universal_time, 
                                                        this->planets, this->planet_count);
        char remainingStr[15];
        
        if (remaining == -1) {
            strcpy(remainingStr, "--");
        } else if (remaining == -2) {
            strcpy(remainingStr, "Bekliyor");
        } else {
            sprintf(remainingStr, "%d", remaining);
        }
        
        printf("%-10s %-10s %-7s %-7s %-20s %-20s\n",
               this->ships[i]->name,
               statusName,
               this->ships[i]->departure_planet,
               this->ships[i]->arrival_planet,
               remainingStr,
               this->ships[i]->arrival_date_str);
    }
    printf("\n");
    
    //nüfus istatistikleri
    int aliveCount = 0;
    for (int i = 0; i < this->person_count; i++) {
        if (this->persons[i]->is_alive) {
            aliveCount++;
        }
    }
}

//simülasyonun devam edip etmeyeceğini kontrol eder
int shouldContinue(const Simulation this) {
    for (int i = 0; i < this->ship_count; i++) {
        if (this->ships[i]->status != ON_ARRIVAL && this->ships[i]->status != DESTROYED) {
            return 1; //devam et
        }
    }
    return 0; //simülasyon tamamlandı
}

//simülasyonu çalıştırır
void runSimulation(const Simulation this) {
    while (this->shouldContinue(this)) {
        this->update(this);
        this->display(this);
    }
    
    //son durumu göster
    this->display(this);
    printf("\nSimulasyon tamamlandi.\n");
}

//Simülasyon nesnesini bellekten temizler
void deleteSimulation(const Simulation this) {
    if (this) {
        //Önce gemilerin ve insanların temizlenmesi için null kontrolleri ekle
        if (this->persons) {
            for (int i = 0; i < this->person_count; i++) {
                if (this->persons[i]) {
                    this->persons[i]->delete(this->persons[i]);
                    this->persons[i] = NULL; //silindikten sonra NULL olarak işaretle
                }
            }
            free(this->persons);
        }
        
        if (this->ships) {
            for (int i = 0; i < this->ship_count; i++) {
                if (this->ships[i]) {
                    //gemi silinmeden önce departure_date'i NULL olarak kontrol et
                    if (this->ships[i]->departure_date) {
                        this->ships[i]->departure_date->delete(this->ships[i]->departure_date);
                        this->ships[i]->departure_date = NULL;
                    }
                    this->ships[i]->delete(this->ships[i]);
                    this->ships[i] = NULL; //silindikten sonra NULL olarak işaretle
                }
            }
            free(this->ships);
        }
        
        if (this->planets) {
            for (int i = 0; i < this->planet_count; i++) {
                if (this->planets[i]) {
                    //gezegen silinmeden önce date'i NULL olarak kontrol et
                    if (this->planets[i]->date) {
                        this->planets[i]->date->delete(this->planets[i]->date);
                        this->planets[i]->date = NULL;
                    }
                    this->planets[i]->delete(this->planets[i]);
                    this->planets[i] = NULL; //silindikten sonra NULL olarak işaretle
                }
            }
            free(this->planets);
        }
        
        free(this);
    }
}