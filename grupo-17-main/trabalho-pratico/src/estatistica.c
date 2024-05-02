#include "estatistica.h"

struct atraso {
    char * aerporto;
    int delay;
};

char * getAerporto (ATRASO a){
    char * aeroporto = strdup(a->aerporto);
    return aeroporto;
}

void setAeroporto (ATRASO a, char* aeroporto){
    a->aerporto = strdup(aeroporto);
}

int getDelay (ATRASO a){
    return (a->delay);
}

void setDelay (ATRASO a, int delay){
    a->delay = delay;
}

struct estatistica{
    int flag;
    GArray *atrasos;
    double total_time[10];
    int n_queries[10];
};

int getFlag (ESTATISTICA e){
    return (e->flag);
}

void setFlag (ESTATISTICA e, int flag){
    e->flag = flag;
}

GArray* getAtrasos(ESTATISTICA e) {
    return e->atrasos;
}

ESTATISTICA newEstatistica() {
    ESTATISTICA e = malloc(sizeof(struct estatistica));
    setFlag(e,0);
    e->atrasos = g_array_new(FALSE, FALSE, sizeof(ATRASO));
    for (int i = 0; i < 10; i++){
        e->total_time[i] = 0.0;
        e->n_queries[i] = 0;
    }
    return e;
}


void addAtraso(ATRASO newAtraso, ESTATISTICA e) {
    if (e != NULL && e->atrasos != NULL) {
        g_array_append_val(e->atrasos, newAtraso);
    }
}

void createAtraso(char* aeroporto, int delay, ESTATISTICA e){
    ATRASO a =  malloc(sizeof(struct atraso));

    setAeroporto(a, aeroporto);
    setDelay(a, delay);

    addAtraso (a, e);
}

void freeEstatistica(ESTATISTICA e) {
    if (e != NULL) {
        if (e->atrasos != NULL) {
            // Loop through each ATRASO in the GArray and free the 'aerporto' string
            for (guint i = 0; i < e->atrasos->len; i++) {
                ATRASO atraso = g_array_index(e->atrasos, ATRASO, i);
                if (atraso->aerporto != NULL) {
                    g_free(atraso->aerporto);
                }
            }
            // Now unref the GArray itself
            g_array_unref(e->atrasos);
        }
        // Finally, free the Estatistica struct
        g_free(e);
    }
}

int compare_atraso(const void* a, const void* b) {
    ATRASO atraso1 = *(ATRASO*)a;
    ATRASO atraso2 = *(ATRASO*)b;

    // First, sort by delay in descending order
    int delay_diff = getDelay(atraso2) - getDelay(atraso1);
    if (delay_diff != 0) {
        return delay_diff;
    }

    char * aero1 = getAerporto(atraso1);
    char * aero2 = getAerporto(atraso2);
    int aero_diff = strcmp(aero1,aero2);
    free(aero1);
    free(aero2);
    return aero_diff;
}

void sortAtrasos(ESTATISTICA e) {
    if (e != NULL && e->atrasos != NULL) {
        g_array_sort(e->atrasos, (GCompareFunc)compare_atraso);
    }
}

void addTime(ESTATISTICA e, int query, double time){
    e->total_time[query-1] += time;
    e->n_queries[query-1] ++;
}

void queryTime(ESTATISTICA e){
    printf("\nTempo médio de execução de cada query\n\n");
    for(int i = 0; i < 10; i++){
        if (e->n_queries[i] !=0){
            double avg_time = e->total_time[i] / e->n_queries[i];
            printf("Query %d: %f\n", i + 1, avg_time);
        }
    }
}