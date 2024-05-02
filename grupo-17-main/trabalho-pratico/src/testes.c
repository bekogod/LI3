#include "testes.h"


struct Estatisticas {
    int totalArquivos;
    int arquivosIguais;
    int arquivosDiferentes;
};

// Função que compara o conteúdo de dois arquivos linha por linha
int compararLinhasArquivos(const char *path1, const char *path2) {
    FILE *arquivo1 = fopen(path1, "r");
    FILE *arquivo2 = fopen(path2, "r");

    if (arquivo1 == NULL || arquivo2 == NULL) {
        perror("Erro ao abrir os arquivos");
        exit(EXIT_FAILURE);
    }

    char linha1[1024], linha2[1024];
    int numeroLinha = 1;

    // Loop para ler e comparar as linhas dos dois arquivos
    while (fgets(linha1, sizeof(linha1), arquivo1) != NULL && fgets(linha2, sizeof(linha2), arquivo2) != NULL) {
        // Remova o caractere de nova linha, se presente
        linha1[strcspn(linha1, "\n")] = '\0';
        linha2[strcspn(linha2, "\n")] = '\0';

        if (strcmp(linha1, linha2) != 0) {
            fclose(arquivo1);
            fclose(arquivo2);
            printf("Os arquivos diferem na linha %d:\n", numeroLinha);
            printf("%s (Arquivo 1)\n%s (Arquivo 2)\n", linha1, linha2);
            return 0; // Arquivos diferentes
        }
        numeroLinha++;
    }

    // Verifica se um arquivo é mais curto do que o outro
    if (fgets(linha1, sizeof(linha1), arquivo1) != NULL || fgets(linha2, sizeof(linha2), arquivo2) != NULL) {
        fclose(arquivo1);
        fclose(arquivo2);
        printf("Os arquivos diferem na linha %d:\n", numeroLinha);
        printf("%s (Arquivo 1)\n%s (Arquivo 2)\n", linha1, linha2);
        return 0; // Arquivos diferentes
    }

    fclose(arquivo1);
    fclose(arquivo2);

    return 1; // Arquivos iguais
}


// Função que compara os arquivos correspondentes nas duas pastas e gera estatísticas
void compararArquivosEmPastas(const char *pathFolder1, const char *pathFolder2) {
    DIR *dir1 = opendir(pathFolder1);

    if (dir1 == NULL) {
        perror("Erro ao abrir as pastas");
        exit(EXIT_FAILURE);
    }
    struct dirent *entrada1;
    struct dirent *entrada2;
    struct Estatisticas *estatisticas = malloc(sizeof(struct Estatisticas));

    // Inicializa as estatísticas
    estatisticas->totalArquivos = 0;
    estatisticas->arquivosIguais = 0;
    estatisticas->arquivosDiferentes = 0;


    entrada1 = readdir(dir1);
    // Loop para percorrer as entradas das duas pastas
    while (entrada1 != NULL) {
        if (strstr(entrada1->d_name, ".txt") == NULL){
            entrada1 = readdir(dir1);
            continue;
        }
        DIR *dir2 = opendir(pathFolder2);
        while((entrada2 = readdir(dir2)) != NULL){
            if (strcmp(entrada1->d_name, entrada2->d_name) == 0){
                break;
            }
        }
        closedir(dir2);
        // Constrói os caminhos completos dos arquivos nas duas pastas
        char pathArquivo1[1024];
        char pathArquivo2[1024];
        snprintf(pathArquivo1, sizeof(pathArquivo1), "%s/%s", pathFolder1, entrada1->d_name);
        snprintf(pathArquivo2, sizeof(pathArquivo2), "%s/%s", pathFolder2, entrada2->d_name);

        // Incrementa o total de arquivos
        estatisticas->totalArquivos++;

        // Chama a função para comparar os arquivos
        if (compararLinhasArquivos(pathArquivo1, pathArquivo2)) {
            estatisticas->arquivosIguais++;
        } else {
            printf("nome arquivo errado: %s\n\n", entrada1->d_name);
            estatisticas->arquivosDiferentes++;
        }
        entrada1 = readdir(dir1);
    }

    
    printf("\n\nQueries corretas: %d\n", estatisticas->arquivosIguais);
    printf("Queries incorretas: %d\n", estatisticas->arquivosDiferentes);
    double perc_acerto = (estatisticas->arquivosIguais * 100.0) / estatisticas->totalArquivos;
    printf("Percentagem de acerto: %f\n", perc_acerto);
    free(estatisticas);

    closedir(dir1);
}