/**
 * @file Spaceship.c
 * @description Uzay araçlarının durumunu güncelleyen ve yöneten fonksiyonların kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "Spaceship.h"
#include "Person.h"

//yeni bir uzay aracı nesnesi oluşturur
Spaceship newSpaceship(const char* name, const char* departurePlanet, 
                      const char* arrivalPlanet, Date departureDate, int travelTime) {
    Spaceship this = (Spaceship)malloc(sizeof(struct SPACESHIP));
    if (!this) return NULL;
    
    strcpy(this->name, name);
    strcpy(this->departure_planet, departurePlanet);
    strcpy(this->arrival_planet, arrivalPlanet);
    this->departure_date = departureDate;
    this->travel_time = travelTime;
    this->status = ON_DEPARTURE;
    this->departure_time = -1;
    this->arrival_time = -1;
    strcpy(this->arrival_date_str, "--");
    
    this->calculateArrivalDate = &calculateArrivalDate;
    this->update = &updateSpaceship;
    this->getRemainingHours = &getRemainingHours;
    this->getStatusString = &getStatusString;
    this->delete = &deleteSpaceship;
    
    return this;
}

//varış tarihini hesaplar
void calculateArrivalDate(const Spaceship this, Planet* planets, int planetCount, int universalTime) {
    strcpy(this->arrival_date_str, "--");
    
    for (int i = 0; i < planetCount; i++) {
        if (strcmp(this->departure_planet, planets[i]->name) == 0) {
            Date currentDate = newDate(0, 0, 0);
            int currentHour = 0;
            
            planets[i]->getLocalTime(planets[i], universalTime, currentDate, &currentHour);
            
            int hoursUntilDeparture = 0;
            
            if (currentDate->compareTo(currentDate, this->departure_date) < 0 ||
                (currentDate->compareTo(currentDate, this->departure_date) == 0 && currentHour > 0)) {
                Date tempDate = newDate(currentDate->day, currentDate->month, currentDate->year);
                tempDate->addDays(tempDate, 1);
                hoursUntilDeparture = (planets[i]->hours_per_day - currentHour);
                tempDate->delete(tempDate);
            } else if (currentDate->compareTo(currentDate, this->departure_date) == 0 && currentHour == 0) {
                hoursUntilDeparture = 0;
            } else {
                Date iterDate = newDate(currentDate->day, currentDate->month, currentDate->year);
                int days = 0;
                while (iterDate->compareTo(iterDate, this->departure_date) < 0) {
                    iterDate->addDays(iterDate, 1);
                    days++;
                }
                hoursUntilDeparture = (days * planets[i]->hours_per_day) - currentHour;
                iterDate->delete(iterDate);
            }
            
            int departureTime = universalTime + hoursUntilDeparture;
            int arrivalTime = departureTime + this->travel_time;
            
            for (int j = 0; j < planetCount; j++) {
                if (strcmp(this->arrival_planet, planets[j]->name) == 0) {
                    Date arrivalDate = newDate(0, 0, 0);
                    int arrivalHour = 0;
                    
                    planets[j]->getLocalTime(planets[j], arrivalTime, arrivalDate, &arrivalHour);
                    
                    sprintf(this->arrival_date_str, "%02d.%02d.%04d",
                            arrivalDate->day, arrivalDate->month, arrivalDate->year);
                    
                    arrivalDate->delete(arrivalDate);
                    break;
                }
            }
            
            currentDate->delete(currentDate);
            break;
        }
    }
}

//uzay aracının durumunu günceller
void updateSpaceship(const Spaceship this, int universalTime, Planet* planets, int planetCount, 
                    Person* persons, int personCount) {
    if (this->status == DESTROYED) {
        strcpy(this->arrival_date_str, "--");
        return;
    }
    
    int livingPersons = 0;
    for (int i = 0; i < personCount; i++) {
        if (persons[i]->is_alive && strcmp(persons[i]->spaceship, this->name) == 0) {
            livingPersons++;
        }
    }
    
    if (livingPersons == 0) {
        this->status = DESTROYED;
        strcpy(this->arrival_date_str, "--");
        return;
    }
    
    if (this->status == ON_DEPARTURE) {
        for (int i = 0; i < planetCount; i++) {
            if (strcmp(this->departure_planet, planets[i]->name) == 0) {
                Date localDate = newDate(0, 0, 0);
                int localHour = 0;
                
                planets[i]->getLocalTime(planets[i], universalTime, localDate, &localHour);
                
                if (localDate->compareTo(localDate, this->departure_date) >= 0 && localHour == 0) {
                    this->status = IN_TRANSIT;
                    this->departure_time = universalTime;
                    this->arrival_time = universalTime + this->travel_time;
                    
                    for (int j = 0; j < planetCount; j++) {
                        if (strcmp(this->arrival_planet, planets[j]->name) == 0) {
                            Date arrivalDate = newDate(0, 0, 0);
                            int arrivalHour = 0;
                            
                            planets[j]->getLocalTime(planets[j], this->arrival_time, arrivalDate, &arrivalHour);
                            
                            sprintf(this->arrival_date_str, "%02d.%02d.%04d",
                                    arrivalDate->day, arrivalDate->month, arrivalDate->year);
                            
                            arrivalDate->delete(arrivalDate);
                            break;
                        }
                    }
                }
                
                localDate->delete(localDate);
                break;
            }
        }
    }
    
    if (this->status == IN_TRANSIT && universalTime >= this->arrival_time) {
        this->status = ON_ARRIVAL;
    }
}

//hedefe kalan saati hesaplar
int getRemainingHours(const Spaceship this, int currentTime, Planet* planets, int planetCount) {
    if (this->status == DESTROYED) {
        return -1;
    }
    
    if (this->status == ON_DEPARTURE) {
        for (int i = 0; i < planetCount; i++) {
            if (strcmp(this->departure_planet, planets[i]->name) == 0) {
                Date currentDate = newDate(0, 0, 0);
                int currentHour = 0;
                
                planets[i]->getLocalTime(planets[i], currentTime, currentDate, &currentHour);
                
                int result = 0;
                
                if (currentDate->compareTo(currentDate, this->departure_date) < 0) {
                    result = (planets[i]->hours_per_day - currentHour) + this->travel_time;
                } else if (currentDate->compareTo(currentDate, this->departure_date) == 0) {
                    if (currentHour == 0) {
                        result = this->travel_time;
                    } else {
                        result = (planets[i]->hours_per_day - currentHour) + this->travel_time;
                    }
                } else {
                    Date tempDate = newDate(currentDate->day, currentDate->month, currentDate->year);
                    int days = 0;
                    while (tempDate->compareTo(tempDate, this->departure_date) < 0) {
                        tempDate->addDays(tempDate, 1);
                        days++;
                    }
                    result = (days * planets[i]->hours_per_day - currentHour) + this->travel_time;
                    tempDate->delete(tempDate);
                }
                
                currentDate->delete(currentDate);
                return result;
            }
        }
        return -2;
    }
    
    if (this->status == ON_ARRIVAL) {
        return 0;
    }
    
    return this->arrival_time - currentTime;
}

//uzay aracının durum metnini döndürür
char* getStatusString(const Spaceship this) {
    switch (this->status) {
        case ON_DEPARTURE: return "Bekliyor";
        case IN_TRANSIT: return "Yolda";
        case ON_ARRIVAL: return "Vardi";
        case DESTROYED: return "IMHA";
        default: return "Bilinmiyor";
    }
}
 
//uzay aracı nesnesini bellekten temizler
void deleteSpaceship(const Spaceship this) {
    if (this == NULL) return;
    
    //eğer departure_date varsa, silmeden önce kontrol et
    if (this->departure_date) {
        this->departure_date->delete(this->departure_date);
    }
    
    free(this);
}