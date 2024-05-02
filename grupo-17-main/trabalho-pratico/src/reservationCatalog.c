//reservationCatalog.c

#include "reservationCatalog.h"

struct reservationCatalog {
    GHashTable * reservation_by_id;
    GHashTable * reservation_by_hotel;
    GHashTable * reservation_by_hotel_by_data;
};

RESERVATION_CATALOG newReservationCatalog(){
    RESERVATION_CATALOG rc = malloc(sizeof(struct reservationCatalog));
    rc->reservation_by_id = g_hash_table_new(g_str_hash, g_str_equal);
    rc->reservation_by_hotel = g_hash_table_new(g_str_hash, g_str_equal);
    rc->reservation_by_hotel_by_data = g_hash_table_new(g_str_hash, g_str_equal);
    return rc;
}

// HASHTABLE RESERVATION_BY_ID

// Adiciona uma reservation ao catálogo de users
void insertReservationById(GHashTable* catalog, RESERVATION reservation){
    char * id = get_Reservation_ID(reservation);
    g_hash_table_insert(catalog, id, reservation);
}

// Retorna uma reservation presente no catálogo com um certo id
RESERVATION AUXgetReservationById(GHashTable* catalog, char* id){
    return g_hash_table_lookup(catalog, id);
}


//HASHTABLE RESERVATION_BY_HOTEL

// Compare function que será usada para inserir com critério numa estrutura de dados
int compare_reservation(gconstpointer a, gconstpointer b) {
    const RESERVATION r_a = *(RESERVATION*) a;
    const RESERVATION r_b = *(RESERVATION*) b;

    char * data_b = get_Reservation_begin_date(r_b);
    char * data_a = get_Reservation_begin_date(r_a);
    char * id_a = get_Reservation_ID(r_a);
    char * id_b = get_Reservation_ID(r_b);
    
    // Use strcmp to compare the reservation ids
    gint date_comparison = strcmp(data_b, data_a);

    // If date is the same, compare id's
    if (date_comparison == 0) {
        date_comparison = strcmp(id_a, id_b);
    }

    free(data_b);
    free(data_a);
    free(id_a);
    free(id_b);
    
    return date_comparison;
}

// Insere uma reserva numa hash table que está organizada por hotel
void insertReservationByHotel(GHashTable* catalogoHotel, RESERVATION r){
    char * hotel = get_Reservation_hotel_id(r);
    if (!g_hash_table_contains(catalogoHotel, hotel)){
        GList *new_list = NULL;
        g_hash_table_insert(catalogoHotel, strdup(hotel), new_list);
    }
    GList *list = g_hash_table_lookup(catalogoHotel, hotel);
    list = g_list_prepend(list, r);
    g_hash_table_replace(catalogoHotel, strdup(hotel), list);
    free(hotel);
}

void insertReservationByHotelByData(GHashTable* catalog, RESERVATION r){
    char * hotel = get_Reservation_hotel_id(r);
    if (!g_hash_table_contains(catalog, hotel)){
        GHashTable *new_hash = g_hash_table_new(g_str_hash, g_str_equal);
        g_hash_table_insert(catalog, strdup(hotel), new_hash);
    }

    GHashTable* hashHotel = g_hash_table_lookup(catalog, hotel);
    char * inicio = get_Reservation_begin_date(r);
    char * fim = get_Reservation_end_date(r);
    char data_temp[11];
    strcpy(data_temp, inicio);
    while(dataEstaNoIntervalo(data_temp, inicio, fim)){
        if (strcmp(data_temp,fim)){
            if (!g_hash_table_contains(hashHotel, data_temp)){
                GList *new_list = NULL;
                g_hash_table_insert(hashHotel, strdup(data_temp), new_list);
            }
            GList *list = g_hash_table_lookup(hashHotel, data_temp);
            list = g_list_prepend(list, r);
            g_hash_table_replace(hashHotel, strdup(data_temp), list);
        }
        diaSeguinte(data_temp, data_temp);
    }
    free(hotel);
    free(inicio);
    free(fim);
}

void insertReservation(RESERVATION_CATALOG rc, RESERVATION r){
    insertReservationById(rc->reservation_by_id, r);
    insertReservationByHotel(rc->reservation_by_hotel, r);
    insertReservationByHotelByData(rc->reservation_by_hotel_by_data, r);
}

RESERVATION getReservationById(RESERVATION_CATALOG rc, char* id){
    return AUXgetReservationById(rc->reservation_by_id, id);
}

GHashTable* get_reservation_by_hotel(RESERVATION_CATALOG rc){
    return rc->reservation_by_hotel;
}

GHashTable* get_reservation_by_hotel_by_data(RESERVATION_CATALOG rc){
    return rc->reservation_by_hotel_by_data;
}

void free_reservation_catalog(RESERVATION_CATALOG catalog) {
    GHashTableIter iter;
    gpointer key, value;

    // Percorre reservation_by_id e libera a memória de cada reserva
    g_hash_table_iter_init(&iter, catalog->reservation_by_id);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        free_Reservation((struct reservation *)value);
        g_free(key);
    }

    // Libera reservation_by_id
    g_hash_table_destroy(catalog->reservation_by_id);

    // Percorre reservation_by_hotel e libera a memória de cada lista de reservas
    g_hash_table_iter_init(&iter, catalog->reservation_by_hotel);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GList *reservation_list = (GList *)value;
        g_list_free(reservation_list);
        g_free(key);
    }

    //Percorrer reservation_by_hotel_by_data e libertar a memoria das hashtables internas
    g_hash_table_iter_init(&iter, catalog->reservation_by_hotel_by_data);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
            free_inner_hash_table(value);
    }


    // Libera reservation_by_hotel
    g_hash_table_destroy(catalog->reservation_by_hotel);
    g_hash_table_destroy(catalog->reservation_by_hotel_by_data);
    // Libera a própria estrutura reservationCatalog
    g_free(catalog);
}