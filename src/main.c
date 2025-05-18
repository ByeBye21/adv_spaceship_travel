/**
 * @file main.c
 * @description Uzay simülasyonunu başlatan ve çalıştıran ana program dosyası.
 * @course 1.Öğretim A Grubu
 * @assignment 2.Ödev
 * @date 2025/05/18
 * @author Younes Rahebi | B221210588
 */

#include <stdio.h>
#include <stdlib.h>
#include "Simulation.h"

int main() {

    /* Simülasyonu oluştur ve çalıştır */
    Simulation simulation = newSimulation();
    if (simulation) {
        simulation->run(simulation);
        
        /* Kaynakları temizle */
        simulation->delete(simulation);
    } else {
        printf("Simulasyon olusturulamadi!\n");
    }
    
    return 0;
}
