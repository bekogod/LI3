#ifndef USER_H
#define USER_H

#include <string.h>
#include <stdio.h>
#include "utily.h"

typedef struct user *USER;

char* get_User_id (USER u);
void set_user_id(USER u, const char* new_id);

char* get_User_name (USER u);
void set_user_name(USER u, const char* new_name);

char* get_User_sex (USER u);
void set_user_sex(USER u, const char* new_sex);

int get_User_age (USER u);
void set_user_age(USER u, int new_age);

char* get_User_country (USER u);
void set_user_country_code(USER u, const char* new_country_code);

GSList* get_User_flights (USER u);

GSList* get_User_reservation (USER u);
void set_User_reservations(USER u, GSList* list);

double get_User_spent (USER u);
void set_user_total_spent(USER u, double new_total_spent);
void add_total_spent(USER u, double preco);

char* get_User_status (USER u);
void set_user_account_status(USER u, const char* new_account_status);

char* get_User_creation_date (USER u);
void set_user_account_creation(USER u, const char* new_account_creation);

char* get_User_passport (USER u);
void set_user_passport (USER u, const char* new_passport);

USER create_User (char *args []);

void free_User (USER u);

void print_User (USER u);

void inserirFlightEmUser(USER u, char * flightid);

void inserirReservationEmUser(USER u, char * resid, double preco);
#endif