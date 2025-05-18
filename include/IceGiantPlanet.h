/**
 * @file IceGiantPlanet.h
 * @description Buz devi gezegenlerini oluşturan sınıfın başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef ICE_GIANT_PLANET_H
#define ICE_GIANT_PLANET_H

#include "Planet.h"

//buz devi gezegeninin alt sınıfı
typedef struct ICE_GIANT_PLANET* IceGiantPlanet;
struct ICE_GIANT_PLANET {
    Planet super;
    //buz devi gezegeni için ek özellikler eklenebilir
};

//IceGiantPlanet metodları için bildirimler
IceGiantPlanet newIceGiantPlanet(const char* name, int hours_per_day, Date date);
float getIceGiantPlanetAgingFactor(const IceGiantPlanet this);
void deleteIceGiantPlanet(const IceGiantPlanet this);

#endif 