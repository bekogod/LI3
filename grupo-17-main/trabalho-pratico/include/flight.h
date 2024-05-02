#ifndef FLIGHT_H
#define FLIGHT_H

#include <glib-2.0/glib.h>
#include <string.h>
#include <stdio.h>
#include <utily.h>

typedef struct flight *FLIGHT;

char* get_Flight_id (FLIGHT f);
void set_flight_id(FLIGHT f, const char* new_id);

char* get_Flight_airline (FLIGHT f);
void set_flight_airline(FLIGHT f, const char* new_airline);

char* get_Flight_plane_model (FLIGHT f);
void set_flight_plane_model(FLIGHT f, const char* new_plane_model);

char* get_Flight_origin (FLIGHT f);
void set_flight_origin(FLIGHT f, const char* new_origin);

char* get_Flight_destination (FLIGHT f);
void set_flight_destination(FLIGHT f, const char* new_destination);

int get_Flight_seats(FLIGHT f);
void set_flight_seats(FLIGHT f, int new_seats);

GSList* get_Flight_passengers (FLIGHT f);
void set_Flight_passengers(FLIGHT f, GSList* list);

char* get_Flight_begin_date (FLIGHT f);
void set_flight_begin_date(FLIGHT f, const char* new_beginning_date);

char* get_Flight_arrival_date (FLIGHT f);
void set_flight_arrival_date(FLIGHT f, const char* new_arrival_date);

int get_Flight_delay (FLIGHT f);
void set_flight_delay(FLIGHT f, int new_delay);

int get_Flight_number_of_passengers (FLIGHT f);

FLIGHT create_Flight (char *args []);

void free_Flight (FLIGHT f);

void inserirPassengerEmFlight(FLIGHT F, char * passid);


#endif