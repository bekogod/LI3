//main.c

#include <stdio.h>

#include "interpretador.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        char* arrayPaths[8];
        char* pathOutput = strdup("Resultados");
        pathsFich(argv[1], pathOutput, arrayPaths);
        CATALOG_MANAGER cm = newCatalogManager();
        allFilesProcessed(cm, arrayPaths);
        free(pathOutput);
        for(int i = 0; i < 8; i++){
            free(arrayPaths[i]);
        }
        executarComandos(cm, argv[2]);
        freeCM(cm);
    }
    else{ if (argc == 1){
            menu();
        }
        else {
            printf("Numero de argumentos errado\n");
        }
    }
    return 0;
}

//programa-principal pathDados pathInput
