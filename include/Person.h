/**
 * @file Person.h
 * @description Kişileri temsil eden sınıfın başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Spaceship.h"
#include "Planet.h"

typedef struct PERSON* Person;

//kişi sınıfı - bir uzay aracındaki kişileri temsil eder
struct PERSON {
    char name[50];
    int age;
    float remaining_life;
    char spaceship[10];
    int is_alive;
    
    void (*update)(const Person, float);
    float (*getAgingFactor)(const Person, Spaceship*, int, Planet*, int);
    void (*delete)(const Person);
};

//person metodları için bildirimler
Person newPerson(const char* name, int age, float remainingLife, const char* spaceship);
void updatePerson(const Person this, float agingFactor);
float getPersonAgingFactor(const Person this, Spaceship* ships, int shipCount, Planet* planets, int planetCount);
void deletePerson(const Person this);

#endif