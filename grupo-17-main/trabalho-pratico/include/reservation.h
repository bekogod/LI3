#ifndef RESERVATION_H
#define RESERVATION_H

#include <glib-2.0/glib.h>
#include <string.h>
#include <stdio.h>
#include <utily.h>
#include <stdlib.h>


typedef struct reservation *RESERVATION;

char* get_Reservation_ID (RESERVATION r);
void set_reservation_id(RESERVATION r, const char* new_id);

char* get_Reservation_User_ID (RESERVATION r);
void set_reservation_user_id(RESERVATION r, const char* new_user_id);

char* get_Reservation_hotel_id (RESERVATION r);
void set_reservation_hotel_id(RESERVATION r, const char* new_hotel_id);

char* get_Reservation_hotel_name (RESERVATION r);
void set_reservation_hotel_name(RESERVATION r, const char* new_hotel_name);

int get_Reservation_hotel_stars (RESERVATION r);
void set_reservation_hotel_stars(RESERVATION r, int new_hotel_stars);

char* get_Reservation_begin_date (RESERVATION r);
void set_reservation_begin_date(RESERVATION r, const char* new_begin_date);

char* get_Reservation_end_date (RESERVATION r);
void set_reservation_end_date(RESERVATION r, const char* new_end_date);

int get_Reservation_breakfast (RESERVATION r);
void set_reservation_breakfast(RESERVATION r, int new_breakfast);

int get_Reservation_nights (RESERVATION r);
void set_reservation_nights(RESERVATION r, int new_nights);

int get_Reservation_price (RESERVATION r);
void set_reservation_price_per_night(RESERVATION r, int new_price_per_night);

int get_Reservation_city_tax (RESERVATION r);
void set_reservation_city_tax(RESERVATION r, int new_city_tax);

int get_Reservation_rating (RESERVATION r);
void set_reservation_rating(RESERVATION r, int new_rating);

RESERVATION create_Reservation (char *args[]);

void free_Reservation (RESERVATION r);

#endif
