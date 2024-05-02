// userCatalog

#include "userCatalog.h"

struct userCatalog {
    GHashTable * user_by_id;
    GHashTable * user_by_initial;
    GHashTable * user_by_data;
};

USER_CATALOG newUserCatalog(){
    USER_CATALOG uc = malloc(sizeof(struct userCatalog));
    uc -> user_by_id = g_hash_table_new(g_str_hash, g_str_equal);
    uc -> user_by_initial = g_hash_table_new(g_str_hash, g_str_equal);
    uc -> user_by_data = g_hash_table_new(g_str_hash, g_str_equal);
    return uc;
}

// Adiciona um user ao catálogo de users
void insertUserById(GHashTable* catalog, USER user){
    char * id = get_User_id(user);
    g_hash_table_insert(catalog, strdup(id), user);
    free(id);
}


// Adiciona um user a hashtable de user_by_initial
void insertUserByInitial(GHashTable * catalog, USER u) {
    char *user_name = get_User_name(u);
    char * key = g_strdup_printf("%c", user_name[0]);
    if(!g_hash_table_contains(catalog, key)){
        GSList *new_list = NULL;
        g_hash_table_insert(catalog, strdup(key), new_list);
    }
    GSList * list = g_hash_table_lookup(catalog, key);
    list = g_slist_prepend(list, u);
    g_hash_table_replace(catalog, strdup(key), list);
    free(key);
    free(user_name);
}

void insertUserByData(GHashTable * catalog, USER u){
    char* datatime = get_User_creation_date(u);
    char* data = get_date_from_datetime(datatime);
    if(!g_hash_table_contains(catalog, data)){
        GSList* new_list = NULL;
        g_hash_table_insert(catalog, strdup(data), new_list);
    }
    GSList* list = g_hash_table_lookup(catalog, data);
    list = g_slist_prepend(list, u);
    g_hash_table_replace(catalog, strdup(data), list);
    free(datatime);
    free(data);
}


int compareUser(gconstpointer a, gconstpointer b) {
    setlocale(LC_COLLATE, "en_US.UTF-8");
    USER u_a = *(USER*) a;
    USER u_b = *(USER*) b;

    char* nome_a = get_User_name(u_a);
    char* nome_b = get_User_name(u_b);
    char* id_a = get_User_id(u_a);
    char* id_b = get_User_id(u_b);

    
    // Use strcmp to compare the reservation ids
    int name_comparison = strcoll(nome_a, nome_b);

    // If date is the same, compare id's
    if (name_comparison == 0) {
        name_comparison = strcoll(id_a, id_b);
    }

    free(nome_b);
    free(nome_a);
    free(id_a);
    free(id_b);
    
    return name_comparison;    
}

// Retorna um user presente no catálogo com um certo id
USER AUXgetUserById(GHashTable* catalog, char* id){
    return g_hash_table_lookup(catalog, id);
}

void insertUser(USER_CATALOG uc, USER user){
    insertUserById(uc->user_by_id, user);
    insertUserByInitial(uc->user_by_initial, user);
    insertUserByData(uc->user_by_data, user);
}

USER getUserById(USER_CATALOG uc, char* id){
    return AUXgetUserById(uc->user_by_id, id);
}

GHashTable * getUserByInitial(USER_CATALOG uc){
    return uc->user_by_initial;
}

GHashTable* getUserByData(USER_CATALOG uc){
    return uc->user_by_data;
}

void free_user_catalog(USER_CATALOG uc) {
    GHashTableIter iter;
    gpointer key, value;

    // Percorre o user_by_id e libera a memória de cada usuário
    g_hash_table_iter_init(&iter, uc->user_by_id);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        free_User((struct user *)value);
    }

    // Libera a tabela de hash
    g_hash_table_destroy(uc->user_by_id);
    g_hash_table_destroy(uc->user_by_initial);
    g_hash_table_destroy(uc->user_by_data);

    // Libera a própria estrutura userCatalog
    g_free(uc);
}