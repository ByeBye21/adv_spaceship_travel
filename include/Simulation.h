/**
 * @file Simulation.h
 * @description Simülasyon yapısını tanımlayan başlık dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include "Person.h"
#include "Spaceship.h"
#include "Planet.h"
#include "RockPlanet.h"
#include "GasGiantPlanet.h"
#include "IceGiantPlanet.h"
#include "DwarfPlanet.h"
#include "FileReading.h"

typedef struct SIMULATION* Simulation;

//simülasyon sınıfı - tüm sistemi yönetir
struct SIMULATION {
    int universal_time;
    Person* persons;
    int person_count;
    Spaceship* ships;
    int ship_count;
    Planet* planets;
    int planet_count;
    
    void (*update)(const Simulation);
    void (*display)(const Simulation);
    int (*shouldContinue)(const Simulation);
    void (*run)(const Simulation);
    int (*getPlanetPopulation)(const Simulation, const Planet);
    void (*delete)(const Simulation);
};

//Simulation metodları için bildirimler
Simulation newSimulation();
void updateSimulation(const Simulation this);
void displaySimulation(const Simulation this);
int shouldContinue(const Simulation this);
void runSimulation(const Simulation this);
int getPlanetPopulation(const Simulation this, const Planet planet);
void deleteSimulation(const Simulation this);

#endif