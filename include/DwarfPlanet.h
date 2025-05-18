/**
 * @file DwarfPlanet.h
 * @description Cüce gezegenleri oluşturan sınıfın başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef DWARF_PLANET_H
#define DWARF_PLANET_H

#include "Planet.h"

//cüce gezegenin alt sınıfı
typedef struct DWARF_PLANET* DwarfPlanet;
struct DWARF_PLANET {
    Planet super;
    //cüce gezegen için ek özellikler eklenebilir
};

//DwarfPlanet metodları için bildirimler
DwarfPlanet newDwarfPlanet(const char* name, int hours_per_day, Date date); 
float getDwarfPlanetAgingFactor(const DwarfPlanet this);
void deleteDwarfPlanet(const DwarfPlanet this);

#endif 