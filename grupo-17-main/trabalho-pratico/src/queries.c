#include "queries.h"

//QUERY 1
void query1(CATALOG_MANAGER cm, int formatFlag, int N, char *  * arg1,char * ofile, int fot){
    //int fot indica se é para ser criado um ficheiro ou para escrever os resultados num terminal

    if(N<1){
        return;
    }
    FILE* fo;
    if (fot == 1)
        fo = openFile(ofile, "w");
    
    char * id = arg1[0];
    USER u = getUser(cm, id);
    if(u!=NULL){
        char * status = get_User_status(u);
        if(strcasecmp(status,"active")==0){
            char * name = get_User_name (u);
            char * sex = get_User_sex (u);
            int age = get_User_age(u);
            char * country_code = get_User_country(u);
            char * passport = get_User_passport(u);
            int nof = g_slist_length(get_User_flights(u));
            int nor = g_slist_length(get_User_reservation(u));
            double total_spent = get_User_spent(u);
            
            writeQuery1User(name,sex,age,country_code,passport,nof,nor,total_spent,formatFlag,fo,fot);
            free(name);
            free(sex);
            free(country_code);
            free(passport);
        }
        free(status);
        if (fot == 1)
            fclose(fo);
        return;
    }
  
    FLIGHT f = getFlight(cm,id);
    if(f!=NULL){
        char * airline = get_Flight_airline(f);
        char * plane_model = get_Flight_plane_model(f);
        char * origin = get_Flight_origin(f);
        char * dest = get_Flight_destination(f);
        char * depdate = get_Flight_begin_date(f);
        char * arrdate = get_Flight_arrival_date(f);
        int passengers = g_slist_length(get_Flight_passengers(f));
        int delay= get_Flight_delay(f);
        
        writeQuery1FLight(airline,plane_model,origin,dest,depdate,arrdate,passengers,delay,formatFlag,fo,fot);
        if (fot == 1)
            fclose(fo);
        free(airline);
        free(plane_model);
        free(origin);
        free(dest);
        free(depdate);
        free(arrdate);
        return;
    }
    
    RESERVATION r = getReservation(cm,id);
    if (r!=NULL){

        char* includes_breakfast;

        if(get_Reservation_breakfast(r) == 0){
            includes_breakfast = strdup("False");
        }
        else{
            includes_breakfast = strdup("True");
        }
        char * hotel_id = get_Reservation_hotel_id(r);
        char * hotel_name = get_Reservation_hotel_name(r);
        int hotel_stars = get_Reservation_hotel_stars(r);
        char * begin_date = get_Reservation_begin_date(r);
        char * end_date = get_Reservation_end_date(r);
        int nights = get_Reservation_nights(r);
        double total_price= nights * get_Reservation_price(r) + ( (nights * get_Reservation_price(r)) / 100.0 ) * get_Reservation_city_tax(r);

        writeQuery1Reservation(hotel_id,hotel_name,hotel_stars,begin_date,end_date,includes_breakfast,nights,total_price,formatFlag,fo,fot);
        if (fot == 1)
            fclose(fo);
        free(hotel_id);
        free(hotel_name);
        free(begin_date);
        free(end_date);
        free(includes_breakfast);
        return;
    }
    if (fot == 1)
        fclose(fo);
    return;
}



