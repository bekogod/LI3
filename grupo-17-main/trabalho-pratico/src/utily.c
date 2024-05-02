#include "utily.h"


//struct auxiliar para Q2
struct q2aux {
    char * id;
    char * data;
    char * hora;
    char * type; // 0 voo / 1 reserva
};

char * getq2auxID(Q2AUX aux){
    char* id = strdup(aux->id);
    return id; 
}

void setq2auxID(Q2AUX aux, char* id){
    aux->id = strdup(id);
}

char * getq2auxdata(Q2AUX aux){
    char * date = strdup(aux->data);
    return date;
}

void setq2auxdata (Q2AUX aux, char * data){
    aux->data = strdup(data);
}

char * getq2auxhora (Q2AUX aux){
    char * hora = strdup(aux->hora);
    return hora;
}

void setq2auxhora (Q2AUX aux, char* hora){
    aux->hora = strdup(hora);
}

char * getq2auxtype (Q2AUX aux) {
    char* type = strdup(aux->type);
    return type;
}

void setq2auxtype (Q2AUX aux, int type){
    if (type == 0) aux->type = strdup("flight");
    else aux->type = strdup("reservation");
}

Q2AUX create_q2aux(char* id, char * data, int type){
    Q2AUX q = malloc(sizeof(struct q2aux));
    
    setq2auxID(q, id);
    //data de uma reserva
    if(type == 1){
        setq2auxdata(q,data);
        setq2auxhora(q, "00:00:00");
    }
    //data de um voo
    else {
        char * aux = strdup(data);
        //removeLastNewLine assim não permite libertar bem a memória do aux
        removeLastNewline(aux);
        char** parametros = malloc(sizeof(char*) * 2); 
        for(int i = 0; i < 2; i++){
            parametros[i] = strdup(strsep(&aux, " "));
        }
        setq2auxdata(q, parametros[0]);
        setq2auxhora(q,parametros[1]);
        free(aux);
        freeArrayStrings(parametros, 2);
    }
    setq2auxtype(q, type);

    free(id);
    free(data);
    return q;
}

void free_Q2aux(Q2AUX q){
    free(q->id);
    free(q->data);
    free(q->hora);
    free(q->type);
    free(q);
}

int compareQ2AUX(const void* a, const void* b) {
    const Q2AUX q1 = *(Q2AUX*)a;
    const Q2AUX q2 = *(Q2AUX*)b;

    char* data2 = getq2auxdata(q2);
    char* data1 = getq2auxdata(q1);

    char* hora2 = getq2auxhora(q2);
    char* hora1 = getq2auxhora(q1);

    char* id2 = getq2auxID(q2);
    char* id1 = getq2auxID(q1);

    int dataCmp = strcmp(data2, data1);

    if (dataCmp == 0) dataCmp = strcmp(hora2, hora1);
    if (dataCmp == 0) dataCmp = strcmp(id1, id2);

    free(data2);
    free(data1);
    free(hora2);
    free(hora1);
    free(id2);
    free(id1);

    return dataCmp;
}

struct keyvalue{
    char* key;
    int value;
};

char* getKey (KEYVALUE k){
    char * key = strdup(k->key);
    return key;
}

void setKey (KEYVALUE k, char* key){
    k->key = key;
}

int getValue (KEYVALUE k){
    return (k->value);
}

void setValue (KEYVALUE k, int value){
    k->value = value;
}

KEYVALUE createKeyValue(char* key, int value){
    KEYVALUE k = malloc(sizeof(struct keyvalue));
    
    setKey(k, key);
    setValue(k, value);

    return k;
}

int compareValues(const void* a, const void* b) {
    const KEYVALUE k1 = *(KEYVALUE*)a;
    const KEYVALUE k2 = *(KEYVALUE*)b;


    int r = getValue(k2) - getValue(k1);

    if (r != 0) return r;

    char* key1 = getKey(k1);
    char* key2 = getKey(k2);
    
    r = strcmp(key1, key2);

    free(key1);
    free(key2);

    return r;
}

void freeKeyValue(KEYVALUE k){
    free(k->key);
    free(k);
}

struct q10aux{
    char* data;
    int n_user;
    int n_flight;
    int n_pass;
    int n_pass_u;
    int n_res;
    GHashTable *unique;
};

char * getData(Q10AUX q){
    char* data = strdup(q->data);
    return data;
}

void setData(Q10AUX q, char* data){
    q->data = strdup(data);
}

int getNUser(Q10AUX q){
    return q->n_user;
}

