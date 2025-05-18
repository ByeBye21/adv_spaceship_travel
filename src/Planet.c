/**
 * @file Planet.c
 * @description Gezegenlerin yerel zamanını hesaplayan fonksiyonun kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "Planet.h"

//tarih yapısı metodlarının uygulamaları
Date newDate(int day, int month, int year) {
    Date this = (Date)malloc(sizeof(struct DATE));
    if (!this) return NULL;
    
    this->day = day;
    this->month = month;
    this->year = year;
    
    this->isLeapYear = &isLeapYear;
    this->daysInMonth = &daysInMonth;
    this->addDays = &addDays;
    this->compareTo = &compareTo;
    this->toString = &dateToString;
    this->parse = &parseDate;
    this->delete = &deleteDate;
    
    return this;
}

int isLeapYear(const Date this) {
    return (this->year % 4 == 0 && this->year % 100 != 0) || (this->year % 400 == 0);
}

int daysInMonth(const Date this) {
    static int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (this->month == 2 && isLeapYear(this))
        return 29;
    return days[this->month];
}

void addDays(Date this, int days) {
    while (days > 0) {
        int days_this_month = this->daysInMonth(this);
        if (this->day + days <= days_this_month) {
            this->day += days;
            days = 0;
        } else {
            days -= (days_this_month - this->day + 1);
            this->day = 1;
            this->month++;
            if (this->month > 12) {
                this->month = 1;
                this->year++;
            }
        }
    }
}

int compareTo(const Date this, const Date other) {
    if (this->year != other->year)
        return this->year - other->year;
    if (this->month != other->month)
        return this->month - other->month;
    return this->day - other->day;
}

char* dateToString(const Date this) {
    char* str = (char*)malloc(11 * sizeof(char));
    if (!str) return NULL;
    
    sprintf(str, "%02d.%02d.%04d", this->day, this->month, this->year);
    return str;
}

void parseDate(Date this, const char* dateStr) {
    sscanf(dateStr, "%d.%d.%d", &this->day, &this->month, &this->year);
}

void deleteDate(const Date this) {
    if (this) free(this);
}

//Gezegen temel metodlarının uygulamaları
//yeni bir gezegen nesnesi oluşturur
Planet newPlanet(const char* name, PlanetType type, int hours_per_day, Date date) {
    Planet this = (Planet)malloc(sizeof(struct PLANET));
    if (!this) return NULL;
    
    strcpy(this->name, name);
    this->type = type;
    this->hours_per_day = hours_per_day;
    this->date = date;
    
    this->getAgingFactor = &getAgingFactor;
    this->getLocalTime = &getLocalTime;
    this->delete = &deletePlanet;
    
    return this;
}

//gezegen tipine göre yaşlanma faktörünü döndürür
float getAgingFactor(const Planet this) {
    switch (this->type) {
        case ROCKY:
            return 1.0;
        case GAS_GIANT:
            return 0.1;
        case ICE_GIANT:
            return 0.5;
        case DWARF:
            return 0.01;
        default:
            return 1.0;
    }
}

//belirli bir evrensel zamanda gezegenin yerel zamanını hesaplar
void getLocalTime(const Planet this, int universalTime, Date localDate, int* localHour) {
    //başlangıç tarihini klonla
    Date baseDate = newDate(this->date->day, this->date->month, this->date->year);
    
    //toplam günleri ve kalan saatleri hesapla
    int totalHours = universalTime;
    int days = totalHours / this->hours_per_day;
    *localHour = totalHours % this->hours_per_day;
    
    //tarihe günleri ekle
    baseDate->addDays(baseDate, days);
    
    //değerleri çıkış tarihine kopyala
    localDate->day = baseDate->day;
    localDate->month = baseDate->month;
    localDate->year = baseDate->year;
    
    baseDate->delete(baseDate);
}

//gezegen nesnesini bellekten temizler
void deletePlanet(const Planet this) {
    if (this == NULL) return;
    
    //eğer date varsa, silmeden önce kontrol et
    if (this->date) {
        this->date->delete(this->date);
    }
    
    free(this);
}