//QUERY 2
void query2(CATALOG_MANAGER cm,int formatFlag, int N, char ** arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = openFile(ofile, "w");
    char * id = arg1[0];
    int flag = 0; //verificar voos e reservas
    //verifica qual tipo de dados tens de devolver flight ou reservation
    if(N != 1) {
        char* type = arg1[1];
        if(!strcmp(type,"flights"))
            flag = 1;   //verificar so voos
        else if(!strcmp(type,"reservations")) flag = 2;  //verificar so reservas  
    }
    
    USER u = getUser(cm, id);
    
    //verificar se so da o apontador ou uma copia
    if(u != NULL ){
        char * status = get_User_status(u);
        if(strcasecmp(status,"active")==0){
            int i = 1;
            FLIGHT f = NULL;
            //verifica os voos
            if(flag == 1){

                GSList * voos =  get_User_flights(u);
                int tam = g_slist_length(voos);
                Q2AUX aux[tam];
                GSList * iterator = NULL;
                int j=0;
                // retirar informacao dos voos
                for (iterator = voos; iterator != NULL; iterator = iterator->next, j++){
                    f = getFlight(cm, (char *) iterator->data);
                    aux[j] = create_q2aux(get_Flight_id(f),get_Flight_begin_date(f),0);
                }
                qsort(aux, tam, sizeof(Q2AUX), compareQ2AUX);
                j = 0;

                for(j; j < tam; j++){
                    //flag é para saber se é preciso imprimir o type ou nao
                    //i e para saber qual é o numero da instancia
                    char* auxID = getq2auxID(aux[j]);
                    char* auxData = getq2auxdata(aux[j]);
                    char* auxType = getq2auxtype(aux[j]);
                    if(i>1 && formatFlag == 1){
                        writeEnter(fo);
                    }
                    writeQuery2(i, auxID, auxData, auxType, flag, formatFlag, fo,fot);
                    free(auxID);
                    free(auxData);
                    free(auxType);
                    free_Q2aux(aux[j]);
                    ++i;
                }
            }

            //verificar as reservas
            if(flag == 2){
                GSList * reservas =  get_User_reservation(u);
                int tam = g_slist_length(reservas);
                Q2AUX aux[tam];
                GSList * iterator = NULL;
                int j=0;
                // retirar informacao das reservas
                for (iterator = reservas; iterator != NULL; iterator = iterator->next, j++){
                    RESERVATION r = getReservation(cm, (char *) iterator->data);
                    aux[j] = create_q2aux(get_Reservation_ID(r),get_Reservation_begin_date(r),1);
                }
                qsort(aux, tam, sizeof(Q2AUX), compareQ2AUX);
                j = 0;

                for(j; j < tam; j++){
                    //flag é para saber se é preciso imprimir o type ou nao
                    //i e para saber qual é o numero da instancia

                    char* auxID = getq2auxID(aux[j]);
                    char* auxData = getq2auxdata(aux[j]);
                    char* auxType = getq2auxtype(aux[j]);
                    if(i>1 && formatFlag == 1){
                        writeEnter(fo);
                    }
                    writeQuery2(i, auxID, auxData, auxType, flag, formatFlag, fo,fot);
                    free(auxID);
                    free(auxData);
                    free(auxType);
                    free_Q2aux(aux[j]);
                    ++i;
                }
            }

            //verificar voos e reservas
            if(flag == 0){
                GSList * voos = get_User_flights(u);
                GSList * reservas =  get_User_reservation(u);
                int tam = g_slist_length(reservas) + g_slist_length(voos);
                Q2AUX aux[tam];
                GSList * iterator = NULL;
                int j=0;
                // informacao das reservas
                for (iterator = reservas; iterator != NULL; iterator = iterator->next, j++){
                    RESERVATION r = getReservation(cm, (char *) iterator->data);
                    aux[j] = create_q2aux(get_Reservation_ID(r),get_Reservation_begin_date(r),1);
                }
                iterator = NULL;
                // informcao dos voos
                for (iterator = voos; iterator != NULL; iterator = iterator->next, j++){
                    FLIGHT f = getFlight(cm, (char *) iterator->data);
                    aux[j] = create_q2aux(get_Flight_id(f),get_Flight_begin_date(f),0);
                }

                qsort(aux, tam, sizeof(Q2AUX), compareQ2AUX);
                j = 0;

                for(j; j < tam; j++){
                    //flag é para saber se é preciso imprimir o type ou nao
                    //i e para saber qual é o numero da instancia
                    char* auxID = getq2auxID(aux[j]);
                    char* auxData = getq2auxdata(aux[j]);
                    char* auxType = getq2auxtype(aux[j]);
                    if(i>1 && formatFlag == 1){
                        writeEnter(fo);
                    }
                    writeQuery2(i, auxID, auxData, auxType, flag, formatFlag, fo,fot);
                    free(auxID);
                    free(auxData);
                    free(auxType);
                    free_Q2aux(aux[j]);
                    ++i;
                }
            }
            free(status);  
        }
    }
    if (fot == 1)
        fclose(fo);
}

//QUERY 3
void query3(CATALOG_MANAGER cm, int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = openFile(ofile, "w");
    if(N<1){
        return ;
    }
    double soma=0;
    double n=0;
    char * hotel_id=arg1[0];
    if (g_hash_table_contains(get_reservation_by_hotelCM(cm), hotel_id)){ //procurar se existe key hotel_id na hash reservation by hotel
        GList* listaRes = g_hash_table_lookup(get_reservation_by_hotelCM(cm), hotel_id); //rbh =  lista de reservas de um hotel
        for (GList *current = listaRes; current != NULL; current = g_list_next(current)){
            RESERVATION r = current->data;
            int rating = get_Reservation_rating(r);
            soma=soma+rating;
            n++;
        }
    }
    double class = (n > 0) ? soma / n : 0.0;
    writeQuery3(class,formatFlag,fo,fot);
    if (fot == 1)
        fclose(fo);
    return ;
}


