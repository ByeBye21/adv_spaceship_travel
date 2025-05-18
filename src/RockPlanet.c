/**
 * @file RockPlanet.c
 * @description Kaya gezegenlerini oluşturan fonksiyonun kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "RockPlanet.h"

//Kaya gezegeni için yaşlanma faktörü hesaplama
float getRockPlanetAgingFactor(const RockPlanet this) {
    return 1.0; //kaya gezegeni standart yaşlanma faktörü
}

//yeni bir kaya gezegeni nesnesi oluşturur
RockPlanet newRockPlanet(const char* name, int hours_per_day, Date date) {
    RockPlanet this = (RockPlanet)malloc(sizeof(struct ROCK_PLANET));
    if (!this) return NULL;
    
    //planet süper sınıfını başlat
    this->super = (Planet)malloc(sizeof(struct PLANET));
    if (!this->super) {
        free(this);
        return NULL;
    }
    
    strcpy(this->super->name, name);
    this->super->type = ROCKY;
    this->super->hours_per_day = hours_per_day;
    this->super->date = date;
    
    // Metodları başlat
    this->super->getAgingFactor = (float (*)(const Planet))&getRockPlanetAgingFactor;
    this->super->getLocalTime = &getLocalTime;
    this->super->delete = (void (*)(const Planet))&deleteRockPlanet;
    
    return this;
}

//kaya gezegeni nesnesini bellekten temizler
void deleteRockPlanet(const RockPlanet this) {
    if (this == NULL) return;
    deletePlanet(this->super);
    free(this);
}