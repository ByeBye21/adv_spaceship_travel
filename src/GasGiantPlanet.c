/**
 * @file GasGiantPlanet.c
 * @description Gaz devi gezegenlerini oluşturan fonksiyonun kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "GasGiantPlanet.h"

//gaz devi gezegeni için yaşlanma faktörü hesaplama
float getGasGiantPlanetAgingFactor(const GasGiantPlanet this) {
    return 0.1; //gaz devi gezegeni yaşlanma faktörü
}

//yeni bir gaz devi gezegeni nesnesi oluşturur
GasGiantPlanet newGasGiantPlanet(const char* name, int hours_per_day, Date date) {
    GasGiantPlanet this = (GasGiantPlanet)malloc(sizeof(struct GAS_GIANT_PLANET));
    if (!this) return NULL;
    
    //planet süper sınıfını başlat
    this->super = (Planet)malloc(sizeof(struct PLANET));
    if (!this->super) {
        free(this);
        return NULL;
    }
    
    strcpy(this->super->name, name);
    this->super->type = GAS_GIANT;
    this->super->hours_per_day = hours_per_day;
    this->super->date = date;
    
    //metodları başlat
    this->super->getAgingFactor = (float (*)(const Planet))&getGasGiantPlanetAgingFactor;
    this->super->getLocalTime = &getLocalTime;
    this->super->delete = (void (*)(const Planet))&deleteGasGiantPlanet;
    
    return this;
}

//gaz devi gezegeni nesnesini bellekten temizler
void deleteGasGiantPlanet(const GasGiantPlanet this) {
    if (this == NULL) return;
    deletePlanet(this->super);
    free(this);
} 