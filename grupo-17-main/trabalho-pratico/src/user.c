#include "user.h"

struct user{
    char* id; 
    char* name; 
    char* sex; 
    int age; 
    char* country_code;
    GSList* flights; 
    GSList* reservation;
    double total_spent;
    char* account_status; 
    char* account_creation; 
    char* passport; 
    
};
//array auxiliar de 8 tokens aquando a leitura de uma linha do fich users.csv

char* get_User_id (USER u) {
    char* id = strdup(u->id);
    return id;
}

void set_user_id(USER u, const char* new_id) {
    u->id = strdup(new_id);
}


char* get_User_name (USER u) {
    char* nome = strdup(u->name);
    return nome;
}

void set_user_name(USER u, const char* new_name) {
    u->name = strdup(new_name);
}


char* get_User_sex (USER u) {
    char* sexo = strdup(u->sex);
    return sexo;
}

void set_user_sex(USER u, const char* new_sex) {
    u->sex = strdup(new_sex);
}


int get_User_age (USER u){return u->age;}

void set_user_age(USER u, int new_age) {
    u->age = new_age;
}


char* get_User_country (USER u) {
    char* pais = strdup(u->country_code);
    return pais;
}

void set_user_country_code(USER u, const char* new_country_code) {
    u->country_code = strdup(new_country_code);
}


GSList* get_User_flights (USER u) {
    return u->flights;
}


GSList* get_User_reservation (USER u) {
    return u->reservation;
}


void set_User_reservations(USER u, GSList* list){
    g_slist_free_full(u->reservation, g_free);
    u->reservation = list;
}


double get_User_spent (USER u) {return u->total_spent;}

void set_user_total_spent(USER u, double new_total_spent) {
    u->total_spent = new_total_spent;
}

void add_total_spent(USER u, double preco){
    double total_spent = get_User_spent(u);
    total_spent += preco;
    set_user_total_spent(u, total_spent);
}

char* get_User_status (USER u) {
    char* status = strdup(u->account_status);
    return status;
}

void set_user_account_status(USER u, const char* new_account_status) {
    u->account_status = strdup(new_account_status);
}


char* get_User_creation_date (USER u) {
    char* data = strdup(u->account_creation);
    return data;
}

void set_user_account_creation(USER u, const char* new_account_creation) {
    u->account_creation = strdup(new_account_creation);
}


char* get_User_passport (USER u) {
    char* passaporte = strdup(u->passport);
    return passaporte;
}

void set_user_passport (USER u, const char* new_passport) {
    u->passport = strdup(new_passport);
}




USER create_User (char *args []) {
    USER u = malloc(sizeof(struct user));
    //este array de strings vai sempre ter tamanho 8
    set_user_id(u,args[0]);
    set_user_name(u,args[1]);
    set_user_sex(u,args[5]);
    int age = calculateAge(args[4]);
    set_user_age(u,age);
    set_user_country_code(u,args[7]);
    GSList * voos = NULL;
    u->flights = voos;
    GSList * reservas = NULL;
    u->reservation = reservas;
    set_user_total_spent(u,0);
    set_user_account_status(u,args[11]);
    set_user_account_creation(u,args[9]);
    set_user_passport(u,args[6]);

    return u;
}

void free_User (USER u){
    if(u != NULL){

        free(u->id);
        free(u->name);
        free(u->sex);
        free(u->country_code);

        g_slist_free_full(u->flights, free);
        g_slist_free_full(u->reservation, free);
        free(u->passport);
        free(u->account_status);
        free(u->account_creation);

        free(u);
    }
}

void print_User (USER u){
    if(u == NULL) printf("(NULL)");
    else{
        printf("\n---User %s---\n", u->id);
        printf("Nome: %s\n", u->name);
        printf("Sexo: %s\n", u->sex);
        printf("Idade: %d\n", u->age);
        printf("País: %s\n", u->country_code);
        printf("Nº de Voos: %d\n", g_slist_length(u->flights));
        printf("Nº de Reservas: %d\n", g_slist_length(u->reservation));
        printf("Status: %s\n", u->account_status);
        printf("Criada a: %s\n", u->account_creation);
    }
}



void inserirFlightEmUser(USER u, char * flightid){
    if (g_slist_find(u->flights, flightid) == NULL){
        u->flights = g_slist_prepend(u->flights, g_strdup(flightid));
    }
}


void inserirReservationEmUser(USER u, char * resid, double preco){
    if (g_slist_find(u->reservation, resid) == NULL){
        u->reservation = g_slist_prepend(u->reservation, g_strdup(resid));
        add_total_spent(u, preco);
    }
}
