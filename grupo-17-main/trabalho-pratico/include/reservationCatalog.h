#ifndef RESERVATIONCATALOG_H
#define RESERVATIONCATALOG_H

#include "reservation.h"

typedef struct reservationCatalog *RESERVATION_CATALOG;

RESERVATION_CATALOG newReservationCatalog();

void insertReservationById(GHashTable* catalog, RESERVATION reservation);

RESERVATION AUXgetReservationById(GHashTable* catalog, char* id);

int compare_reservation(gconstpointer a, gconstpointer b);

void insertReservationByHotel(GHashTable* catalogoHotel, RESERVATION r);

void insertReservationByHotelByData(GHashTable* catalog, RESERVATION r);

void insertReservation(RESERVATION_CATALOG rc, RESERVATION r);

RESERVATION getReservationById(RESERVATION_CATALOG rc, char* id);

GHashTable* get_reservation_by_hotel(RESERVATION_CATALOG rc);

GHashTable* get_reservation_by_hotel_by_data(RESERVATION_CATALOG rc);

void free_reservation_catalog(RESERVATION_CATALOG catalog);
#endif