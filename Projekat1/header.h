#define _CRT_SECURE_NO_WARNINGS

#ifndef HEADER_H
#define HEADER_H

#define MAX_NAZIV 100 //makro funkcija//
#define MAX_DATUM 20
#define MAX_LOKACIJA 100
#define MAX_OPIS 256
#define MAX_PERIOD 100

typedef struct { //typedef za strukturu//
    int id; //primitivni tip podatka za cjelobrojnu vrijednost//
    char naziv[MAX_NAZIV]; //statički zauzeto polje//
    char datum[MAX_DATUM];
    char lokacija[MAX_LOKACIJA];
    char opis[MAX_OPIS];
} Dogadaj; //složeni tip podatka za strukturu događaja//

typedef enum { //typedef za enum//
    IZLAZ = 0,
    DODAJ_DOGADJAJ,
    ISPISI_DOGADJAJE,
    AZURIRAJ_DOGADJAJ,
    OBRISI_DOGADJAJ,
    PRETRAZI_DOGADJAJ //struktura funkcije//
} IzbornikOpcija;

extern void dodajDogadaj();
extern void ispisiDogadaje();
extern void azurirajDogadaj();
extern void obrisiDogadaj();
extern void pretraziDogadaj(); //extern void omogućuje pristup funkcijama iz drugog modula//

#endif