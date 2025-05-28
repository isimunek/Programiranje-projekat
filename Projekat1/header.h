#define _CRT_SECURE_NO_WARNINGS

#ifndef HEADER_H
#define HEADER_H

#define MAX_NAZIV 100
#define MAX_DATUM 20
#define MAX_LOKACIJA 100
#define MAX_OPIS 256
#define MAX_PERIOD 100

typedef struct {
    int id;
    char naziv[MAX_NAZIV];
    char datum[MAX_DATUM];
    char lokacija[MAX_LOKACIJA];
    char opis[MAX_OPIS];
} Dogadaj;

void dodajDogadaj();
void ispisiDogadaje();
void azurirajDogadaj();
void obrisiDogadaj();

#endif