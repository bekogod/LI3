#ifndef FLIGHTCATALOG_H
#define FLIGHTCATALOG_H

#include "flight.h"

typedef struct flightCatalog *FLIGHT_CATALOG;

FLIGHT_CATALOG newFlightCatalog();

void insertFlightByID(GHashTable* catalog, FLIGHT flight);

FLIGHT AUXgetFlightById(GHashTable* catalog, char* id);

gint compare_flights(gconstpointer a, gconstpointer b);

void insertFlightByOrigin(GHashTable* catalogOrigin, FLIGHT flight);

void removeFlightEntry(GHashTable* catalogById, char * id_voo);

void insertFlight(FLIGHT_CATALOG fc, FLIGHT f);

FLIGHT getFlightById(FLIGHT_CATALOG fc, char* id);

GHashTable* getFlightByOrigin(FLIGHT_CATALOG fc);

GHashTable* getFlightByIDtable(FLIGHT_CATALOG fc);

GHashTable* getFlightByOrginByData(FLIGHT_CATALOG fc);

void deleteFlight(FLIGHT_CATALOG fc, char* id);

void insertFlightByOriginByData(GHashTable* catalog, FLIGHT f);

void insertAllFlights(FLIGHT_CATALOG fc);

void free_flight_catalog(FLIGHT_CATALOG catalog);
#endif