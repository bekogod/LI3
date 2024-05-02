#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include "flightCatalog.h"
#include "userCatalog.h"
#include "reservationCatalog.h"
#include "estatistica.h"

typedef struct catalogManager *CATALOG_MANAGER;

CATALOG_MANAGER newCatalogManager();

void insertUserCM(CATALOG_MANAGER cm, USER u);

void insertFlightCM(CATALOG_MANAGER cm, FLIGHT f);

void insertReservationCM(CATALOG_MANAGER cm, RESERVATION r);

USER getUser(CATALOG_MANAGER cm, char* id);

GHashTable* getUserByInitialCM(CATALOG_MANAGER cm);

GHashTable* getUserByDataCM(CATALOG_MANAGER cm);

FLIGHT getFlight(CATALOG_MANAGER cm, char* id);

RESERVATION getReservation(CATALOG_MANAGER cm, char* id);

ESTATISTICA getEstatistica(CATALOG_MANAGER cm);

GHashTable* get_reservation_by_hotelCM(CATALOG_MANAGER cm);

GHashTable* getFlightByOriginCM(CATALOG_MANAGER cm);

GHashTable* getFlightByIDCM(CATALOG_MANAGER cm);

GHashTable* getReservationByHotelByData(CATALOG_MANAGER cm);

GHashTable* getFlightByOrginByDataCM(CATALOG_MANAGER cm);

void removeFlightCM(CATALOG_MANAGER cm, char* id);

void insertAllFlightsCM(CATALOG_MANAGER cm);

void freeCM(CATALOG_MANAGER cm);

void allFilesProcessed(CATALOG_MANAGER cm, char ** files);
#endif