void setNUser(Q10AUX q, int n_u){
    q->n_user = n_u;
}

int getNFlight(Q10AUX q){
    return q->n_flight;
}

void setNFlight(Q10AUX q, int n_f){
    q->n_flight = n_f;
}

int getNPass(Q10AUX q){
    return q->n_pass;
}

void setNPass(Q10AUX q, int n_p){
    q->n_pass = n_p;
}

int getNPassU(Q10AUX q){
    return q->n_pass_u;
}

void setNPassU(Q10AUX q, int n_p_u){
    q->n_pass_u = n_p_u;
}

int getNRes(Q10AUX q){
    return q->n_res;
}

void setNRes(Q10AUX q, int n_r){
    q->n_res = n_r;
}

GHashTable * getUnique(Q10AUX q){
    return q->unique;
}

void addUnique(Q10AUX q, char* id){
    g_hash_table_add(q->unique, strdup(id));
}


Q10AUX create_q10(char* data){
    Q10AUX q = malloc(sizeof(struct q10aux));

    setData(q, data);
    setNUser(q, 0);
    setNFlight(q,0);
    setNPass(q, 0);
    setNPassU(q, 0);
    setNRes(q, 0);
    q->unique = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);


    return q;
}

int compareQ10(const void* a, const void* b){
    const Q10AUX k1 = *(Q10AUX*)a;
    const Q10AUX k2 = *(Q10AUX*)b;

    char* ano1 = getData(k1);
    char* ano2 = getData(k2);  
    int year1 = atoi(ano1);
    int year2 = atoi(ano2);

    free(ano1);
    free(ano2);
    if (year1 < year2) return -1;
    if (year1 > year2) return 1;
}

void free_q10(void *data){
    Q10AUX q = (Q10AUX)data;
    free(q->data);
    if (q->unique) {
        g_hash_table_destroy(q->unique);
    }
    free(q);
}

char* getYear(const char *date) {
    char* year = (char*) malloc(sizeof(char) * 5);

    strncpy(year, date, 4);
    year[4] = '\0';
    return year;
}

char* getMonth(const char *date) {
    char* month = (char*) malloc(sizeof(char) * 3);

    strncpy(month, date + 5, 2);
    month[2] = '\0';
    return month;
}

char* getDay(const char *date) {
    char* day = (char*) malloc(sizeof(char) * 3);

    strncpy(day, date + 8, 2);
    day[2] = '\0';
    return day;
}




//parsing de uma data
void parseDate(const char *dateStr, int *year, int *month, int *day) {
    sscanf(dateStr, "%d/%d/%d", year, month, day);
}

gpointer copy_string(gconstpointer src, gpointer data) {
    return g_strdup((const char*)src);
}

//calcula a idade dum user
int calculateAge (const char* birthDate){
    int year = 2023;
    int month = 10;
    int day = 1;

    int ano, mes, dia;

    parseDate(birthDate, &ano, &mes, &dia);

    int age = year - ano;

    if(month < mes || (month == mes && day < dia) )
        age--;
    
    return age;
}


/*como usar
    // Assuming the given date is in the format "YYYY/MM/DD"
    const char *dateString = "1990/05/15"; birth_date

    int age = calculateAge(dateString);
*/

//calcula o custo de uma reserva
double calculaPreco(int precoPorNoite, int noites, int city_tax) {
    double preco_total = precoPorNoite * noites + (precoPorNoite * noites * city_tax) / 100.0;
    return preco_total;
}

//calular as noites
int calculateDateDifference(const char* date1, const char* date2) {
    int year1, month1, day1;
    int year2, month2, day2;

    // Parse dateStr1 - older
    parseDate(date1, &year1, &month1, &day1);

    // Parse dateStr2 - most recent
    parseDate(date2, &year2, &month2, &day2);

    // Calculate the date difference in days
    return day2 - day1;
}

/*como usar
    const char *dateStr1 = "2023/01/01";    begin_date
    const char *dateStr2 = "2023/02/15";    end_date

    int difference = calculateDateDifference(dateStr1, dateStr2);

*/
char* get_date_from_datetime(const char* datetime) {
    char* date = malloc(sizeof(char) * 11);
    strncpy(date, datetime, 10);
    date[10] = '\0'; // Ensure null termination

    return date;
}


void parseDateTime(const char *dateTimeStr, int *year, int *month, int *day, int *hour, int *minute, int *second) {
    sscanf(dateTimeStr, "%d/%d/%d %d:%d:%d", year, month, day, hour, minute, second);
}

