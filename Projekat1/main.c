#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "header.h"

int main() {
    int izbor;

    do {
        printf("\n=== IZBORNIK ===\n"); //implementacija izbornika//
        printf("%d. Dodaj dogadaj\n", DODAJ_DOGADJAJ);
        printf("%d. Ispisi dogadaje\n", ISPISI_DOGADJAJE);
        printf("%d. Azuriraj dogadaj\n", AZURIRAJ_DOGADJAJ);
        printf("%d. Obrisi dogadaj\n", OBRISI_DOGADJAJ);
        printf("%d. Pretrazi dogadaj\n", PRETRAZI_DOGADJAJ);
        printf("%d. Izlaz\n", IZLAZ);
        printf("Odabir: ");
        scanf("%d", &izbor);
        getchar();

        switch (izbor) {
        case DODAJ_DOGADJAJ: dodajDogadaj(); break;
        case ISPISI_DOGADJAJE: ispisiDogadaje(); break;
        case AZURIRAJ_DOGADJAJ: azurirajDogadaj(); break;
        case OBRISI_DOGADJAJ: obrisiDogadaj(); break;
        case PRETRAZI_DOGADJAJ: pretraziDogadaj(); break;
        case IZLAZ: printf("Izlaz iz programa.\n"); break;
        default: printf("Pogresan unos.\n"); break;
        }
    } while (izbor != IZLAZ);

    return 0;
}
