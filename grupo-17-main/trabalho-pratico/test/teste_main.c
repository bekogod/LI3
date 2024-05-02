#include <stdio.h>
#include <sys/resource.h>
#include "interpretador.h"

int main(int argc, char *argv[]) {
    if (argc == 4) {
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
        compararArquivosEmPastas("./Resultados", argv[3]);
        struct rusage r_usage;
        getrusage(RUSAGE_SELF, &r_usage);
        printf("Memory usage: %ld KB\n", r_usage.ru_maxrss);
        queryTime(getEstatistica(cm));
        freeCM(cm);
    }
    else {
        printf("Numero de argumentos errado\n");
    }

    return 0;
}