//QUERY 4
void query4(CATALOG_MANAGER cm,int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = openFile(ofile, "w");
    if (N<1){
        return ;
    }
    int i = 1;
    char * hotel_id= arg1[0];
    if (g_hash_table_contains(get_reservation_by_hotelCM(cm), hotel_id)){
        GList* listaRes = g_hash_table_lookup(get_reservation_by_hotelCM(cm), hotel_id);
        int tam = g_list_length(listaRes);
        RESERVATION res[tam];
        int i = 0;
        GList * iterator = NULL;
        //coloca as reservas num array estatico auxiliar
        for (iterator = listaRes; iterator != NULL; iterator = iterator->next){
            RESERVATION r = iterator->data;
            res[i] = r;
            i++;
        }
        //ordena as reservas
        qsort(res, tam, sizeof(RESERVATION), compare_reservation);

        for (i = 0; i<tam; i++){
            char* reserva_id    = get_Reservation_ID(res[i]);
            char* date1         = get_Reservation_begin_date(res[i]);
            char* date2         = get_Reservation_end_date(res[i]);
            char* user_id       = get_Reservation_User_ID(res[i]);
            int rating          = get_Reservation_rating(res[i]);
            double total_price  = calculaPreco(get_Reservation_price(res[i]), get_Reservation_nights(res[i]), get_Reservation_city_tax(res[i]));
            if(i>0 && formatFlag == 1){
                writeEnter(fo);
            }
            writeQuery4(i+1,reserva_id,date1,date2,user_id,rating,total_price,formatFlag,fo,fot);
            free(reserva_id);
            free(date1);
            free(date2);
            free(user_id);
        }
    }
    if (fot == 1)
        fclose(fo);
    return ;
}

//QUERY 5
void query5(CATALOG_MANAGER cm,int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = openFile(ofile, "w");
    
    char * aero = arg1[0];
    char * inicio = arg1[1];
    char * fim = arg1[2];

    GHashTable* voos = getFlightByOrginByDataCM(cm);

    //obeter a GHashTable interna correspondente ao aeroporto
    GHashTable * voosPorData = g_hash_table_lookup(voos, aero);
    //Verificar se o aeroporto existe na GHashTable principal
    if(voosPorData != NULL) {
        char * data_temp = get_date_from_datetime(fim);
        char * inicio_temp = get_date_from_datetime(inicio);
        char * fim_temp = get_date_from_datetime(fim);
        int j = 1;
        //iterar entre as duas data
        while(dataEstaNoIntervalo(data_temp, inicio_temp, fim_temp)){
            //Obter um GList de voos para uma data especifica
            GList * voosParaData = g_hash_table_lookup(voosPorData, data_temp);
            if (voosParaData != NULL){
                int tam = g_list_length(voosParaData);
                FLIGHT voo[tam];
                GList * iterator = voosParaData;
                int i = 0;
                while(iterator != NULL){
                    FLIGHT f = (FLIGHT) (iterator->data);
                    voo[i] = f;
                    i++;
                    iterator = iterator->next;
                }
                
                qsort(voo, tam, sizeof(FLIGHT), compare_flights);
                for (i = 0; i < tam; i++){
                    //nao é nem a data de inicio ou fim
                    if(!(strcmp(data_temp, inicio_temp) == 0 || strcmp(data_temp, fim_temp) == 0 )){
                        char* voo_id = get_Flight_id(voo[i]);
                        char* data_a = get_Flight_begin_date(voo[i]);
                        char* dest = get_Flight_destination(voo[i]);
                        char* airline = get_Flight_airline(voo[i]);
                        char* plain_m = get_Flight_plane_model(voo[i]);
                        if(j>1 && formatFlag == 1){
                            writeEnter(fo);
                        }
                        writeQuery5(j, voo_id, data_a, dest, airline, plain_m, formatFlag, fo, fot);
                        j++;
                        free(voo_id);
                        free(data_a);
                        free(dest);                    
                        free(airline);
                        free(plain_m);   
                    }
                    else {
                        char *begin_date = get_Flight_begin_date(voo[i]);
                        //caso seja no inicio verificar se a data do voo é superior à da inicio
                        if( (strcmp(data_temp, inicio_temp) == 0) && (strcmp(begin_date, inicio) >= 0) ){
                            char* voo_id = get_Flight_id(voo[i]);
                            char* data_a = get_Flight_begin_date(voo[i]);
                            char* dest = get_Flight_destination(voo[i]);
                            char* airline = get_Flight_airline(voo[i]);
                            char* plain_m = get_Flight_plane_model(voo[i]);
                            if(j>1 && formatFlag == 1){
                                writeEnter(fo);
                            }
                            writeQuery5(j, voo_id, data_a, dest, airline, plain_m, formatFlag, fo, fot);
                            j++;
                            free(voo_id);
                            free(data_a);
                            free(dest);                    
                            free(airline);
                            free(plain_m);  
                        }
                        //caso seja no fim verificar se a data do voo é inferior à de fim
                        if( (strcmp(data_temp, fim_temp) == 0) && (strcmp(fim, begin_date) >= 0) ){
                            char* voo_id = get_Flight_id(voo[i]);
                            char* data_a = get_Flight_begin_date(voo[i]);
                            char* dest = get_Flight_destination(voo[i]);
                            char* airline = get_Flight_airline(voo[i]);
                            char* plain_m = get_Flight_plane_model(voo[i]);
                            if(j>1 && formatFlag == 1){
                                writeEnter(fo);
                            }
                            writeQuery5(j, voo_id, data_a, dest, airline, plain_m, formatFlag, fo, fot);
                            j++;
                            free(voo_id);
                            free(data_a);
                            free(dest);                    
                            free(airline);
                            free(plain_m);  
                        }
                        free(begin_date);
                    }
                }

            }
            diaAnterior(data_temp, data_temp);
        }
        free(data_temp);
        free(inicio_temp);
        free(fim_temp);

    }
    if (fot == 1)
        fclose(fo);
}

