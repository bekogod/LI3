#include "interpretador.h"

//Function that gives the number of argumentes
int countArguments(char *str) {
    if(str == NULL || str[0] == '\0' ) return 0;
    int count = 1;
    int insideQuotes = 0;
    // Iterate through the string
    if(str == NULL) return 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        // Check for the beginning of a quoted section
        if (str[i] == '\"' && insideQuotes == 0) {
            insideQuotes = 1;

        }
        // Check for the end of a quoted section
        else if (str[i] == '\"' && insideQuotes==1) {
            insideQuotes = 0;
        }
        // Check for space as a delimiter if not inside quotes
        else if (str[i] == ' ' && insideQuotes==0) {
            ++count;
        }
    }
    return count;
}


// Function to process a string and return an array of arguments
char** processString(char *str, int numArguments) {
    char*  line_copy = str;
    char** args = malloc(sizeof(char*) * numArguments);
    //iterate throw the array
    for(int i=0; i<numArguments; i++){

        char* token;
        //hard part that has to change

        if(line_copy[0] == '\"'){
            token = strdup(strsep(&line_copy, " "));

            char* temp = strdup(strsep(&line_copy, " "));

            char* token_aux = malloc(strlen(token) + 1);
            char* temp_aux = strdup(temp);

            if (strlen(temp_aux) > 0 && temp_aux[strlen(temp_aux) - 1] == '\"')
                temp_aux[strlen(temp_aux) - 1] = '\0';

            strcpy(token_aux, token + 1);

            // Calculate the length needed for the resulting string
            int result_length = strlen(token_aux) + strlen(temp_aux) + 2; // +2 for space and null terminator
            char* result = malloc(result_length);

            // Use snprintf to safely format the string
            snprintf(result, result_length, "%s %s", token_aux, temp_aux);

            free(token);
            free(temp);
            free(token_aux);
            free(temp_aux);

            args[i] = strdup(result);
            free(result);
        }
        else{
            args[i] = strdup( strsep(&line_copy, " "));
        }   
    }
    return args;
}

// Function to parse the query and store information using pointers
void parseQuery(char input[], int *queryId, int *formatFlag, char *arg1) {

    char query[60];
    char flag[2];
    // Using sscanf to parse the input
    int result = sscanf(input, "%s %[^\n]", query, arg1);
    if (query[strlen(query)-1] == 'F') {
        *formatFlag = 1;
        query[strlen(query)-1] = '\0'; // Remove the 'F' from the query string
    } else {
        *formatFlag = 0;
    }

    *queryId = strtol(query, &flag, 10);

    if (result < 2) {
        // If sscanf didn't find any arguments, set arg to an empty string
        arg1[0] = '\0';
    }
}




void executarComandos(CATALOG_MANAGER cm, char * infile){
    FILE * fi = fopen (infile, "r");
    if(fi==NULL){
        perror("Erro a abrir ficheiro input");
        return;
    }
    struct timespec start, end;
    double elapsed;
    size_t sizelinha = 1024;
    char linha [1024];
    char output [1024];
    char outputPath[40];
    int n_command = 1;
    int mode = 1;
    while(fgets(linha, sizelinha,fi)){
        int queryId;
        int formatFlag;
        char arg[60];
        int n_arg;
        sprintf(outputPath, "Resultados/command%d_output.txt", n_command);
        n_command++;
        parseQuery(linha,&queryId,&formatFlag, arg);
        n_arg = countArguments(arg);
        char ** arrayArgs;
        arrayArgs = processString(arg, n_arg);
        switch (queryId){
            case (1):
                clock_gettime(CLOCK_REALTIME, &start);
                query1(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 1, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;
            
            case (2):
                clock_gettime(CLOCK_REALTIME, &start);
                query2(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 2, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;
            
            case (3):
                clock_gettime(CLOCK_REALTIME, &start);
                query3(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 3, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;

            case (4):
                clock_gettime(CLOCK_REALTIME, &start);
                query4(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 4, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;    
            
            case (5):
                clock_gettime(CLOCK_REALTIME, &start);
                query5(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 5, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;
            
            case (6):
                clock_gettime(CLOCK_REALTIME, &start);
                query6(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 6, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;
                

            case (7):
                clock_gettime(CLOCK_REALTIME, &start);
                query7(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 7, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;
            
            case (8):
                clock_gettime(CLOCK_REALTIME, &start);
                query8(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 8, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;

            case (9):
                clock_gettime(CLOCK_REALTIME, &start);
                query9(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 9, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;

            case (10):
                clock_gettime(CLOCK_REALTIME, &start);
                query10(cm, formatFlag, n_arg, arrayArgs, outputPath, mode);
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                addTime(getEstatistica(cm), 10, elapsed);
                freeArrayStrings(arrayArgs, n_arg);
                break;  
        }
        
    }
    
    fclose(fi);

}

/*
int main() {
    char input_with_flag[] = "1f Hello World";
    char input_without_flag[] = "2 ThisIsAnID fights Some Argument with Spaces";

    int queryId1, queryId2;
    char formatFlag1, formatFlag2;
    char arg1[50], arg2[50];

    // Example 1: Format flag exists
    printf("Example 1:\n");
    parseQuery(input_with_flag, &queryId1, &formatFlag1, arg1);

    // Example 2: Format flag doesn't exist
    printf("\nExample 2:\n");
    parseQuery(input_without_flag, &queryId2, &formatFlag2, arg2);

    // You now have access to queryId1, formatFlag1, arg1, queryId2, formatFlag2, arg2 in the main function.

    return 0;
}
*/
