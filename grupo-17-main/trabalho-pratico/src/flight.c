#include "flight.h"

struct flight {
    char* id;                       
    char* airline;                  
    char* plane_model;              
    char* origin;                   
    char* destination;              
    int total_seats;                
    GSList* passengers;
    char* beginning_date;           
    char* arrival_date;             
    int delay;                     
};

//array auxiliar com 9 campos

char* get_Flight_id (FLIGHT f) {
    char* id = strdup(f->id);
    return id;
}

void set_flight_id(FLIGHT f, const char* new_id) {
    f->id = strdup(new_id);
}


char* get_Flight_airline (FLIGHT f) {
    char* airline = strdup(f->airline);
    return airline;
}

void set_flight_airline(FLIGHT f, const char* new_airline) {
    f->airline = strdup(new_airline);
}


char* get_Flight_plane_model (FLIGHT f) {
    char* model = strdup(f->plane_model);
    return model;
}

void set_flight_plane_model(FLIGHT f, const char* new_plane_model) {
    f->plane_model = strdup(new_plane_model);
}


char* get_Flight_origin (FLIGHT f) {
    char* origem = strdup(f->origin);
    return origem;
}

void set_flight_origin(FLIGHT f, const char* new_origin) {
    char* origem = g_ascii_strup(new_origin, -1);
    f->origin = origem;
}


char* get_Flight_destination (FLIGHT f) {
    char* destino = strdup(f->destination);
    return destino;
}

void set_flight_destination(FLIGHT f, const char* new_destination) {
    f->destination = g_ascii_strup(new_destination, -1);
}

int get_Flight_seats(FLIGHT f){
    return f->total_seats;
    }

void set_flight_seats(FLIGHT f, int new_seats){
    f->total_seats = new_seats;
}


GSList* get_Flight_passengers(FLIGHT f) {
    return f->passengers;
}

void set_Flight_passengers(FLIGHT f, GSList *newPassengers) {
    g_slist_free_full(f->passengers, g_free);

    f->passengers = newPassengers;
}


char* get_Flight_begin_date (FLIGHT f) {
    char* data_partida = strdup(f->beginning_date);
    return data_partida;
}

void set_flight_begin_date(FLIGHT f, const char* new_beginning_date) {
    f->beginning_date = strdup(new_beginning_date);
}


char* get_Flight_arrival_date (FLIGHT f) {
    char* data_chegada = strdup(f->arrival_date);
    return data_chegada;
}

void set_flight_arrival_date(FLIGHT f, const char* new_arrival_date) {
    f->arrival_date = strdup(new_arrival_date);
}


int get_Flight_delay (FLIGHT f) {return f->delay;}

void set_flight_delay(FLIGHT f, int new_delay) {
    f->delay = new_delay;
}

int get_Flight_number_of_passengers (FLIGHT f) {return g_slist_length(f->passengers);}

   
FLIGHT create_Flight (char *args []){
    FLIGHT f = malloc(sizeof(struct flight));
    //args terá sempre tamanho 9
    set_flight_id(f,args[0]);
    set_flight_airline(f,args[1]);
    set_flight_plane_model(f,args[2]);
    set_flight_origin(f,args[4]);
    set_flight_destination(f,args[5]);
    set_flight_seats(f,atoi(args[3]));
    GSList * passageiros = NULL;
    f->passengers = passageiros;
    set_flight_begin_date(f,args[6]);
    set_flight_arrival_date(f,args[7]);
    int delay = calculateDateTimeDifference(args[6],args[8]);
    set_flight_delay(f,delay);
  
    return f;
}

void free_Flight (FLIGHT f){
    if(f != NULL){

        free(f->id);
        free(f->airline);
        free(f->plane_model);
        free(f->origin);
        free(f->destination);

        g_slist_free_full(f->passengers, free);
        
        free(f->beginning_date);
        free(f->arrival_date);

        free(f);
    }
}

void print_Flight (FLIGHT f){
    printf("\n---VOO %s---\n", f->id);
    printf("Airline: %s\n", f->airline);
    printf("Aeroporto: %s\n", f->origin);
    printf("Destino: %s\n", f->destination);
    printf("Numero de lugares: %d\n", f->total_seats);
    printf("Numero de Passageiros: %d\n", g_slist_length(f->passengers));
    printf("Data de partida: %s\n", f->beginning_date);
    printf("Data de chegada: %s\n", f->arrival_date);
    printf("Delay: %d\n", f->delay);
}


void inserirPassengerEmFlight(FLIGHT f, char * passid){
    if (g_slist_find(f->passengers, passid) == NULL){
        f->passengers = g_slist_prepend(f->passengers, g_strdup(passid));
    }
}
