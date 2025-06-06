#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static void ocistiBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int usporediDogadajePoNazivu(const void* a, const void* b) {
    return strcmp(((Dogadaj*)a)->naziv, ((Dogadaj*)b)->naziv);
}

static int usporediDogadajPoIDu(const void* key, const void* elem) {
    int id = *(int*)key;
    return id - ((Dogadaj*)elem)->id;
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
        perror("Greska prilikom otvaranja datoteke");
        return;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    Dogadaj* noviDogadaj = (Dogadaj*)malloc(sizeof(Dogadaj));
    if (!noviDogadaj) {
        perror("Greska pri alokaciji memorije");
        fclose(f);
        return;
    }

    noviDogadaj->id = size / sizeof(Dogadaj) + 1;

    printf("Naziv dogadaja: ");
    fgets(noviDogadaj->naziv, sizeof(noviDogadaj->naziv), stdin);
    noviDogadaj->naziv[strcspn(noviDogadaj->naziv, "\n")] = 0;

    printf("Datum: ");
    fgets(noviDogadaj->datum, sizeof(noviDogadaj->datum), stdin);
    noviDogadaj->datum[strcspn(noviDogadaj->datum, "\n")] = 0;

    printf("Lokacija: ");
    fgets(noviDogadaj->lokacija, sizeof(noviDogadaj->lokacija), stdin);
    noviDogadaj->lokacija[strcspn(noviDogadaj->lokacija, "\n")] = 0;

    printf("Opis: ");
    fgets(noviDogadaj->opis, sizeof(noviDogadaj->opis), stdin);
    noviDogadaj->opis[strcspn(noviDogadaj->opis, "\n")] = 0;

    fwrite(noviDogadaj, sizeof(Dogadaj), 1, f);
    free(noviDogadaj);
    fclose(f);
    printf("Dogadaj dodan u '%s'.\n", period);
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
        perror("Greska pri otvaranju datoteke");
        return;
    }

    fseek(f, 0, SEEK_END);
    long velicina = ftell(f);
    rewind(f);

    int broj = velicina / sizeof(Dogadaj);
    if (broj == 0) {
        printf("Nema dogadaja u datoteci.\n");
        fclose(f);
        return;
    }

    Dogadaj* niz = (Dogadaj*)malloc(broj * sizeof(Dogadaj));
    if (!niz) {
        perror("Greska pri alokaciji memorije");
        fclose(f);
        return;
    }

    fread(niz, sizeof(Dogadaj), broj, f);
    fclose(f);

    for (int i = 0; i < broj; i++) {
        printf("\nID: %d\nNaziv: %s\nDatum: %s\nLokacija: %s\nOpis: %s\n",
            niz[i].id, niz[i].naziv, niz[i].datum, niz[i].lokacija, niz[i].opis);
    }

    free(niz);
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
        perror("Greska pri otvaranju datoteke");
        return;
    }

    int trazeniID;
    printf("Unesite ID za azuriranje: ");
    scanf("%d", &trazeniID);
    ocistiBuffer();

    Dogadaj d;
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
            printf("Azurirano.\n");
            fclose(f);
            return;
        }
    }

    printf("Dogadaj nije pronaden.\n");
    fclose(f);
}

void obrisiDogadaj() {
    char period[MAX_PERIOD];
    printf("Unesite naziv perioda: ");
    fgets(period, sizeof(period), stdin);
    period[strcspn(period, "\n")] = 0;

    char imeDatoteke[MAX_PERIOD + 10];
    snprintf(imeDatoteke, sizeof(imeDatoteke), "%s.bin", period);

    FILE* f = fopen(imeDatoteke, "rb");
    if (!f) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    FILE* temp = fopen("temp.bin", "wb");
    if (!temp) {
        perror("Greska pri otvaranju privremene datoteke");
        fclose(f);
        return;
    }

    int trazeniID;
    printf("Unesite ID za brisanje: ");
    scanf("%d", &trazeniID);
    ocistiBuffer();

    Dogadaj d;
    int noviID = 1, found = 0;

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
        printf("Dogadaj obrisan.\n");
    else
        printf("Dogadaj nije pronaden.\n");
}

int usporediPoIDu(const void* a, const void* b) {
    const Dogadaj* d1 = (const Dogadaj*)a;
    const Dogadaj* d2 = (const Dogadaj*)b;
    return (d1->id - d2->id);
}

void pretraziDogadaj() {
    char period[MAX_PERIOD];
    printf("Unesite naziv povijesnog perioda za pretragu: ");
    fgets(period, sizeof(period), stdin);
    period[strcspn(period, "\n")] = 0;

    char imeDatoteke[MAX_PERIOD + 10];
    snprintf(imeDatoteke, sizeof(imeDatoteke), "%s.bin", period);

    FILE* f = fopen(imeDatoteke, "rb");
    if (!f) {
        perror("Greska pri otvaranju datoteke");
        return;
    }

    fseek(f, 0, SEEK_END);
    long velicina = ftell(f);
    rewind(f);

    int brojDogadaja = velicina / sizeof(Dogadaj);
    if (brojDogadaja == 0) {
        printf("Nema dogadaja u datoteci.\n");
        fclose(f);
        return;
    }

    Dogadaj* niz = (Dogadaj*)malloc(brojDogadaja * sizeof(Dogadaj));
    if (!niz) {
        perror("Alokacija memorije nije uspjela");
        fclose(f);
        return;
    }

    fread(niz, sizeof(Dogadaj), brojDogadaja, f);
    fclose(f);

    qsort(niz, brojDogadaja, sizeof(Dogadaj), usporediPoIDu);

    int trazeniID;
    printf("Unesite ID za pretragu: ");
    scanf("%d", &trazeniID);
    getchar();

    Dogadaj kljuc = { .id = trazeniID };
    Dogadaj* rezultat = (Dogadaj*)bsearch(&kljuc, niz, brojDogadaja, sizeof(Dogadaj), usporediPoIDu);

    if (rezultat) {
        printf("\nPronaden događaj:\nID: %d\nNaziv: %s\nDatum: %s\nLokacija: %s\nOpis: %s\n",
            rezultat->id, rezultat->naziv, rezultat->datum, rezultat->lokacija, rezultat->opis);
    }
    else {
        printf("Dogadaj s ID %d nije pronaden.\n", trazeniID);
    }

    free(niz);
}