#ifndef VALIDATION_H
#define VALIDATION_H

#include <ctype.h>
#include "utily.h"
#include "catalogManager.h"
#include "utily.h"


int valid_default (char * string);

int valid_data (char * data);

int valid_hora (char * hora);

int valid_datacomhora(char * data);

int valid_email (char * email);

int valid_countrycode(char * code);

int valid_accountstatus(char * status);

int valid_airport(char * name);

int valid_hotelstars(char * stars);

int valid_citytax(char * citytax);

int valid_pricepernight(char * price);

int valid_includesbreakfast(char * flag);

int valid_rating(char * rating);

int valid_timeline(char * before, char * after);

int validFlight(char ** parametros, CATALOG_MANAGER cm);

int validPassengers(char * id_voo_atual, GSList * passageiros, GSList ** invalidos, CATALOG_MANAGER cm);

int validReservation(char ** parametros, CATALOG_MANAGER cm);

int validUsers(char ** parametros, CATALOG_MANAGER cm);

#endif