#ifndef PARSER_H
#define PARSER_H

#include "validation.h"
#include "utily.h"
#include "catalogManager.h"

void processUsersFile (CATALOG_MANAGER cm, char * infile, char * outfile);

void processFlightsFile (CATALOG_MANAGER cm, char * infile, char * outfile, GHashTable* idVoo_linhaOriginal);

void processReservationsFile (CATALOG_MANAGER cm, char * infile, char * outfile);

void processPassengersFile (CATALOG_MANAGER cm, char * infile, char * outfilePass, char * outfileVoos, GHashTable* idVoo_linhaOriginal);

#endif