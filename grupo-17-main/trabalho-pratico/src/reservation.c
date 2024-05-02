#include "reservation.h"

struct reservation {
    char* id;           
    char* user_id;      
    char* hotel_id;     
    char* hotel_name;   
    int hotel_stars;    
    char* begin_date;   
    char* end_date;     
    int breakfast;      
    int nights;  
    int price_per_night; 
    int city_tax;       
    int rating;         
};

//array auxiliar com 11 parametros

char* get_Reservation_ID (RESERVATION r) {
    char* id_reserva = strdup(r->id);
    return id_reserva;
}

void set_reservation_id(RESERVATION r, const char* new_id) {
    r->id = strdup(new_id);
}


char* get_Reservation_User_ID (RESERVATION r) {
    char* id_user = strdup(r->user_id);
    return id_user;
}

void set_reservation_user_id(RESERVATION r, const char* new_user_id) {
    r->user_id = strdup(new_user_id);
}


char* get_Reservation_hotel_id (RESERVATION r) {
    char* id_hotel = strdup(r->hotel_id);
    return id_hotel;
}

void set_reservation_hotel_id(RESERVATION r, const char* new_hotel_id) {
    r->hotel_id = strdup(new_hotel_id);
}


char* get_Reservation_hotel_name (RESERVATION r) {
    char* nome_hotel = strdup(r->hotel_name);
    return nome_hotel;
}

void set_reservation_hotel_name(RESERVATION r, const char* new_hotel_name) {
    r->hotel_name = strdup(new_hotel_name);
}


int get_Reservation_hotel_stars (RESERVATION r) {return r->hotel_stars;}

void set_reservation_hotel_stars(RESERVATION r, int new_hotel_stars) {
    r->hotel_stars = new_hotel_stars;
}

char* get_Reservation_begin_date (RESERVATION r) {
    char* data_inicio = strdup(r->begin_date);
    return data_inicio;
}

void set_reservation_begin_date(RESERVATION r, const char* new_begin_date) {
    r->begin_date = strdup(new_begin_date);
}


char* get_Reservation_end_date (RESERVATION r) {
    char* data_fim = strdup(r->end_date);
    return data_fim;
}

void set_reservation_end_date(RESERVATION r, const char* new_end_date) {
    r->end_date = strdup(new_end_date);
}


int get_Reservation_breakfast (RESERVATION r) {return r->breakfast;}

void set_reservation_breakfast(RESERVATION r, int new_breakfast) {
    r->breakfast = new_breakfast;
}


int get_Reservation_nights (RESERVATION r) {return r->nights;}

void set_reservation_nights(RESERVATION r, int new_nights) {
    r->nights = new_nights;
}


int get_Reservation_price (RESERVATION r) {return r->price_per_night;}

void set_reservation_price_per_night(RESERVATION r, int new_price_per_night) {
    r->price_per_night = new_price_per_night;
}


int get_Reservation_city_tax (RESERVATION r) {return r->city_tax;}

void set_reservation_city_tax(RESERVATION r, int new_city_tax) {
    r->city_tax = new_city_tax;
}


int get_Reservation_rating (RESERVATION r) {return r->rating;}

void set_reservation_rating(RESERVATION r, int new_rating) {
    r->rating = new_rating;
}

RESERVATION create_Reservation (char *args[]){
    RESERVATION r = malloc(sizeof(struct reservation));
    //este array tem sempre tamanho 11
    set_reservation_id(r,args[0]);
    set_reservation_user_id(r,args[1]);
    set_reservation_hotel_id(r,args[2]);
    set_reservation_hotel_name(r,args[3]);
    set_reservation_hotel_stars(r,atoi(args[4]));
    set_reservation_begin_date(r,args[7]);
    set_reservation_end_date(r,args[8]);
    int bf = haveBreakfast(args[10]);
    set_reservation_breakfast(r,bf);
    int nights = calculateDateDifference(args[7],args[8]);
    set_reservation_nights(r,nights);
    set_reservation_price_per_night(r,atoi(args[9]));
    set_reservation_city_tax(r,atoi(args[5]));
    set_reservation_rating(r,atoi(args[12]));

    return r;
}

void free_Reservation (RESERVATION r){
    if(r != NULL){

        free(r->id);
        free(r->user_id);
        free(r->hotel_id);
        free(r->hotel_name);
        free(r->begin_date);
        free(r->end_date);

        free(r);
    }
}

void print_Reservation (RESERVATION r){
    printf("\n---Reserva %s---\n", r->id);
    printf("User: %s\n", r->user_id);
    printf("ID do Hotel: %s\n", r->hotel_id);
    printf("Hotel: %s\n", r->hotel_name);
    printf("Estrelas: %d\n", r->hotel_stars);
    printf("Data de entrada: %s\n", r->begin_date);
    printf("Data de Saida: %s\n", r->end_date);
    printf("Pequeno almoço: %d\n", r->breakfast);
    printf("Noites: %d\n", r->nights);
    printf("Preço por Noite: %d\n", r->price_per_night);
    printf("Taxa: %d\n", r->city_tax);
    printf("Avaliação: %d\n", r->rating);
}
