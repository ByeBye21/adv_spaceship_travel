/**
 * @file IceGiantPlanet.c
 * @description Buz devi gezegenlerini oluşturan fonksiyonun kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "IceGiantPlanet.h"

//buz devi gezegeni için yaşlanma faktörü hesaplama
float getIceGiantPlanetAgingFactor(const IceGiantPlanet this) {
    return 0.5; //buz devi gezegeni yaşlanma faktörü
}

//yeni bir buz devi gezegeni nesnesi oluşturur
IceGiantPlanet newIceGiantPlanet(const char* name, int hours_per_day, Date date) {
    IceGiantPlanet this = (IceGiantPlanet)malloc(sizeof(struct ICE_GIANT_PLANET));
    if (!this) return NULL;
    
    //planet süper sınıfını başlat
    this->super = (Planet)malloc(sizeof(struct PLANET));
    if (!this->super) {
        free(this);
        return NULL;
    }
    
    strcpy(this->super->name, name);
    this->super->type = ICE_GIANT;
    this->super->hours_per_day = hours_per_day;
    this->super->date = date;
    
    // Metodları başlat
    this->super->getAgingFactor = (float (*)(const Planet))&getIceGiantPlanetAgingFactor;
    this->super->getLocalTime = &getLocalTime;
    this->super->delete = (void (*)(const Planet))&deleteIceGiantPlanet;
    
    return this;
}

//buz devi gezegeni nesnesini bellekten temizler
void deleteIceGiantPlanet(const IceGiantPlanet this) {
    if (this == NULL) return;
    deletePlanet(this->super);
    free(this);
}