#ifndef USERCATALOG_H
#define USERCATALOG_H

#include "user.h"
#include <locale.h>

typedef struct userCatalog *USER_CATALOG;

USER_CATALOG newUserCatalog();

void insertUserById(GHashTable* catalog, USER user);

void insertUserByInitial (GHashTable *catalogo, USER u);

void insertUserByData(GHashTable * catalog, USER u);

int compareUser(gconstpointer a, gconstpointer b);

USER AUXgetUserById(GHashTable* catalog, char* id);

void insertUser(USER_CATALOG uc, USER user);

USER getUserById(USER_CATALOG uc, char* id);

GHashTable * getUserByInitial(USER_CATALOG uc);

GHashTable * getUserByData(USER_CATALOG uc);

void free_user_catalog(USER_CATALOG uc);

#endif