//calcula o delay
int calculateDateTimeDifference(const char *dateTime1, const char *dateTime2) {
    int year1, month1, day1, hour1, minute1, second1;
    int year2, month2, day2, hour2, minute2, second2;

    // Parse dateTimeStr1 - older 
    parseDateTime(dateTime1, &year1, &month1, &day1, &hour1, &minute1, &second1);

    // Parse dateTimeStr2 - most recent
    parseDateTime(dateTime2, &year2, &month2, &day2, &hour2, &minute2, &second2);

    // Calculate the difference in seconds
    int difference = (hour2 - hour1) * 3600 + (minute2 - minute1) * 60 + (second2 - second1);

    return difference;
}
/*como usar
    const char *dateTimeStr1 = "2023/01/01 12:00:00";   shcedule_departure
    const char *dateTimeStr2 = "2023/01/01 15:30:45";   real_departure

    int difference = calculateDateTimeDifference(dateTimeStr1, dateTimeStr2);

*/

int haveBreakfast(char * breakfast){
    // true = 1, false = 0
    if (!strcasecmp(breakfast,"f")) return 0;
    if (!strcasecmp(breakfast,"false")) return 0;
    if (!strcmp(breakfast,"0")) return 0;
    if (!strcmp(breakfast,"")) return 0;
    if (!strcasecmp(breakfast,"t")) return 1;
    if (!strcasecmp(breakfast,"true")) return 1;
    if (!strcmp(breakfast,"1")) return 1;
}

void freeArrayStrings(char ** array, int tam){
    if(array != NULL){    
        for(int i = 0; i < tam; i++){
            if(array[i] != NULL)
                free(array[i]);
        } 
    }
    free(array);
}


void removeLastNewline(char *str) {
    size_t length = strlen(str);

    // Check if the last character is a newline
    if (length > 0 && str[length - 1] == '\n') {
        // Replace newline character with null terminator
        str[length - 1] = '\0';
    }
}

void writeListToFile(GList *list, FILE *file) {
    GList *current = list;
    while (current != NULL) {
        fprintf(file, "%s\n", (char*)current->data);
        current = g_list_next(current);
    }
}

void freeHashTable(GHashTable* ht){
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, ht);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_free(key);
        g_free(value);
    }
    g_hash_table_destroy(ht);
}

void print_gslist(GSList *list) {
    
    if(list == NULL) printf("(null)");
    
    GSList *iterator = NULL;
    int i = 2;
    for (iterator = list; iterator; iterator = iterator->next) {
        // Assuming the data is a string (char *)
        printf("%s, %p, %d;     ",(char*)iterator->data, iterator,i);
        i++;
    }
    printf("\n");
}

void pathsFich(char* pastaCsv, char* pastaResultados, char** array){
    const char* zero = "/users.csv";
    const char* one = "/users_errors.csv";
    const char* two = "/flights.csv";
    const char* three = "/flights_errors.csv";
    const char* four = "/reservations.csv";
    const char* five = "/reservations_errors.csv";
    const char* six = "/passengers.csv";
    const char* seven = "/passengers_errors.csv";
    array[0] = strdup(pastaCsv);
    array[2] = strdup(pastaCsv);
    array[4] = strdup(pastaCsv);
    array[6] = strdup(pastaCsv);
    array[1] = strdup(pastaResultados);
    array[3] = strdup(pastaResultados);
    array[5] = strdup(pastaResultados);
    array[7] = strdup(pastaResultados);
    array[0] = (char *)realloc(array[0], strlen(array[0]) + strlen(zero) + 1);
    array[1] = (char *)realloc(array[1], strlen(array[1]) + strlen(one) + 1);
    array[2] = (char *)realloc(array[2], strlen(array[2]) + strlen(two) + 1);
    array[3] = (char *)realloc(array[3], strlen(array[3]) + strlen(three) + 1);
    array[4] = (char *)realloc(array[4], strlen(array[4]) + strlen(four) + 1);
    array[5] = (char *)realloc(array[5], strlen(array[5]) + strlen(five) + 1);
    array[6] = (char *)realloc(array[6], strlen(array[6]) + strlen(six) + 1);
    array[7] = (char *)realloc(array[7], strlen(array[7]) + strlen(seven) + 1);
    strcat(array[0], zero);
    strcat(array[1], one);
    strcat(array[2], two);
    strcat(array[3], three);
    strcat(array[4], four);
    strcat(array[5], five);
    strcat(array[6], six);
    strcat(array[7], seven);
}

