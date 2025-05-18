/**
 * @file Person.c
 * @description Kişi nesnelerini oluşturan ve yöneten fonksiyonların kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "Person.h"

//yeni bir kişi nesnesi oluşturur
Person newPerson(const char* name, int age, float remainingLife, const char* spaceship) {
    Person this = (Person)malloc(sizeof(struct PERSON));
    if (!this) return NULL;
    
    strcpy(this->name, name);
    this->age = age;
    this->remaining_life = remainingLife;
    strcpy(this->spaceship, spaceship);
    this->is_alive = 1;
    
    this->update = &updatePerson;
    this->getAgingFactor = &getPersonAgingFactor;
    this->delete = &deletePerson;
    
    return this;
}

//kişiyi verilen yaşlanma faktörüne göre günceller
void updatePerson(const Person this, float agingFactor) {
    if (this->is_alive) {
        this->remaining_life -= agingFactor;
        if (this->remaining_life <= 0) {
            this->is_alive = 0;
        }
    }
}

//kişinin bulunduğu konuma göre yaşlanma faktörünü hesaplar
float getPersonAgingFactor(const Person this, Spaceship* ships, int shipCount, Planet* planets, int planetCount) {
    for (int i = 0; i < shipCount; i++) {
        if (strcmp(this->spaceship, ships[i]->name) == 0) {
            if (ships[i]->status == IN_TRANSIT) {
                return 1.0; //uzayda yaşlanma faktörü
            } else {
                //gezegendeki yaşlanma faktörü
                char planet_name[10];
                if (ships[i]->status == ON_DEPARTURE) {
                    strcpy(planet_name, ships[i]->departure_planet);
                } else {
                    strcpy(planet_name, ships[i]->arrival_planet);
                }
                for (int j = 0; j < planetCount; j++) {
                    if (strcmp(planet_name, planets[j]->name) == 0) {
                        return planets[j]->getAgingFactor(planets[j]);
                    }
                }
            }
            break;
        }
    }
    return 1.0; //varsayılan değer
}

//kişi nesnesini bellekten temizler
void deletePerson(const Person this) {
    if (this) free(this);
}