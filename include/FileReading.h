/**
 * @file FileReading.h
 * @description Dosyalardan veri okuyan fonksiyonların başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef FILE_READING_H
#define FILE_READING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Person.h"
#include "Spaceship.h"
#include "Planet.h"
#include "RockPlanet.h"
#include "GasGiantPlanet.h"
#include "IceGiantPlanet.h"
#include "DwarfPlanet.h"

//dosya okuma fonksiyonları
Person* readPersons(const char* filename, int* count);
Spaceship* readSpaceships(const char* filename, int* count);
Planet* readPlanets(const char* filename, int* count);

#endif