#ifndef ESTATISTICA_H
#define ESTATISTICA_H

#include <glib-2.0/glib.h>
#include <string.h>
#include <stdio.h>
#include <utily.h>

typedef struct atraso *ATRASO;

char * getAerporto (ATRASO a);

void setAeroporto (ATRASO a, char* aeroporto);

int getDelay (ATRASO a);

void setDelay (ATRASO a, int delay);

typedef struct estatistica *ESTATISTICA;

int getFlag (ESTATISTICA e);

void setFlag (ESTATISTICA e, int flag);

GArray* getAtrasos(ESTATISTICA e);

ESTATISTICA newEstatistica();

void addAtraso(ATRASO newAtraso, ESTATISTICA e);

void createAtraso(char* aeroporto, int delay, ESTATISTICA e);

void freeEstatistica(ESTATISTICA e);

int compare_atraso(const void* a, const void* b);

void sortAtrasos(ESTATISTICA e);

void addTime(ESTATISTICA e, int query, double time);

void queryTime(ESTATISTICA e);
#endif