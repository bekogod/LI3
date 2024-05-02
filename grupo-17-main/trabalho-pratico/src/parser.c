#include "validation.h"


void processUsersFile (CATALOG_MANAGER cm, char * infile, char * outfile){

    //abrir ficheiro users
    FILE * fi = fopen(infile,"r");
    if(fi==NULL){
        perror("Erro a abrir ficheiro input");
        return;
    }

    //criar e abrir ficheiro users_errors
    FILE * fo = fopen(outfile,"w");
    if(fo==NULL){
        perror("Error a abrir ficheiro output");
        return;
    }

    size_t sizelinha = 1024;
    char linha [1024];

    //ler a primeira linha de users
    fgets(linha, sizelinha,fi);
    //escrever a primeira linha em users_errors
    fprintf(fo,"%s",linha);

    //ler restantes linhas
    while(fgets(linha, sizelinha,fi)){
        char * linha_temp = strdup(linha);
        char * line_2 = linha_temp;
        removeLastNewline(linha_temp);
        char** parametros = malloc(sizeof(char*) * 12); 
        
        for(int i = 0; i < 12; i++){
            parametros[i] = strdup(strsep(&line_2, ";"));
        }

        int r = validUsers(parametros, cm);
        //caso a linha não seja valida escreve-a no ficheiro de erros
        if (r == 0) fprintf(fo, "%s", linha);
        freeArrayStrings(parametros, 12);
        free(linha_temp);

    }

    fclose(fi);
    fclose(fo);
}



void processFlightsFile (CATALOG_MANAGER cm, char * infile, char * outfile, GHashTable* idVoo_linhaOriginal){
 
    //abrir ficheiro flights
    FILE * fi = fopen(infile,"r");
    if(fi==NULL){
        perror("Erro a abrir ficheiro input");
        return;
    }


    //criar e abrir ficheiro flights_errors 
    FILE * fo = fopen(outfile,"w");
    if(fo==NULL){
        perror("Error a abrir ficheiro output");
        return;
    }

    size_t sizelinha = 1024;
    char linha [1024];

    //ler a primeira linha de flights
    fgets(linha, sizelinha,fi);
    //escrever a primeira linha em flights_errors
    fprintf(fo,"%s",linha);
  
    //ler restantes linhas
    while(fgets(linha, sizelinha,fi)){
        char * linha_temp = strdup(linha);
        char * line_2 = linha_temp;
        removeLastNewline(linha_temp);
        char** parametros = malloc(sizeof(char*) * 13); 
        
        for(int i = 0; i < 13; i++){
            parametros[i] = strdup(strsep(&line_2, ";"));
        }

        int r = validFlight(parametros, cm);
        //caso a linha não seja valida escreve-a no ficheiro de erros
        if (r == 0) {
            fprintf(fo, "%s", linha);
        }
        
        else g_hash_table_insert(idVoo_linhaOriginal, strdup(parametros[0]), strdup(linha));
        freeArrayStrings(parametros, 13);
        free(linha_temp);

    }

    fclose(fi);
    fclose(fo);
}



void processReservationsFile (CATALOG_MANAGER cm, char * infile, char * outfile){

    //abrir ficheiro reservations
    FILE * fi = fopen(infile,"r");
    if(fi==NULL){
        perror("Erro a abrir ficheiro input");
        return;
    }


    //criar e abrir ficheiro reservations_errors
    FILE * fo = fopen(outfile,"w");
    if(fo==NULL){
        perror("Error a abrir ficheiro output");
        return;
    }

    size_t sizelinha = 1024;
    char linha [1024];
    //ler a primeira linha de reservations
    fgets(linha, sizelinha,fi);
    //escrever a primeira linha em reservations_errors
    fprintf(fo,"%s",linha);

     //ler restantes linhas
    while(fgets(linha, sizelinha,fi)){
        char * linha_temp = strdup(linha);
        char * line_2 = linha_temp;
        removeLastNewline(linha_temp);
        char** parametros = malloc(sizeof(char*) * 14); 
        
        for(int i = 0; i < 14; i++){
            parametros[i] = strdup(strsep(&line_2, ";"));
        }

        int r = validReservation(parametros, cm);
        //caso a linha não seja valida escreve-a no ficheiro de erros
        if (r == 0) fprintf(fo, "%s", linha);
        freeArrayStrings(parametros, 14);
        free(linha_temp);

    }

    fclose(fi);
    fclose(fo);
}



