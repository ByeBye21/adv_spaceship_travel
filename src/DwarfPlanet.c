/**
 * @file DwarfPlanet.c
 * @description Cüce gezegenleri oluşturan fonksiyonun kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "DwarfPlanet.h"

//cüce gezegen için yaşlanma faktörü hesaplama
float getDwarfPlanetAgingFactor(const DwarfPlanet this) {
    return 0.01; //cüce gezegen yaşlanma faktörü
}

//yeni bir cüce gezegen nesnesi oluşturur
DwarfPlanet newDwarfPlanet(const char* name, int hours_per_day, Date date) {
    DwarfPlanet this = (DwarfPlanet)malloc(sizeof(struct DWARF_PLANET));
    if (!this) return NULL;
    
    //planet süper sınıfını başlat
    this->super = (Planet)malloc(sizeof(struct PLANET));
    if (!this->super) {
        free(this);
        return NULL;
    }
    
    strcpy(this->super->name, name);
    this->super->type = DWARF;
    this->super->hours_per_day = hours_per_day;
    this->super->date = date;
    
    //metodları başlat
    this->super->getAgingFactor = (float (*)(const Planet))&getDwarfPlanetAgingFactor;
    this->super->getLocalTime = &getLocalTime;
    this->super->delete = (void (*)(const Planet))&deleteDwarfPlanet;
    
    return this;
}

//cüce gezegen nesnesini bellekten temizler
void deleteDwarfPlanet(const DwarfPlanet this) {
    if (this == NULL) return;
    deletePlanet(this->super);
    free(this);
} 