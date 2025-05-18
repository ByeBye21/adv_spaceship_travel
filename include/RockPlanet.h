/**
 * @file RockPlanet.h
 * @description Kaya gezegenlerini oluşturan sınıfın başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef ROCK_PLANET_H
#define ROCK_PLANET_H

#include "Planet.h"

//kaya gezegeninin alt sınıfı
typedef struct ROCK_PLANET* RockPlanet;
struct ROCK_PLANET {
    Planet super;
};

//RockPlanet metodları için bildirimler
RockPlanet newRockPlanet(const char* name, int hours_per_day, Date date);
float getRockPlanetAgingFactor(const RockPlanet this);
void deleteRockPlanet(const RockPlanet this);

#endif