void processPassengersFile (CATALOG_MANAGER cm, char * infile, char * outfilePass, char * outfileVoos, GHashTable* idVoo_linhaOriginal){

    //abrir ficheiro passengers
    FILE * fi = fopen(infile,"r");

    //criar e abrir ficheiro passengers_errors
    FILE * fo = fopen(outfilePass,"w");

    //abrir ficheiro flights_errors
    FILE * fv = fopen(outfileVoos,"a");
    

    size_t sizelinha = 1024;
    char linha [1024];

    char* id_voo_atual;
    id_voo_atual = strdup("0000000000");
    GSList * passageiros = NULL;
    GSList * invalidos = NULL;
    int counter;
    int r;
    
    //ler a primeira linha de passengers
    fgets(linha, sizelinha,fi);
    //escrever a primeira linha em passengers_errors
    fprintf(fo,"%s",linha);
    
    while(fgets(linha, sizelinha, fi)){
        char * linha_temp = strdup(linha);
        char * line_2 = linha_temp;
        removeLastNewline(linha_temp);
        char** parametros = malloc(sizeof(char*) * 2); 

        
        for(int i = 0; i < 2; i++){
            parametros[i] = strdup(strsep(&line_2, ";"));
        }
        

        //sao o mesmo voo
        if(strcmp(parametros[0], id_voo_atual) == 0) { // são do mesmo voo
            passageiros = g_slist_prepend(passageiros, strdup(parametros[1]));
            counter++;
            
        }
        else {
            //primeiro voo a ser lido
            if (strcmp(id_voo_atual, "0000000000") == 0) { 
                free(id_voo_atual);
                id_voo_atual = strdup(parametros[0]);
                //colocar o primeiro passageiro no voo;
                passageiros = g_slist_prepend(passageiros, strdup(parametros[1]));
                counter = 1;
                
            }
            //muda de voo
            else {
                r = validPassengers(id_voo_atual, passageiros, &invalidos, cm);
                
                // escreve no ficheiro de passagerios as entradas invalidas, 
                // caso o voo seja valido ou
                // o id deste nao for valido
                GSList * iterator = NULL;
                if( r==1 ){
                    for (iterator = invalidos; iterator != NULL; iterator = iterator->next){
                        GString *result = g_string_new(NULL);
                        char * user_id = (char*) iterator->data;
                        g_string_append_printf(result, "%s;%s\n", id_voo_atual, user_id);
   
                        fprintf(fo, "%s", result->str);
    
                        g_string_free(result, TRUE);
                    }
                }
                // voo é invalido por causa de nao haver lugares que chegue 
                // vai escrever os restantes voos que nao passaram para a lista de invalidos
                if (r == -1 || r == 0){
                    iterator = NULL;
                    for (iterator = passageiros; iterator != NULL; iterator = iterator->next){
                        GString *result = g_string_new(NULL);
                        char * user_id = (char*) iterator->data;
                        g_string_append_printf(result, "%s;%s\n", id_voo_atual, user_id);

                        fprintf(fo, "%s", result->str);

                        g_string_free(result, TRUE);
                    }
                }
                // o voo é invalido
                // -1 = nao haver lugares que chegue 
                // 0 =  o id nao é valido
                if (r == -1 || r == 0){
                    //caso o voo nao seja valido por causa do id
                    if(g_hash_table_contains(idVoo_linhaOriginal, id_voo_atual)){
                        char * linha_voo_corrupto = strdup(g_hash_table_lookup(idVoo_linhaOriginal, id_voo_atual));
                        fprintf(fv, "%s", linha_voo_corrupto);
                        removeFlightCM(cm, id_voo_atual);
                        free(linha_voo_corrupto);
                    }
                }
                //iniciar o novo voo
                free(id_voo_atual);
                id_voo_atual = strdup(parametros[0]);

                g_slist_free_full(passageiros, g_free);
                g_slist_free_full(invalidos, g_free);
                passageiros = NULL;
                passageiros = g_slist_prepend(passageiros, strdup(parametros[1]));
                invalidos = NULL;
                counter = 1;
            }
        }
        freeArrayStrings(parametros, 2);
        free(linha_temp);

    }
    // verificar o ultimo voo
    //como melhorar???
    r = validPassengers(id_voo_atual, passageiros, &invalidos, cm);
    // escreve no ficheiro de passagerios as entradas invalidas, 
    // caso o voo seja valido ou
    // o id deste nao for valido
    GSList * iterator = NULL;
    if( r==1 ){
        for (iterator = invalidos; iterator != NULL; iterator = iterator->next){
            GString *result = g_string_new(NULL);
            char * user_id = (char*) iterator->data;
            g_string_append_printf(result, "%s;%s\n", id_voo_atual, user_id);
            fprintf(fo, "%s", result->str);
            g_string_free(result, TRUE);
        }
    }
    // voo é invalido por causa de nao haver lugares que chegue 
    // vai escrever os restantes voos que nao passaram para a lista de invalidos
    if (r == -1 || r == 0){
        iterator = NULL;
        for (iterator = passageiros; iterator != NULL; iterator = iterator->next){
            GString *result = g_string_new(NULL);
            char * user_id = (char*) iterator->data;
            g_string_append_printf(result, "%s;%s\n", id_voo_atual, user_id);
            fprintf(fo, "%s", result->str); 
            g_string_free(result, TRUE);
        }
    }
    // o voo é invalido
    // -1 = nao haver lugares que chegue 
    // 0 =  o id nao é valido
    if (r == -1 || r == 0){
        //caso o voo nao seja valido por causa do id
        if(g_hash_table_contains(idVoo_linhaOriginal, id_voo_atual)){
            char * linha_voo_corrupto = strdup(g_hash_table_lookup(idVoo_linhaOriginal, id_voo_atual));
            fprintf(fv, "%s", linha_voo_corrupto);
            removeFlightCM(cm, id_voo_atual);
            free(linha_voo_corrupto);
        }
    }

    fclose(fi);
    fclose(fo);
    //libertação de memoria
    free(id_voo_atual);
    g_slist_free_full(passageiros, g_free);
    g_slist_free_full(invalidos, g_free);
}
