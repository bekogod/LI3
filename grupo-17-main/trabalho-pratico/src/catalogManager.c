#include "catalogManager.h"

struct catalogManager {
    FLIGHT_CATALOG flightCatalog;
    RESERVATION_CATALOG reservationCatalog;          
    USER_CATALOG userCatalog;
    ESTATISTICA e;
};

CATALOG_MANAGER newCatalogManager(){
    CATALOG_MANAGER cm = malloc(sizeof(struct catalogManager));
    cm->flightCatalog = newFlightCatalog();
    cm->reservationCatalog = newReservationCatalog();
    cm->userCatalog = newUserCatalog();
    cm->e = newEstatistica();
    return cm;
}

void insertUserCM(CATALOG_MANAGER cm, USER u){
    insertUser(cm->userCatalog, u);
}

void insertFlightCM(CATALOG_MANAGER cm, FLIGHT f){
    insertFlight(cm->flightCatalog, f);
}

void insertReservationCM(CATALOG_MANAGER cm, RESERVATION r){
    insertReservation(cm->reservationCatalog, r);
}

USER getUser(CATALOG_MANAGER cm, char* id){
    // retorna um user ou NULL
    return getUserById(cm->userCatalog, id);
}

GHashTable* getUserByInitialCM(CATALOG_MANAGER cm){
    return getUserByInitial(cm->userCatalog);
}

GHashTable* getUserByDataCM(CATALOG_MANAGER cm){
    return getUserByData(cm->userCatalog);
}

FLIGHT getFlight(CATALOG_MANAGER cm, char* id){
    return getFlightById(cm->flightCatalog, id);
}

RESERVATION getReservation(CATALOG_MANAGER cm, char* id){
    return getReservationById(cm->reservationCatalog, id);
}

ESTATISTICA getEstatistica(CATALOG_MANAGER cm){
    return (cm->e);
}

GHashTable* get_reservation_by_hotelCM(CATALOG_MANAGER cm){
    return get_reservation_by_hotel(cm->reservationCatalog);
}

GHashTable* getFlightByOriginCM(CATALOG_MANAGER cm){
    return getFlightByOrigin(cm->flightCatalog);
}
GHashTable* getFlightByIDCM(CATALOG_MANAGER cm){
    return getFlightByIDtable(cm->flightCatalog);
}

GHashTable* getReservationByHotelByData(CATALOG_MANAGER cm){
    return get_reservation_by_hotel_by_data(cm->reservationCatalog);
}

GHashTable* getFlightByOrginByDataCM(CATALOG_MANAGER cm){
    return getFlightByOrginByData(cm->flightCatalog);
}

void removeFlightCM(CATALOG_MANAGER cm, char* id){
    deleteFlight(cm->flightCatalog, id);
}

void insertAllFlightsCM(CATALOG_MANAGER cm){
    insertAllFlights(cm->flightCatalog);
}

void freeCM(CATALOG_MANAGER cm){
    free_user_catalog(cm->userCatalog);
    free_flight_catalog(cm->flightCatalog);
    free_reservation_catalog(cm->reservationCatalog);
    freeEstatistica(cm->e);
    free(cm);
}

void allFilesProcessed(CATALOG_MANAGER cm, char ** files){
    GHashTable* idVoo_linhaOriginal = g_hash_table_new(g_str_hash, g_str_equal);
    processUsersFile (cm, files[0], files[1]);
    printf("O ficheiro de Users foi processado!!!\n");
    processReservationsFile (cm, files[4], files[5]);
    printf("O ficheiro de Reservas foi processado!!!\n");
    processFlightsFile (cm, files[2], files[3], idVoo_linhaOriginal);
    printf("O ficheiro de Voos foi processado!!!\n");
    processPassengersFile (cm, files[6], files[7], files[3], idVoo_linhaOriginal);
    printf("O ficheiro de Passageiros foi processado!!!\n");
    insertAllFlightsCM(cm);
    freeHashTable(idVoo_linhaOriginal);
}