// Função de comparação para qsort
int comparaAtrasos(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Função para calcular mediana
double calculaMediana(int* atrasos, int numVoos) {
    // Ordenar o vetor de atrasos
    qsort(atrasos, numVoos, sizeof(int), comparaAtrasos);

    // Calcular a mediana
    if (numVoos % 2 == 0) {
        // Se o número de voos for par, calcular a média dos dois valores do meio
        int meio1 = atrasos[numVoos / 2 - 1];
        int meio2 = atrasos[numVoos / 2];
        return (meio1 + meio2) / 2.0;
    } else {
        // Se o número de voos for ímpar, retornar o valor do meio
        return atrasos[numVoos / 2];
    }
}

void diaAnterior(const char *dataString, char *resultado) {
    struct tm data;
    memset(&data, 0, sizeof(struct tm));
    sscanf(dataString, "%d/%d/%d", &data.tm_year, &data.tm_mon, &data.tm_mday);

    // Ajustar os índices dos meses (de 1 a 12)
    data.tm_mon--;

    // Reduzir 1900 do ano, pois a struct tm conta os anos desde 1900
    data.tm_year -= 1900;

    // Adicionar um dia
    time_t timestamp = mktime(&data);
    timestamp -= 24 * 60 * 60;  // Adicionar 24 horas em segundos
    struct tm *novoData = localtime(&timestamp);

    // Formatando o resultado
    sprintf(resultado, "%04d/%02d/%02d", novoData->tm_year + 1900, novoData->tm_mon + 1, novoData->tm_mday);
}

void diaSeguinte(const char *dataString, char *resultado) {
    struct tm data;
    memset(&data, 0, sizeof(struct tm));
    sscanf(dataString, "%d/%d/%d", &data.tm_year, &data.tm_mon, &data.tm_mday);

    // Ajustar os índices dos meses (de 1 a 12)
    data.tm_mon--;

    // Reduzir 1900 do ano, pois a struct tm conta os anos desde 1900
    data.tm_year -= 1900;

    // Adicionar um dia
    time_t timestamp = mktime(&data);
    timestamp += 24 * 60 * 60;  // Adicionar 24 horas em segundos
    struct tm *novoData = localtime(&timestamp);

    // Formatando o resultado
    sprintf(resultado, "%04d/%02d/%02d", novoData->tm_year + 1900, novoData->tm_mon + 1, novoData->tm_mday);
}


// Função para verificar se uma data está no intervalo entre duas outras datas
int dataEstaNoIntervalo(const char* data, const char* inicio, const char* fim) {
    // Converter as strings para estruturas tm
    struct tm data_tm, inicio_tm, fim_tm;
    memset(&data_tm, 0, sizeof(struct tm));
    memset(&inicio_tm, 0, sizeof(struct tm));
    memset(&fim_tm, 0, sizeof(struct tm));

    sscanf(data, "%d/%d/%d", &data_tm.tm_year, &data_tm.tm_mon, &data_tm.tm_mday);
    sscanf(inicio, "%d/%d/%d", &inicio_tm.tm_year, &inicio_tm.tm_mon, &inicio_tm.tm_mday);
    sscanf(fim, "%d/%d/%d", &fim_tm.tm_year, &fim_tm.tm_mon, &fim_tm.tm_mday);

    // Reduzir 1900 do ano, pois a struct tm conta os anos desde 1900
    data_tm.tm_year -= 1900;
    inicio_tm.tm_year -= 1900;
    fim_tm.tm_year -= 1900;

    // Subtrair 1 do mês, pois a struct tm conta os meses de 0 a 11
    data_tm.tm_mon -= 1;
    inicio_tm.tm_mon -= 1;
    fim_tm.tm_mon -= 1;

    // Verificar se a data está no intervalo
    time_t timestamp_data = mktime(&data_tm);
    time_t timestamp_inicio = mktime(&inicio_tm);
    time_t timestamp_fim = mktime(&fim_tm);

    return (timestamp_data >= timestamp_inicio && timestamp_data <= timestamp_fim);
}
void free_inner_hash_table(gpointer data) {
    GHashTable* inner_hash = (GHashTable*)data;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter,inner_hash);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GList *reservation_list = (GList *)value;
        g_list_free(reservation_list);
        g_free(key);
    }
    g_hash_table_destroy(inner_hash);  // Isso libera a hash table interna e seus conteúdos
}