//parser.c

#include "validation.h"


//validação de strings
int valid_default (char * string){
    if (strlen(string)) return 1;
    return 0;
}

//validação de datas
int valid_data (char * data){
    char * d = strdup(data);
    char * copy = d;
    //memory leak
    char * token = strdup(strsep(&copy, "/"));
    int n;
    
    //inicio validacao do ano
    if (strlen(token) != 4){
        free(d);
        free(token);
        return 0;
    } 

    for(int i = 0; i < 4; i++){
        if (!isdigit(token[i])) {
            free(d);
            free(token);
            return 0;
        }
    }
    //ano validado
    free(token);
    token = strdup(strsep(&copy, "/"));

    //inicio validacao do mes
    if (strlen(token) != 2){
        free(d);
        free(token);
        return 0;
        }

    for(int i = 0; i < 2; i++){
        if (!isdigit(token[i])) {
            free(token);
            free(d);
            return 0;
        }    
    }
    n = atoi (token);
    if (n > 12){
        free(token);
        free(d);
        return 0;
    }    
    // mes validado
    free(token);
    token = strdup(strsep(&copy, "/"));

    //inicio validacao dia
    if (strlen(token) != 2){
        free(d);
        free(token);
        return 0;
    }    

    for(int i = 0; i < 2; i++){
        if (!isdigit(token[i])){
            free(d);
            free(token);
            return 0;
        }     
    }
    n = atoi (token);
    if (n > 31) {
        free(token);
        free(d);
        return 0;
    }    
    // dia validado
    free(token);
    free(d);
    return 1;
}

// validação de hora
int valid_hora (char * hora){
    char * h = strdup(hora);
    char * copy = h;
    char * token = strdup(strsep(&copy, ":"));
    int n;

    //inicio validacao da hora
    if (strlen(token) != 2){
        free(h);
        free(token);
        return 0;
    }    
    for(int i = 0; i < 2; i++){
        if (!isdigit(token[i])) {
        free(h);
        free(token);
        return 0;
        }    
    }
    n = atoi (token);
    if (n > 23) {
        free(h);
        free(token);
        return 0;
    }    
    //hora validada
    free(token);
    token = strdup(strsep(&copy, ":"));

    //inicio validacao do minuto
    if (strlen(token) != 2) {
        free(h);
        free(token);
        return 0;
    }    
    for(int i = 0; i < 2; i++){
        if (!isdigit(token[i])) {
        free(h);
        free(token);
        return 0;
        }    
    }
    n = atoi (token);
    if (n > 59) {
        free(h);
        free(token);
        return 0;
    }    
    //minuto validado

    free(token);
    token = strdup(strsep(&copy, ":"));

    //inicio validacao do segundo
    if (strlen(token) != 2) {
        free(h);
        free(token);
        return 0;
    }    
    for(int i = 0; i < 2; i++){
        if (!isdigit(token[i])) {
        free(h);
        free(token);
        return 0;
    }    
    }
    n = atoi (token);
    if (n > 59) {
        free(h);
        free(token);
        return 0;
    }    
    //segundo validado
    free(token);
    free(h);
    return 1;
}

// validação de data com hora
int valid_datacomhora(char * data){
    char * d = strdup(data);
    char * copy = d;
    if (strchr(copy, ' ') == NULL) {
        free(d);
        return 0;
    }
    char * token = strdup(strsep(&copy, " "));
    int r;
    
    //validar data
    char * token_aux = strdup(token);
    if (!valid_data(token_aux)) {
        free(token_aux);
        free(token);
        free(d);
        return 0;
    }    

    free(token);
    token = strdup(strsep(&copy, " "));
    free(token_aux);
    token_aux = strdup(token);
    //validar hora
    if (!valid_hora(token_aux)) {
        free(token_aux);
        free(token);
        free(d);
        return 0;
    }

    free(token_aux);    
    free(token);    
    free(d);

    return 1;
}

int valid_email (char * email){
    char * e = strdup(email);
    char * copy = e;
    
    if (strchr(copy, '@') == NULL) {
        free(e);
        return 0;
    }    
    
    
    //validar username
    char * token = strdup(strsep(&copy, "@"));
    
    if (!valid_default(token)) {
        free(e);
        free(token);
        return 0;
    }    
    
    if (strchr(copy, '.') == NULL) {
        free(e);
        free(token);
        return 0;
    }


    //validar domain
    free(token);
    token = strdup(strsep(&copy, "."));
    
    if (!valid_default(token)) {
        free(e);
        free(token);
        return 0;
    }    

    //validar TLD
    free(token);
    token = strdup(strsep(&copy, "."));
    if (strlen(token) < 2) {
        free(e);
        free(token);
        return 0;
    }    

    free(token);
    free(e);
    return 1;
}

