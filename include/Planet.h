/**
 * @file Planet.h
 * @description Gezegenlerin temel sınıfını tanımlayan başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef PLANET_H
#define PLANET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ROCKY = 0,
    GAS_GIANT = 1,
    ICE_GIANT = 2,
    DWARF = 3
} PlanetType;

typedef enum {
    ON_DEPARTURE,
    IN_TRANSIT,
    ON_ARRIVAL,
    DESTROYED
} ShipStatus;

//tarih için yapı - gezegene özel tarih hesaplamaları için kullanılır
typedef struct DATE* Date;
struct DATE {
    int day;
    int month;
    int year;
    
    int (*isLeapYear)(const Date);
    int (*daysInMonth)(const Date);
    void (*addDays)(Date, int);
    int (*compareTo)(const Date, const Date);
    char* (*toString)(const Date);
    void (*parse)(Date, const char*);
    void (*delete)(const Date);
};

//tarih için bildirimler
Date newDate(int day, int month, int year);
int isLeapYear(const Date this);
int daysInMonth(const Date this);
void addDays(Date this, int days);
int compareTo(const Date this, const Date other);
char* dateToString(const Date this);
void parseDate(Date this, const char* dateStr);
void deleteDate(const Date this);

//gezegen soyut temel sınıfı
typedef struct PLANET* Planet;
struct PLANET {
    char name[10];
    PlanetType type;
    int hours_per_day;
    Date date;
    
    float (*getAgingFactor)(const Planet);
    void (*getLocalTime)(const Planet, int, Date, int*);
    void (*delete)(const Planet);
};

//planet temel metodları için bildirimler
Planet newPlanet(const char* name, PlanetType type, int hours_per_day, Date date);
float getAgingFactor(const Planet this);
void getLocalTime(const Planet this, int universalTime, Date localDate, int* localHour);
void deletePlanet(const Planet this);

#endif