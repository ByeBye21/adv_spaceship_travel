/**
 * @file FileReading.c
 * @description Dosyalardan veri okuyan fonksiyonların kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "FileReading.h"

//kişiler dosyasını okuyup kişi nesneleri oluşturur
Person* readPersons(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Dosya acilamadi: %s\n", filename);
        exit(1);
    }
    
    int lineCount = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), file)) {
        lineCount++;
    }
    
    Person* persons = (Person*)malloc(lineCount * sizeof(Person));
    if (!persons) {
        printf("Bellek hatasi\n");
        exit(1);
    }
    
    rewind(file);
    *count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        char name[50], spaceship[10];
        int age;
        float remainingLife;
        
        char* token = strtok(buffer, "#");
        strcpy(name, token);
        
        token = strtok(NULL, "#");
        age = atoi(token);
        
        token = strtok(NULL, "#");
        remainingLife = atof(token);
        
        token = strtok(NULL, "#\n");
        strcpy(spaceship, token);
        
        persons[*count] = newPerson(name, age, remainingLife, spaceship);
        (*count)++;
    }
    
    fclose(file);
    return persons;
}

//uzay araçları dosyasını okuyup uzay aracı nesneleri oluşturur
Spaceship* readSpaceships(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Dosya acilamadi: %s\n", filename);
        exit(1);
    }
    
    int lineCount = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), file)) {
        lineCount++;
    }
    
    Spaceship* ships = (Spaceship*)malloc(lineCount * sizeof(Spaceship));
    if (!ships) {
        printf("Bellek hatasi\n");
        exit(1);
    }
    
    rewind(file);
    *count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        char name[10], departurePlanet[10], arrivalPlanet[10], dateStr[11];
        int travelTime;
        
        char* token = strtok(buffer, "#");
        strcpy(name, token);
        
        token = strtok(NULL, "#");
        strcpy(departurePlanet, token);
        
        token = strtok(NULL, "#");
        strcpy(arrivalPlanet, token);
        
        token = strtok(NULL, "#");
        strcpy(dateStr, token);
        
        Date departureDate = newDate(0, 0, 0);
        departureDate->parse(departureDate, dateStr);
        
        token = strtok(NULL, "#\n");
        travelTime = atoi(token);
        
        ships[*count] = newSpaceship(name, departurePlanet, arrivalPlanet, departureDate, travelTime);
        (*count)++;
    }
    
    fclose(file);
    return ships;
}

//sezegenler dosyasını okuyup gezegen nesneleri oluşturur
Planet* readPlanets(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Dosya acilamadi: %s\n", filename);
        exit(1);
    }
    
    int lineCount = 0;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), file)) {
        lineCount++;
    }
    
    Planet* planets = (Planet*)malloc(lineCount * sizeof(Planet));
    if (!planets) {
        printf("Bellek hatasi\n");
        exit(1);
    }
    
    rewind(file);
    *count = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        char name[10], dateStr[11];
        int type, hoursPerDay;
        
        char* token = strtok(buffer, "#");
        strcpy(name, token);
        
        token = strtok(NULL, "#");
        type = atoi(token);
        
        token = strtok(NULL, "#");
        hoursPerDay = atoi(token);
        
        token = strtok(NULL, "#\n");
        strcpy(dateStr, token);
        
        Date date = newDate(0, 0, 0);
        date->parse(date, dateStr);
        
        //doğrudan Planet nesnesi oluştur, alt türlere dönüştürme yapmadan
        planets[*count] = newPlanet(name, (PlanetType)type, hoursPerDay, date);
        (*count)++;
    }
    
    fclose(file);
    return planets;
}