int* new_heap_int(int value) {
    int* ptr = malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = value;
    }
    return ptr;
}

//QUERY 6
void query6(CATALOG_MANAGER cm, int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = openFile(ofile, "w");
    GHashTable* n_passageiros= g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    char * ano = arg1[0];
    int n_aeroportos = atoi(arg1[1]);
    char *inicio = malloc(11 * sizeof(char));
    char *fim = malloc(11 * sizeof(char));

    sprintf(inicio, "%s/01/01", ano);
    sprintf(fim, "%s/12/31", ano);

    char data_temp[11];
    int tam = 0;

    GHashTable* aeroPorData = getFlightByOrginByDataCM(cm);
    GHashTableIter iter;
    gpointer key, value;

    //iterar pela hashtable exterior
    g_hash_table_iter_init(&iter, aeroPorData);
    while (g_hash_table_iter_next(&iter, &key, &value)){
        strcpy(data_temp, inicio);

        //iterar pela hashtable interior
        while(dataEstaNoIntervalo(data_temp, inicio, fim)   ){
            //conteudo da hashtable interior
            GList * voos = g_hash_table_lookup(value, data_temp);
            GList * iterator = voos;
            while(iterator != NULL){
                //printf("entrei na glist\n");
                FLIGHT f = (FLIGHT)(iterator->data);
                int n = get_Flight_number_of_passengers(f);
                char * ori = get_Flight_origin(f);
                char * dest = get_Flight_destination(f);

                //aumenta value do aeroporto de partida
                if(g_hash_table_contains(n_passageiros, ori)){
                    int* value_ptr = (int*) g_hash_table_lookup(n_passageiros, ori);
                    *value_ptr += n;
                }
                else{
                    int* new_value = new_heap_int(n);
                    g_hash_table_insert(n_passageiros, strdup(ori), new_value);
                    tam++;
                }
                //aumenta value do aeroporto de saida
                if(g_hash_table_contains(n_passageiros, dest)){
                    int* value_ptr = (int*) g_hash_table_lookup(n_passageiros, dest);
                    *value_ptr += n;
                }
                else{
                    int* new_value = new_heap_int(n);
                    g_hash_table_insert(n_passageiros, strdup(dest), new_value);
                    tam++;
                }
                iterator = iterator->next;
                free(ori);
                free(dest);
            }
            diaSeguinte(data_temp, data_temp);
        }
    }
    KEYVALUE array[tam];
    int j = 0;
    // Initialize the iterator
    g_hash_table_iter_init(&iter, n_passageiros);
    // Iterate over the hash table
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        int* intValue = value;
        array[j] = createKeyValue((char*)key, *intValue);
        j++;
    }
    //ordenar o array
    qsort(array, tam, sizeof(KEYVALUE), compareValues);
    for(j = 0; j < n_aeroportos; j++){
        char* aeroporto = getKey(array[j]);
        int num_p = getValue(array[j]);
        if(j>0 && formatFlag == 1){
            writeEnter(fo);
        }
        writeQuery6(j+1, aeroporto, num_p, formatFlag, fo, fot);
        free(aeroporto);
        free(array[j]);
    }
        
    g_hash_table_destroy(n_passageiros);
    if (fot == 1)
        fclose(fo);
    free(inicio);
    free(fim);
}

