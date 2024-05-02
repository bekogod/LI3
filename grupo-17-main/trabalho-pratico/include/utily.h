#ifndef UTILITY_H
#define UTILITY_H

#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct q2aux * Q2AUX;

char * getq2auxID(Q2AUX aux);
void setq2auxID(Q2AUX aux, char* id);

char * getq2auxdata(Q2AUX aux);
void setq2auxdata (Q2AUX aux, char * data);

char * getq2auxhora (Q2AUX aux);
void setq2auxhora (Q2AUX aux, char* hora);

char * getq2auxtype (Q2AUX aux);
void setq2auxtype (Q2AUX aux, int type);

Q2AUX create_q2aux(char* id, char * data, int type);

void free_Q2aux(Q2AUX q);

int compareQ2AUX(const void* a, const void* b);

typedef struct keyvalue * KEYVALUE;

char* getKey (KEYVALUE k);

void setKey (KEYVALUE k, char* key);

int getValue (KEYVALUE k);

void setValue (KEYVALUE k, int value);

KEYVALUE createKeyValue(char* key, int value);

int compareValues(const void* a, const void* b);

void freeKeyValue(KEYVALUE k);

typedef struct q10aux * Q10AUX;

char * getData(Q10AUX q);

void setData(Q10AUX q, char* data);

int getNUser(Q10AUX q);

int getNPass(Q10AUX q);

void setNUser(Q10AUX q, int n_u);

int getNFlight(Q10AUX q);

void setNFlight(Q10AUX q, int n_f);

void setNPass(Q10AUX q, int n_p);

int getNPassU(Q10AUX q);

void setNPassU(Q10AUX q, int n_p_u);

int getNRes(Q10AUX q);

void setNRes(Q10AUX q, int n_r);

GHashTable * getUnique(Q10AUX q);

void addUnique(Q10AUX q, char* id);

Q10AUX create_q10(char* data);

void free_q10(void *data);

int compareQ10(const void* a, const void* b);

char* getYear(const char *date);

char* getMonth(const char *date);

char* getDay(const char *date);

char* get_date_from_datetime(const char* datetime);

void parseDate(const char *dateStr, int *year, int *month, int *day);

gpointer copy_string(gconstpointer src, gpointer data);

int calculateAge (const char* birthDate);

double calculaPreco (int precoPorNoite, int noites, int city_tax);

int calculateDateDifference(const char* date1, const char* date2);

void parseDateTime(const char *dateTimeStr, int *year, int *month, int *day, int *hour, int *minute, int *second);

int calculateDateTimeDifference(const char *dateTime1, const char *dateTime2);

int haveBreakfast(char * breakfast);

void freeArrayStrings(char ** array, int tam);

void initArrayStrings(char** array, int tam);

void removeLastNewline(char *str);

void writeListToFile(GList *list, FILE *file);

void freeHashTable(GHashTable* ht);

void print_gslist(GSList *list);

void pathsFich(char* pastaCsv, char* pastaResultados, char** array);

int comparaAtrasos(const void* a, const void* b);

double calculaMediana(int* atrasos, int numVoos);

void diaAnterior(const char *dataString, char *resultado);

void diaSeguinte(const char *dataString, char *resultado);

int dataEstaNoIntervalo(const char* data, const char* inicio, const char* fim);

void free_inner_hash_table(gpointer data);
#endif