int valid_countrycode(char * code){
    if (strlen(code) != 2) return 0;
    
    for(int i = 0; i < 2; i++){
        if (!isalpha(code[i])) return 0;
    }
    return 1;
}

int valid_accountstatus(char * status){
    if (!strcasecmp(status,"active")) return 1;
    if (!strcasecmp(status,"inactive")) return 1;

    return 0;
}

int valid_airport(char * name){
    if (strlen(name) != 3) return 0;
    for(int i = 0; i < 3; i++){
        if (!isalpha(name[i])) return 0;
    }
    
    return 1;
}

int valid_hotelstars(char * stars){
    if (strlen(stars) != 1) return 0;
    if (!isdigit(stars[0])) return 0;
    int n = atoi(stars);
    if (n < 1 || n > 5) return 0;

    return 1;
}

int valid_citytax(char * citytax){
    for(int i = 0; i < strlen(citytax); i++){
        if (!isdigit(citytax[i])) return 0;
    }

    return 1;
}

int valid_pricepernight(char * price){
    //verifica se é um numero inteiro nao negativo
    for(int i = 0; i < strlen(price); i++){
        if (!isdigit(price[i])) return 0;
    }

    //verifica se é positivo
    int n = atoi(price);
    if (n == 0) return 0;

    return 1;
}

int valid_includesbreakfast(char * flag){
    if (!strcasecmp(flag,"f")) return 1;
    if (!strcasecmp(flag,"false")) return 1;
    if (!strcmp(flag,"0")) return 1;
    if (!strcmp(flag,"")) return 1;
    if (!strcasecmp(flag,"t")) return 1;
    if (!strcasecmp(flag,"true")) return 1;
    if (!strcmp(flag,"1")) return 1;

    return 0;
}

int valid_rating(char * rating){
    if (!strcmp(rating,"")) return 1;
    
    if (strlen(rating) != 1) return 0;
    if (!isdigit(rating[0])) return 0;
    int n = atoi(rating);
    if (n < 1 || n > 5) return 0;

    return 1;
}

int valid_timeline(char * before, char * after){
    if (strcmp(before, after) > 0) return 0;
    return 1;
}



int validFlight(char ** parametros, CATALOG_MANAGER cm){
    int valid = 1;
    for (int i= 0; i<12; i++){
        if (valid == 0) break;
        switch (i){
            case 0:
            if(!valid_default(parametros[0])) valid = 0;
            break;

            case 1:
            if(!valid_default(parametros[1])) valid = 0;
            break;

            case 2:
            if(!valid_default(parametros[2])) valid = 0;
            break;

            case 3:
            if(!valid_default(parametros[3])) valid = 0;
            break;

            case 4:
            if(!valid_airport(parametros[4])) valid = 0;
            break;

            case 5:
            if(!valid_airport(parametros[5])) valid = 0;
            break;

            case 6:
            if(!valid_datacomhora(parametros[6])) valid = 0;
            break;

            case 7:
            if(!valid_datacomhora(parametros[7])) valid = 0;
            if(!valid_timeline(parametros[6],parametros[7])) valid = 0;
            break;

            case 8:
            if(!valid_datacomhora(parametros[8])) valid = 0;
            break;

            case 9:
            if(!valid_datacomhora(parametros[9])) valid = 0;
            if(!valid_timeline(parametros[8],parametros[9])) valid = 0;
            break;

            case 10:
            if(!valid_default(parametros[10])) valid = 0;
            break;

            case 11:
            if(!valid_default(parametros[11])) valid = 0;
            break;
   
        }
    }
    if(valid==1){
        FLIGHT f = create_Flight(parametros);

        insertFlightCM(cm,f);
    }
    return valid;
}