//QUERY 7
void query7(CATALOG_MANAGER cm, int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = fopen(ofile,"w");
    //nnc fizemos a query
    if(getFlag(getEstatistica(cm)) == 0){
        GHashTable* hashtable = getFlightByOriginCM(cm);

        // Iterar sobre as chaves (nomes de aeroportos) na hashtable
        GHashTableIter iter;
        gpointer chave, valor;

        g_hash_table_iter_init(&iter, hashtable);
        //analise de um aeroporto

        while (g_hash_table_iter_next(&iter, &chave, &valor)) {

            char* aerporto = strdup((char*)chave);
            int tam = g_list_length((GList*)valor);
            int delay[tam];

            int i = 0;
            GList* listaVoos = (GList*)valor;
            //passar os valores de atraso para o array
            while (listaVoos != NULL) {
                FLIGHT voo = (FLIGHT)listaVoos->data;
                // Calcular atraso em segundos e armazenar no vetor de atrasos
                delay[i] = get_Flight_delay(voo);
                i++;
                listaVoos = g_list_next(listaVoos);
            }

            // Calcular a mediana e armazenar na instância de Aeroporto
            int mediana = calculaMediana(delay, tam);
            //cria a instancia do atraso e ja adiciona à estatistica
            createAtraso(aerporto, mediana, getEstatistica(cm));
            free(aerporto);
        }
        //ja analisou todos os aeroportos
        //vamos ordenar o que temos em estatisticas
        sortAtrasos(getEstatistica(cm));
        setFlag(getEstatistica(cm), 1);
    }

    //Agora que tudo está calculado só falta encaminhar para o output
    int max = atoi(arg1[0]);

    GArray* atrasos = getAtrasos(getEstatistica(cm));

    if (atrasos != NULL) {
        int count = MIN(max, atrasos->len);
        for (int i = 0; i < count; i++) {
            ATRASO a = g_array_index(atrasos, ATRASO, i);
            char* aerporto = getAerporto(a);
            int delay = getDelay(a);
            if(i>0 && formatFlag == 1){
                writeEnter(fo);
            }
            writeQuery7(i+1,aerporto,delay,formatFlag, fo, fot);
            free(aerporto);
        }
    }
    if (fot == 1)
        fclose(fo);
}

//QUERY 8
void query8(CATALOG_MANAGER cm,int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = fopen(ofile,"w");
    char* id_hotel = arg1[0];
    char* inicio = arg1[1];
    char* fim = arg1[2];
    int receitaTotal = 0;

    GHashTable* reservas = getReservationByHotelByData(cm);
    
    // Obtenha a GHashTable interna correspondente ao hotel
    GHashTable *reservasPorData = g_hash_table_lookup(reservas, id_hotel);
    // Verifica se o hotel existe na GHashTable principal
    if (reservasPorData != NULL) {
        char data_temp[11];
        strcpy(data_temp, inicio);
        // Iterar sobre as datas entre inicio e fim
        while(dataEstaNoIntervalo(data_temp, inicio, fim)){
            //Obter uma GList de reservas para uma data específica
            GList *reservasParaData = g_hash_table_lookup(reservasPorData, data_temp);

            if (reservasParaData != NULL) {
                // Iterar sobre as reservas para a data específica
                GList *iterador = reservasParaData;
                while (iterador != NULL) {
                    RESERVATION r = (RESERVATION)(iterador->data);
                    // Calcular a receita para esta reserva
                    receitaTotal += get_Reservation_price(r);

                    // Mover para a próxima reserva
                    iterador = g_list_next(iterador);
                }
            }
            diaSeguinte(data_temp, data_temp);
        }
        writeQuery8(receitaTotal, formatFlag, fo, fot);    
    }

    if (fot == 1)
        fclose(fo);
}


//QUERY 9 
void query9(CATALOG_MANAGER cm,int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = fopen(ofile,"w");
    char * prefix = arg1[0];

    GHashTable* iniciais = getUserByInitialCM(cm);
    GArray *user_array = g_array_new(FALSE, FALSE, sizeof(USER));
    
    char*  key = g_strdup_printf("%c", prefix[0]);;
    GSList* users = g_hash_table_lookup(iniciais, key);
    GSList* iterator = users;

    while(iterator != NULL){
        USER u = (USER) iterator->data;
        char * status = get_User_status(u);
        if(strcasecmp(status,"active")==0){
            char * nome = get_User_name(u);
            if(strncmp(nome, prefix, strlen(prefix)) == 0){
                g_array_append_val(user_array, u);
            }
            free(nome);
        }
        free(status);
        iterator = iterator->next;
    }

    g_array_sort(user_array, (GCompareFunc)compareUser);

    int i = 0;
    for(i; i < (user_array->len); i++){
        USER u = g_array_index(user_array, USER, i);
        char* id = get_User_id(u);
        char* nome = get_User_name(u);
        if(i>0 && formatFlag == 1){
            writeEnter(fo);
        }
        writeQuery9(i+1, id, nome, formatFlag, fo, fot);

        free(id);
        free(nome);
    }
    free(key);
    g_array_free(user_array, TRUE);
    if (fot == 1)
        fclose(fo);

}


