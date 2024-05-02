#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <stdio.h>
#include <stdlib.h> 
#include "queries.h"
#include "catalogManager.h"

int countArguments(char *str);

char** processString(char *str, int numArguments);

void parseQuery(char input[], int *queryId, int *formatFlag, char *arg1);

void executarComandos(CATALOG_MANAGER cm, char * infile);


#endif