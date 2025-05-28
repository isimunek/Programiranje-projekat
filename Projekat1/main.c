#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "header.h"

int main() {
    int izbor;

    do {
        printf("\n=== IZBORNIK ===\n");
        printf("1. Dodaj dogadaj\n");
        printf("2. Ispisi dogadaje\n");
        printf("3. Azuriraj dogadaj\n");
        printf("4. Obrisi dogadaj\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        scanf_s("%d", &izbor);
        getchar();

        switch (izbor) {
        case 1:
            dodajDogadaj();
            break;
        case 2:
            ispisiDogadaje();
            break;
        case 3:
            azurirajDogadaj();
            break;
        case 4:
            obrisiDogadaj();
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Pokusajte ponovno.\n");
        }
    } while (izbor != 0);

    return 0;
}