//QUERY 10
void query10(CATALOG_MANAGER cm,int formatFlag, int N, char *  * arg1, char * ofile, int fot){
    FILE* fo;
    if (fot == 1)
        fo = fopen(ofile,"w");

    //Guardar a informacao que queremos numa Hashtable em que a chave vai ser o ano, mes ou dia
    //Uma hashtable para contarmos passageiros unicos e tbm reservas
    //basicamente antes de somarmos o passageiro ou a reserva, vamos ver se ela ja existe nesta hashtable
    GHashTable *time_data = g_hash_table_new_full(g_str_hash, g_str_equal, free, free_q10);
     int data_type = 0;
    //Não é dado nnh argumento
    //vai percorrer as hashtable todas
    if(N == 0){
        data_type = 0;
        // USER
        GHashTable* user_table = getUserByDataCM(cm);
        GHashTableIter iter_user;
        gpointer key_user, value_user;
        int i = 0;
        g_hash_table_iter_init(&iter_user, user_table);
        while(g_hash_table_iter_next(&iter_user, &key_user, &value_user)){
            
            char* year = getYear((char *)key_user);
            GSList *list = (GSList *)value_user;
            int n = g_slist_length(list);
            
            Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, year);
            if (info == NULL) {
                char* key_year = strdup(year);
                info = create_q10(year);
                g_hash_table_insert(time_data, key_year, info);
            }

            int u = getNUser(info);
            setNUser(info, n+u);
            free(year);
        }

        //VOOS
        GHashTable* flight_table = getFlightByOrginByDataCM(cm);
        GHashTableIter iter_flight;
        gpointer key_flight, value_flight;

        //iterar pelos aeroportos
        g_hash_table_iter_init(&iter_flight, flight_table);
        while(g_hash_table_iter_next(&iter_flight, &key_flight, &value_flight)){
            GHashTable * voo = (GHashTable*) value_flight;
            GHashTableIter iter_voo;
            gpointer key_voo, value_voo;

            //iterar pelas datas
            g_hash_table_iter_init(&iter_voo, voo);
            while (g_hash_table_iter_next(&iter_voo, &key_voo, &value_voo)) {
                
                char* year = getYear((char *)key_voo);
                GSList *list = (GSList *) value_voo;
                
                //verificar se ja existe uma entrada desse ano
                Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, year);
                if (!info) {
                    info = create_q10(year);
                    g_hash_table_insert(time_data, strdup(year), info);
                }

                GHashTable* unique = getUnique(info);

                //percorrer os voos dessa data nesse aeroporto
                for(GSList* iterator = list; iterator!= NULL; iterator = iterator->next){
                    FLIGHT f = (FLIGHT)iterator->data;
                    char* id = get_Flight_id(f);
                    int nf = getNFlight(info);
                    setNFlight(info, nf+1);
                    GSList* pass = get_Flight_passengers(f);
                    //percorrer os passageiros de um voo
                    for(GSList* aux = pass; aux != NULL; aux = aux->next){
                        char * user = strdup(aux->data);
                        //verificar se é a primeira vez q o passageiro aparece
                        if(!g_hash_table_contains(unique, user)){
                            addUnique(info, user);
                            int up = getNPassU(info);
                            setNPassU(info, up+1);
                        }
                        int p = getNPass(info);
                        setNPass(info, p+1);
                        free(user);
                    }
                    free(id);
                }
                free(year);
            }
        }

        //RESERVAS
        GHashTable* reservation_table = getReservationByHotelByData(cm);
        GHashTableIter iter_reservation;
        gpointer key_reservation, value_reservation;

        //iterar pelos hoteis
        g_hash_table_iter_init(&iter_reservation, reservation_table);
        while(g_hash_table_iter_next(&iter_reservation, &key_reservation, &value_reservation)){
            GHashTable * res = (GHashTable*) value_reservation;
            GHashTableIter iter_res;
            gpointer key_res, value_res;

            //iterar pelas datas
            g_hash_table_iter_init(&iter_res, res);
            while (g_hash_table_iter_next(&iter_res, &key_res, &value_res)) {
                
                char* year = getYear((char *)key_res);
                GSList *list = (GSList *) value_res;
                
                //verificar se ja existe uma entrada desse ano
                Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, year);
                if (!info) {
                    info = create_q10(year);
                    g_hash_table_insert(time_data, strdup(year), info);
                }

                GHashTable* unique = getUnique(info);

                //percorrer as reservas dessa data no hotel
                for(GSList* iterator = list; iterator!= NULL; iterator = iterator->next){
                    RESERVATION r = (RESERVATION)iterator->data;
                    char* id = get_Reservation_ID(r);
                    if(!g_hash_table_contains(unique, id)){
                        addUnique(info, id);
                        int nr = getNRes(info);
                        setNRes(info, nr+1);
                    }
                    free(id);
                }
                free(year);
            }
                
            
        }
    }
    
    //é dado o ano, fazer algo similar à Q6, mas para todas as hashtables
    //depois do ciclo do "estaentreadata", mudar o mes das datas e continuar
    if(N == 1){
        data_type = 1;
        char * ano = arg1[0];
        char *inicio = malloc(11 * sizeof(char));
        char *fim = malloc(11 * sizeof(char));

        sprintf(inicio, "%s/01/01", ano);
        sprintf(fim, "%s/12/31", ano);

        char data_temp[11];
        

        // USER
        
        GHashTable* user_table = getUserByDataCM(cm);
        strcpy(data_temp, inicio);
            
        while(dataEstaNoIntervalo(data_temp, inicio, fim) ){
            char* mes = getMonth(data_temp);

            GSList *list = (GSList *) g_hash_table_lookup(user_table, data_temp);
            if(list != NULL){
                int n = g_slist_length(list);
                Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, mes);
                if (!info) {
                    info = create_q10(mes);
                    g_hash_table_insert(time_data, strdup(mes), info);
                }
                int u = getNUser(info);
                setNUser(info, n+u);
            }
            free(mes);
            diaSeguinte(data_temp, data_temp);
        }
    

        //VOOS
        GHashTable* flight_table = getFlightByOrginByDataCM(cm);
        GHashTableIter iter_flight;
        gpointer key_flight, value_flight;

        //iterar pelos aeroportos
        g_hash_table_iter_init(&iter_flight, flight_table);
        while(g_hash_table_iter_next(&iter_flight, &key_flight, &value_flight)){
            
            strcpy(data_temp, inicio);

            while(dataEstaNoIntervalo(data_temp, inicio, fim) ){
                char* mes = getMonth(data_temp);
                GSList * list =  g_hash_table_lookup(value_flight, data_temp);
                if(list!=NULL){
                    Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, mes);
                    if (!info) {
                        info = create_q10(mes);
                        g_hash_table_insert(time_data, strdup(mes), info);
                    }

                    GHashTable* unique = getUnique(info);

                    //percorrer os voos dessa data nesse aeroporto
                    for(GSList* iterator = list; iterator!= NULL; iterator = iterator->next){
                        FLIGHT f = (FLIGHT)iterator->data;
                        char* id = get_Flight_id(f);
                        int nf = getNFlight(info);
                        setNFlight(info, nf+1);
                        GSList* pass = get_Flight_passengers(f);
                        //percorrer os passageiros de um voo
                        for(GSList* aux = pass; aux != NULL; aux = aux->next){
                            char * user = strdup(aux->data);
                            //verificar se é a primeira vez q o passageiro aparece
                            if(!g_hash_table_contains(unique, user)){
                                addUnique(info, user);
                                int up = getNPassU(info);
                                setNPassU(info, up+1);
                            }
                            int p = getNPass(info);
                            setNPass(info, p+1);
                            free(user);
                        }
                        free(id);
                    }
                }
                free(mes);
                diaSeguinte(data_temp, data_temp);
            }
        }

        //RESERVAS
        GHashTable* reservation_table = getReservationByHotelByData(cm);
        GHashTableIter iter_reservation;
        gpointer key_reservation, value_reservation;

        //iterar pelos hoteis
        g_hash_table_iter_init(&iter_reservation, reservation_table);
        while(g_hash_table_iter_next(&iter_reservation, &key_reservation, &value_reservation)){
            strcpy(data_temp, inicio);
            //iterar pelas datas
            while(dataEstaNoIntervalo(data_temp, inicio, fim) ){
                char* mes = getMonth(data_temp);
                GSList * list = g_hash_table_lookup(value_reservation, data_temp);

                if(list != NULL) {
                    Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, mes);
                    if (!info) {
                        info = create_q10(mes);
                        g_hash_table_insert(time_data, strdup(mes), info);
                    }

                    GHashTable* unique = getUnique(info);
                    //percorrer as reservas dessa data no hotel
                    for(GSList* iterator = list; iterator!= NULL; iterator = iterator->next){
                        RESERVATION r= (RESERVATION)iterator->data;
                        char* id = get_Reservation_ID(r);
                        if(!g_hash_table_contains(unique, id)){
                            addUnique(info, id);
                            int nr = getNRes(info);
                            setNRes(info, nr+1);
                        }
                        free(id);
                    }
                }
                free(mes);
                diaSeguinte(data_temp, data_temp);
            }
        }
        free(inicio);
        free(fim);
    }

    //igual à Q6 com o simples ciclo de "estaentredatas"
    if(N == 2){
        data_type = 2;
        char * ano = arg1[0];
        char * mes = arg1[1];
        char *inicio = malloc(11 * sizeof(char));
        char *fim = malloc(11 * sizeof(char));

        sprintf(inicio, "%s/%s/01", ano, mes);
        sprintf(fim, "%s/%s/31", ano, mes);

        char data_temp[11];

        // USER
        GHashTable* user_table = getUserByDataCM(cm);
        strcpy(data_temp, inicio);
            
        while(dataEstaNoIntervalo(data_temp, inicio, fim) ){
            char* dia = getDay(data_temp);

            GSList *list = (GSList *) g_hash_table_lookup(user_table, data_temp);
            if(list != NULL){
                int n = g_slist_length(list);
                Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, dia);
                if (!info) {
                    info = create_q10(dia);
                    g_hash_table_insert(time_data, strdup(dia), info);
                }
                int u = getNUser(info);
                setNUser(info, n+u);
            }
            free(dia);
            diaSeguinte(data_temp, data_temp);
        }
    

        //VOOS
        GHashTable* flight_table = getFlightByOrginByDataCM(cm);
        GHashTableIter iter_flight;
        gpointer key_flight, value_flight;

        //iterar pelos aeroportos
        g_hash_table_iter_init(&iter_flight, flight_table);
        while(g_hash_table_iter_next(&iter_flight, &key_flight, &value_flight)){
            
            strcpy(data_temp, inicio);

            while(dataEstaNoIntervalo(data_temp, inicio, fim) ){
                char* dia = getDay(data_temp);
                
                GSList * list =  g_hash_table_lookup(value_flight, data_temp);
                if(list!=NULL){
                    Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, dia);
                    if (!info) {
                        info = create_q10(dia);
                        g_hash_table_insert(time_data, strdup(dia), info);
                    }

                    GHashTable* unique = getUnique(info);

                    //percorrer os voos dessa data nesse aeroporto
                    for(GSList* iterator = list; iterator!= NULL; iterator = iterator->next){
                        FLIGHT f = (FLIGHT)iterator->data;
                        char* id = get_Flight_id(f);
                        int nf = getNFlight(info);
                        setNFlight(info, nf+1);
                        GSList* pass = get_Flight_passengers(f);
                        //percorrer os passageiros de um voo
                        for(GSList* aux = pass; aux != NULL; aux = aux->next){
                            char * user = strdup(aux->data);
                            //verificar se é a primeira vez q o passageiro aparece
                            if(!g_hash_table_contains(unique, user)){
                                addUnique(info, user);
                                int up = getNPassU(info);
                                setNPassU(info, up+1);
                            }
                            int p = getNPass(info);
                            setNPass(info, p+1);
                            free(user);
                        }
                        free(id);
                    }
                }
                free(dia);
                diaSeguinte(data_temp, data_temp);
            }
        }

        //RESERVAS
        GHashTable* reservation_table = getReservationByHotelByData(cm);
        GHashTableIter iter_reservation;
        gpointer key_reservation, value_reservation;

        //iterar pelos hoteis
        g_hash_table_iter_init(&iter_reservation, reservation_table);
        while(g_hash_table_iter_next(&iter_reservation, &key_reservation, &value_reservation)){
            strcpy(data_temp, inicio);
            //iterar pelas datas
            while(dataEstaNoIntervalo(data_temp, inicio, fim) ){
                char* dia = getDay(data_temp);
                GSList * list = g_hash_table_lookup(value_reservation, data_temp);

                if(list != NULL) {
                    Q10AUX info = (Q10AUX)g_hash_table_lookup(time_data, dia);
                    if (!info) {
                        info = create_q10(dia);
                        g_hash_table_insert(time_data, strdup(dia), info);
                    }

                    GHashTable* unique = getUnique(info);
                    int len = g_slist_length(list);
                    //percorrer as reservas dessa data no hotel
                    for(GSList* iterator = list; iterator!= NULL; iterator = iterator->next){
                        RESERVATION r= (RESERVATION)iterator->data;
                        char* id = get_Reservation_ID(r);
                        if(!g_hash_table_contains(unique, id)){
                            addUnique(info, id);
                            char* data_ent = get_Reservation_begin_date(r);
                            if(strcmp(data_ent, data_temp) == 0){
                                int nr = getNRes(info);
                                setNRes(info, nr+1);
                            }
                            free(data_ent);
                        }
                        free(id);
                    }
                }
                free(dia);
                diaSeguinte(data_temp, data_temp);
            }
        }
        free(inicio);
        free(fim);
    }

    //nao esquecer que tem de percorrer as 3 hashtables, uma de cada vez, o que nao é muito facil
    //e é uma dos motivos de querer guardar a informacao numa hashtable, assim podemos atualizar a informacao quando quisermos

    GHashTableIter iter;
    gpointer key, value;

    int tam =  g_hash_table_size(time_data);
    Q10AUX aux[tam];
    
    int j= 0;
    g_hash_table_iter_init(&iter, time_data);
    while(g_hash_table_iter_next(&iter, &key, &value)){
        Q10AUX q = (Q10AUX) value;

        aux[j] = q;
        j++;
    }
    int i = 1;
    qsort(aux, tam, sizeof(Q10AUX), compareQ10);
    for(j=0; j<tam;j++){
        char* d = getData(aux[j]); 
        int num_user = getNUser(aux[j]);
        int num_fli = getNFlight(aux[j]);
        int num_pass = getNPass(aux[j]);
        int num_pass_u = getNPassU(aux[j]);
        int num_res = getNRes(aux[j]);
        if(!(num_user == 0 && num_fli == 0 && num_pass == 0 && num_pass_u == 0 && num_res == 0)){
            if(i>1 && formatFlag == 1){
                writeEnter(fo);
            }
            writeQuery10(i, d, data_type, num_user, num_fli, num_pass, num_pass_u, num_res, formatFlag, fo, fot);
            i++;
        }
    }
    g_hash_table_destroy(time_data);
    if (fot == 1)
        fclose(fo);
}





