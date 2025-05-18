/**
 * @file Spaceship.h
 * @description Uzay araçlarını temsil eden sınıfın başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Planet.h"

typedef struct PERSON* Person;
typedef struct SPACESHIP* Spaceship;

//uzay aracı sınıfı - gezegenlere gidip gelen araçları temsil eder
struct SPACESHIP {
    char name[10];
    char departure_planet[10];
    char arrival_planet[10];
    Date departure_date;
    int travel_time;
    ShipStatus status;
    int departure_time;
    int arrival_time;
    char arrival_date_str[20];
    
    void (*calculateArrivalDate)(const Spaceship, Planet*, int, int);
    void (*update)(const Spaceship, int, Planet*, int, Person*, int);
    int (*getRemainingHours)(const Spaceship, int, Planet*, int);
    char* (*getStatusString)(const Spaceship);
    void (*delete)(const Spaceship);
};

//Spaceship metodları için bildirimler
Spaceship newSpaceship(const char* name, const char* departurePlanet, const char* arrivalPlanet, Date departureDate, int travelTime);
void calculateArrivalDate(const Spaceship this, Planet* planets, int planetCount, int universalTime);
void updateSpaceship(const Spaceship this, int universalTime, Planet* planets, int planetCount, Person* persons, int personCount);
int getRemainingHours(const Spaceship this, int currentTime, Planet* planets, int planetCount);
char* getStatusString(const Spaceship this);
void deleteSpaceship(const Spaceship this);

#endif 