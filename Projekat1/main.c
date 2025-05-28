#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "header.h"

void dodajDogadaj();
void ispisiDogadaje();
void azurirajDogadaj();
void obrisiDogadaj();

typedef enum {
    IZLAZ = 0,
    DODAJ_DOGADJAJ = 1,
    ISPISI_DOGADJAJE = 2,
    AZURIRAJ_DOGADJAJ = 3,
    OBRISI_DOGADJAJ = 4
} IzbornikOpcija;

int main() {
    int izbor;

    do {
        printf("\n=== IZBORNIK ===\n");
        printf("%d. Dodaj dogadaj\n", DODAJ_DOGADJAJ);
        printf("%d. Ispisi dogadaje\n", ISPISI_DOGADJAJE);
        printf("%d. Azuriraj dogadaj\n", AZURIRAJ_DOGADJAJ);
        printf("%d. Obrisi dogadaj\n", OBRISI_DOGADJAJ);
        printf("%d. Izlaz\n", IZLAZ);
        printf("Odabir: ");
        scanf("%d", &izbor);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (izbor) {
        case DODAJ_DOGADJAJ:
            dodajDogadaj();
            break;
        case ISPISI_DOGADJAJE:
            ispisiDogadaje();
            break;
        case AZURIRAJ_DOGADJAJ:
            azurirajDogadaj();
            break;
        case OBRISI_DOGADJAJ:
            obrisiDogadaj();
            break;
        case IZLAZ:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Pokusajte ponovno.\n");
            break;
        }
    } while (izbor != IZLAZ);

    return 0;
}
