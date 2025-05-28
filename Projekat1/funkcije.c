#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void ucistiBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void dodajDogadaj() {
    char period[MAX_PERIOD];
    printf("Unesite naziv povijesnog perioda: ");
    fgets(period, sizeof(period), stdin);
    period[strcspn(period, "\n")] = 0;

    char imeDatoteke[MAX_PERIOD + 10];
    snprintf(imeDatoteke, sizeof(imeDatoteke), "%s.bin", period);

    FILE* f = fopen(imeDatoteke, "ab+");
    if (!f) {
        perror("Ne mogu otvoriti datoteku");
        return;
    }

    Dogadaj d;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    d.id = size / sizeof(Dogadaj) + 1;

    printf("Naziv dogadaja: ");
    fgets(d.naziv, sizeof(d.naziv), stdin);
    d.naziv[strcspn(d.naziv, "\n")] = 0;

    printf("Datum: ");
    fgets(d.datum, sizeof(d.datum), stdin);
    d.datum[strcspn(d.datum, "\n")] = 0;

    printf("Lokacija: ");
    fgets(d.lokacija, sizeof(d.lokacija), stdin);
    d.lokacija[strcspn(d.lokacija, "\n")] = 0;

    printf("Opis: ");
    fgets(d.opis, sizeof(d.opis), stdin);
    d.opis[strcspn(d.opis, "\n")] = 0;

    fwrite(&d, sizeof(Dogadaj), 1, f);
    fclose(f);
    printf("Dogadaj uspjesno dodan u '%s'.\n", period);
}

void ispisiDogadaje() {
    char period[MAX_PERIOD];
    printf("Unesite naziv povijesnog perioda za ispis: ");
    fgets(period, sizeof(period), stdin);
    period[strcspn(period, "\n")] = 0;

    char imeDatoteke[MAX_PERIOD + 10];
    snprintf(imeDatoteke, sizeof(imeDatoteke), "%s.bin", period);

    FILE* f = fopen(imeDatoteke, "rb");
    if (!f) {
        printf("Nema dogadaja za period '%s'.\n", period);
        return;
    }

    Dogadaj d;
    printf("\nDogadaji u periodu '%s':\n", period);
    while (fread(&d, sizeof(Dogadaj), 1, f)) {
        printf("\nID: %d\nNaziv: %s\nDatum: %s\nLokacija: %s\nOpis: %s\n",
            d.id, d.naziv, d.datum, d.lokacija, d.opis);
    }

    fclose(f);
}

void azurirajDogadaj() {
    char period[MAX_PERIOD];
    printf("Unesite naziv povijesnog perioda: ");
    fgets(period, sizeof(period), stdin);
    period[strcspn(period, "\n")] = 0;

    char imeDatoteke[MAX_PERIOD + 10];
    snprintf(imeDatoteke, sizeof(imeDatoteke), "%s.bin", period);

    FILE* f = fopen(imeDatoteke, "rb+");
    if (!f) {
        printf("Nema dogadaja za period '%s'.\n", period);
        return;
    }

    int trazeniID;
    printf("Unesite ID dogadaja za azuriranje: ");
    scanf_s("%d", &trazeniID);
    ucistiBuffer();

    Dogadaj d;
    int found = 0;

    while (fread(&d, sizeof(Dogadaj), 1, f)) {
        if (d.id == trazeniID) {
            printf("Novi naziv: ");
            fgets(d.naziv, sizeof(d.naziv), stdin);
            d.naziv[strcspn(d.naziv, "\n")] = 0;

            printf("Novi datum: ");
            fgets(d.datum, sizeof(d.datum), stdin);
            d.datum[strcspn(d.datum, "\n")] = 0;

            printf("Nova lokacija: ");
            fgets(d.lokacija, sizeof(d.lokacija), stdin);
            d.lokacija[strcspn(d.lokacija, "\n")] = 0;

            printf("Novi opis: ");
            fgets(d.opis, sizeof(d.opis), stdin);
            d.opis[strcspn(d.opis, "\n")] = 0;

            fseek(f, -(long)sizeof(Dogadaj), SEEK_CUR);
            fwrite(&d, sizeof(Dogadaj), 1, f);
            found = 1;
            printf("Dogadaj azuriran.\n");
            break;
        }
    }

    if (!found)
        printf("Dogadaj s ID %d nije pronaden.\n", trazeniID);

    fclose(f);
}

void obrisiDogadaj() {
    char period[MAX_PERIOD];
    printf("Unesite naziv povijesnog perioda: ");
    fgets(period, sizeof(period), stdin);
    period[strcspn(period, "\n")] = 0;

    char imeDatoteke[MAX_PERIOD + 10];
    snprintf(imeDatoteke, sizeof(imeDatoteke), "%s.bin", period);

    FILE* f = fopen(imeDatoteke, "rb");
    if (!f) {
        printf("Period '%s' nema unesenih dogadaja.\n", period);
        return;
    }

    FILE* temp = fopen("temp.bin", "wb");
    if (!temp) {
        perror("Nije moguce otvoriti datoteku.");
        fclose(f);
        return;
    }

    int trazeniID;
    printf("Unesite ID dogadaja za brisanje: ");
    scanf_s("%d", &trazeniID);
    ucistiBuffer();

    Dogadaj d;
    int found = 0;
    int noviID = 1;

    while (fread(&d, sizeof(Dogadaj), 1, f)) {
        if (d.id != trazeniID) {
            d.id = noviID++;
            fwrite(&d, sizeof(Dogadaj), 1, temp);
        }
        else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove(imeDatoteke);
    rename("temp.bin", imeDatoteke);

    if (found)
        printf("Dogadaj obrisan i ID-evi azurirani.\n");
    else
        printf("Dogadaj s ID %d nije pronaden.\n", trazeniID);
}