//pode haver memory leaks por causa de passageiros
int validPassengers(char * id_voo_atual, GSList * passageiros, GSList ** invalidos, CATALOG_MANAGER cm){
    int r = 1;
    FLIGHT f = getFlight(cm, id_voo_atual);
    //caso o id nao seja valido ou nao exista na hashtable
    if(!(valid_default(id_voo_atual) && f)){ //ver se funciona
        return 0;
    }

    int counter = 0;
    int lugares = get_Flight_seats(f);

    GSList * iterator = passageiros;

    while(iterator != NULL){
        // se o user for valido e existir aumenta o counter
        if((valid_default((char *) iterator->data) && getUser(cm, (char *) iterator->data))) {
            counter++;
            // verifica se o counter é superior ao numero de lugares do voo e por isso invalido e remove o voo da hashtable
            if(counter > lugares){
                r = -1;
                break;
            }
        }
        // o user nao existe ou nao é valido
        else {
            //printf("o user nao existe\n");
            *invalidos = g_slist_prepend(*invalidos, strdup(iterator->data));
        }
        

        iterator = iterator -> next;
    }
    // o voo é valido
    if (r == 1){
        iterator = passageiros;

        //inserir o voo na lista de voos do user
        while(iterator != NULL){
            USER u = getUser(cm, (char*) iterator->data);
            if (u) inserirFlightEmUser(u, id_voo_atual);

            FLIGHT f = getFlight(cm, id_voo_atual);
            if (u) {
                char* user = get_User_id(u);
                inserirPassengerEmFlight(f, user);
                free(user);
            }

            iterator = iterator -> next;
        }

    }

    return r;
}



int validReservation(char ** parametros, CATALOG_MANAGER cm){
    int valid = 1;
    char * user_id =strdup(parametros[1]);

    if (!getUser(cm, user_id)){ //mudar esta linha visto que nao podemos fazer 
        free(user_id);
        return valid = 0;
    }

    for (int i= 0; i<13; i++){
        if (valid == 0) break;
        switch (i){
            case 0:
            if(!valid_default(parametros[0])) valid = 0;
            break;

            case 1:
            if(!valid_default(parametros[1])) valid = 0;
            break;

            case 2:
            if(!valid_default(parametros[2])) valid = 0;
            break;

            case 3:
            if(!valid_default(parametros[3])) valid = 0;
            break;

            case 4:
            if(!valid_hotelstars(parametros[4])) valid = 0;
            break;

            case 5:
            if(!valid_citytax(parametros[5])) valid = 0;
            break;

            case 6:
            if(!valid_default(parametros[6])) valid = 0;
            break;

            case 7:
            if(!valid_data(parametros[7])) valid = 0;
            break;

            case 8:
            if(!valid_data(parametros[8])) valid = 0;
            if(!valid_timeline(parametros[7],parametros[8])) valid = 0;
            break;

            case 9:
            if(!valid_pricepernight(parametros[9])) valid = 0;
            break;

            case 10:
            if(!valid_includesbreakfast(parametros[10])) valid = 0;
            break;

            case 11:
            if(!valid_default(parametros[11])) valid = 0;
            break;

            case 12:
            if(!valid_rating(parametros[12])) valid = 0;
            break;
   
        }
    }
    if(valid==1){

        RESERVATION r  = create_Reservation(parametros);
        insertReservationCM(cm,r);
        USER u = getUser(cm, user_id);
        double custo =  calculaPreco(get_Reservation_price(r), get_Reservation_nights(r), get_Reservation_city_tax(r));
        char * reserid =  get_Reservation_ID(r);
        inserirReservationEmUser(u, reserid, custo);
        free(reserid);
    }
    free(user_id);
    return valid;
}



int validUsers(char ** parametros, CATALOG_MANAGER cm){
    int valid = 1;
    for (int i= 0; i<12; i++){
        if (valid == 0) break;
        switch (i){
            case 0:
            if(!valid_default(parametros[0])) valid = 0;
            break;

            case 1:
            if(!valid_default(parametros[1])) valid = 0;
            break;

            case 2:
            if(!valid_email(parametros[2])) valid = 0;
            break;

            case 3:
            if(!valid_default(parametros[3])) valid = 0;
            break;

            case 4:
            if(!valid_data(parametros[4])) valid = 0;
            break;

            case 5:
            if(!valid_default(parametros[5])) valid = 0;
            break;

            case 6:
            if(!valid_default(parametros[6])) valid = 0;
            break;

            case 7:
            if(!valid_countrycode(parametros[7])) valid = 0;
            break;

            case 8:
            if(!valid_default(parametros[8])) valid = 0;
            break;

            case 9:
            if(!valid_datacomhora(parametros[9])) valid = 0;
            break;

            case 10:
            if(!valid_default(parametros[10])) valid = 0;
            break;

            case 11:
            if(!valid_accountstatus(parametros[11])) valid = 0;
            break;
   
        }
    }
    if(valid==1){
        USER u = create_User(parametros);
        insertUserCM(cm,u);
    }
    return valid;
}