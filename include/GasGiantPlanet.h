/**
 * @file GasGiantPlanet.h
 * @description Gaz devi gezegenlerini oluşturan sınıfın başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef GAS_GIANT_PLANET_H
#define GAS_GIANT_PLANET_H

#include "Planet.h"

//gaz devi gezegeninin alt sınıfı
typedef struct GAS_GIANT_PLANET* GasGiantPlanet;
struct GAS_GIANT_PLANET {
    Planet super;
    //gaz devi gezegeni için ek özellikler eklenebilir
};

//GasGiantPlanet metodları için bildirimler
GasGiantPlanet newGasGiantPlanet(const char* name, int hours_per_day, Date date);
float getGasGiantPlanetAgingFactor(const GasGiantPlanet this);
void deleteGasGiantPlanet(const GasGiantPlanet this);

#endif