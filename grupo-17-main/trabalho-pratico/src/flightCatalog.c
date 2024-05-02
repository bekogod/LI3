//flightCatalog.c

#include "flightCatalog.h"

struct flightCatalog {
    GHashTable * flight_by_id;
    GHashTable * flight_by_origin;
    GHashTable * flight_by_origin_by_data;
};

FLIGHT_CATALOG newFlightCatalog(){
    FLIGHT_CATALOG fc = malloc(sizeof(struct flightCatalog));
    fc->flight_by_id = g_hash_table_new(g_str_hash, g_str_equal);
    fc->flight_by_origin = g_hash_table_new(g_str_hash, g_str_equal);
    fc->flight_by_origin_by_data = g_hash_table_new(g_str_hash, g_str_equal);
    return fc;
}

// HASHTABLE FLIGHT_BY_ID

// Adiciona um flight ao catálogo de users
void insertFlightByID(GHashTable* catalog, FLIGHT flight){
    char * id = get_Flight_id(flight);
    g_hash_table_insert(catalog, id, flight);
}

// Retorna um flight presente no catálogo com um certo id
FLIGHT AUXgetFlightById(GHashTable* catalog, char* id){
    return g_hash_table_lookup(catalog, id);
}



//HASTABLE FLIGHT_BY_ORIGIN

// Compare function que será usada para inserir com critério numa estrutura de dados
gint compare_flights(gconstpointer a, gconstpointer b) {
    const FLIGHT flight_a = *(FLIGHT*) a;
    const FLIGHT flight_b = *(FLIGHT*) b;

    char * data_b = get_Flight_begin_date(flight_b);
    char * data_a = get_Flight_begin_date(flight_a);
    char * id_a = get_Flight_id(flight_a);
    char * id_b = get_Flight_id(flight_b);

    // Use strcmp to compare the flight ids
    gint date_comparison = strcmp(data_b, data_a);

    // If dates are equal then compare de id's
    if (date_comparison == 0) {
        date_comparison = strcmp(id_a, id_b);
    }

    free(data_b);
    free(data_a);
    free(id_a);
    free(id_b);

    // If ids are equal, compare by destination
    return date_comparison;
}

// Insere um voo numa hash table que está organizada por origem
void insertFlightByOrigin(GHashTable* catalogOrigin, FLIGHT flight){
    char * org = get_Flight_origin(flight);
    if (!g_hash_table_contains(catalogOrigin, org)){
        GList *new_list = NULL;
        g_hash_table_insert(catalogOrigin, strdup(org), new_list);
    }
    GList *list = g_hash_table_lookup(catalogOrigin, org);
    list = g_list_prepend(list, flight);
    g_hash_table_replace(catalogOrigin, strdup(org), list);
    free(org);
}

void removeFlightEntry(GHashTable* catalogById, char * id_voo){
    FLIGHT f = AUXgetFlightById(catalogById, id_voo);
    const gchar *key_to_remove = g_strdup(id_voo);
    g_hash_table_remove(catalogById, key_to_remove);
    g_free((gchar*)key_to_remove);
    free_Flight(f);
}

void insertFlight(FLIGHT_CATALOG fc, FLIGHT f){
    insertFlightByID(fc->flight_by_id, f);
}

FLIGHT getFlightById(FLIGHT_CATALOG fc, char* id){
    return AUXgetFlightById(fc->flight_by_id, id);
}

GHashTable* getFlightByOrigin(FLIGHT_CATALOG fc){
    return fc->flight_by_origin;
} 

GHashTable* getFlightByIDtable(FLIGHT_CATALOG fc){
    return fc->flight_by_id;
} 

GHashTable* getFlightByOrginByData(FLIGHT_CATALOG fc){
    return fc->flight_by_origin_by_data;
}

void deleteFlight(FLIGHT_CATALOG fc, char* id){
    removeFlightEntry(fc->flight_by_id, id);
}

void insertFlightByOriginByData(GHashTable* catalog, FLIGHT f){
    char * ori = get_Flight_origin(f);
    if (!g_hash_table_contains(catalog, ori)){
        GHashTable *new_hash = g_hash_table_new(g_str_hash, g_str_equal);
        g_hash_table_insert(catalog, strdup(ori), new_hash);
    }

    GHashTable* hashOri = g_hash_table_lookup(catalog, ori);
    char * datatime = get_Flight_begin_date(f);
    char* partida = get_date_from_datetime(datatime);


    if (!g_hash_table_contains(hashOri, partida)){
        GList *new_list = NULL;
        g_hash_table_insert(hashOri, strdup(partida), new_list);
    }
    GList *list = g_hash_table_lookup(hashOri, partida);
    list = g_list_prepend(list, f);
    g_hash_table_replace(hashOri, strdup(partida), list);
    free(partida);
    free(datatime);
    free(ori);
}

static void insertAux(gpointer key, gpointer value, gpointer user_data) {
    (void)key;
    FLIGHT_CATALOG fc = (FLIGHT_CATALOG)user_data;
    insertFlightByOrigin(fc->flight_by_origin, (FLIGHT)value);
    insertFlightByOriginByData (fc->flight_by_origin_by_data, (FLIGHT)value);
}

void insertAllFlights(FLIGHT_CATALOG fc){
    GHashTable* voos_id = fc->flight_by_id;
    g_hash_table_foreach(voos_id, insertAux, fc);
}

void free_flight_catalog(FLIGHT_CATALOG catalog) {
    GHashTableIter iter;
    gpointer key, value;

    // Percorre flight_by_id e libera a memória de cada voo
    g_hash_table_iter_init(&iter, catalog->flight_by_id);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        free_Flight((struct flight *)value);
        g_free(key);
    }

    // Libera flight_by_id
    g_hash_table_destroy(catalog->flight_by_id);

    // Percorre flight_by_origin e libera a memória de cada lista de voos
    g_hash_table_iter_init(&iter, catalog->flight_by_origin);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GList *flight_list = (GList *)value;
        g_list_free(flight_list);
        g_free(key);
    }

    // Libera flight_by_origin
    g_hash_table_destroy(catalog->flight_by_origin);

    g_hash_table_iter_init(&iter, catalog->flight_by_origin_by_data);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
            free_inner_hash_table(value);
    }
    g_hash_table_destroy(catalog->flight_by_origin_by_data);

    // Libera a própria estrutura flightCatalog
    g_free(catalog);
}