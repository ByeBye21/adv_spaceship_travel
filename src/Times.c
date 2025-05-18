/**
 * @file Times.c
 * @description Mevcut zamanı formatlı şekilde döndüren fonksiyonun kaynak dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include "Times.h"

//şu anki tarihi ve zamanı formatlanmış şekilde döndürür
char* getTime() {
    char* buff = malloc(sizeof(char) * 100);
    time_t now = time(NULL);
    strftime(buff, 100, "%Y-%m-%d %H:%M", localtime(&now));
    return buff;
}