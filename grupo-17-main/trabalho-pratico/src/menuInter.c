#include "menuInter.h"
#include <stdlib.h>
#include "queries.h"

void menuHead() {
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*              Welcome to LI3              *\n");
    printf("*              Menu Interativo             *\n");
    printf("*                                          *\n");
    printf("********************************************\n");
}

void clearScreen(){
    printf("\e[1;1H\e[2J");
}



void query1mi(CATALOG_MANAGER cm){

    int f;
    char * of;

    char id[40];
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY1                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Indique um ID, seja de Utilizador, de Voo ou de Reserva, e consequentemente irá receber informações sobre o mesmo!\n");
    printf("ID: ");
    scanf("%s", id);
    printf("\n");
    char *arg1[1] = {id};
    query1(cm,f,1,arg1,of,2);
}




void query2mi(CATALOG_MANAGER cm){
    char id[40];
    char * arg1[2];
    char * of;
    int f;
    int opcao = -1;
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY2                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Indique um ID de Utilizador\n");
    printf("ID de Uilizador: ");
    scanf("%s", id);
    printf("Pretende verificar os Voos, Reservas, ou ambos deste Utilizador? :\n");
    printf("1. Voos\n");
    printf("2. Reservas\n");
    printf("3. Voos e Reservas\n");
    printf("0. Sair!\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    printf("\n");
    arg1[0] = id;
    while (opcao != 0)
        switch (opcao){
            case 1:
                arg1[1]="flights";
                query2(cm,f,2,arg1,of,2);
                opcao = 0;
                break;

            case 2:
                arg1[1]="reservations";
                query2(cm,f,2,arg1,of,2);
                opcao = 0;
                break;
            
            case 3:
                query2(cm,f,1,arg1,of,2);
                opcao = 0;
                break;

            case 0:
                clearScreen();
                exit(0);

            default:
                printf("Opção Inválida, escolha novamente!:\n");
                printf("1. Voos\n");
                printf("2. Reservas\n");
                printf("3. Voos e Reservas\n");
                printf("0. Sair!\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                printf("\n");
                break;
        }
    
 
}




void query3mi(CATALOG_MANAGER cm){
    char id[15];
    int f;
    char * of;
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY3                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Indique um ID de Hotel para obter a classifação média deste mesmo:\n");
    printf("ID: ");
    scanf("%s", id);
    printf("\n");
    char *arg1[1] = {id};
    query3(cm,f,1,arg1,of,2);
}



void query4mi(CATALOG_MANAGER cm){
    char id[15];
    int f;
    char * of;
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY4                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Indique um ID de Hotel lhe serem consquentemente listadas as Reservas deste mesmo, ordenadas pela mais recente para a mais antiga:\n");
    printf("ID: ");
    scanf("%s", id);
    printf("\n");
    char *arg1[1] = {id};
    query4(cm,f,1,arg1,of,2);
}




void query5mi(CATALOG_MANAGER cm){
    int f;
    char * of;

    char aer[4];
    char data1[30];
    char data2[30];
    int c;
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY5                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Indique um Aeroporto, para que lhe possam ser apresentados os Voos com origem neste mesmo, entre as seguintes datas:\n");
    printf("Indique as datas com este estilo : aaaa/MM/dd\n");
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Voos entre: ");
    scanf("%[^\n]s", data1);
    printf("\n");
    while ((c = getchar()) != '\n' && c != EOF);
    printf("E: ");
    scanf("%[^\n]s", data2);
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Do Aeroporto: ");
    scanf("%s", aer);
    printf("\n");
    char *arg1[3] = {aer, data1, data2};
    query5(cm,f,3,arg1,of,2);
}




void query6mi(CATALOG_MANAGER cm){
    int f;
    char * of;

    char ano[5];
    char N[7];
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY6                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Listar os N Aeroportos com mais passageiros num Ano escolhido por si!\n");
    printf("Indique o Ano!\n");
    printf("Ano: ");
    scanf("%s",ano);
    printf("Indique o número de Aeroportos!\n");
    printf("N: ");
    scanf("%s",N);
    printf("\n");
    char *arg1[2] = {ano, N};
    query6(cm,f,2,arg1,of,2);
}




void query7mi(CATALOG_MANAGER cm){

    int f;
    char * of;

    char N[7];
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY7                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Listar os N Aeroportos com pior mediana de atrasos!\n");
    printf("N: ");
    scanf("%s",N);
    printf("\n");
    char *arg1[1] = {N};
    query7(cm,f,1,arg1,of,2);
}




void query8mi(CATALOG_MANAGER cm){
    int f;
    char* of;
    char id[30];
    char data1[15];
    char data2[15];
    int c;
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY8                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Indique um ID de Hotel e duas datas, para que lhe possam ser demonstrado as receitas deste mesmo, no espaço de tempo desejado!\n");
    printf("ID: ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%s", id);
    printf("\n");
    printf("Indique as datas com este estilo : aaaa/MM/dd\n");
    printf("De: ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%s", data1);
    printf("\n");
    printf("A: ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%s", data2);
    printf("\n");
    char *arg1[3] = {id, data1, data2};
    query8(cm,f,3,arg1,of,2);
}





void query9mi(CATALOG_MANAGER cm){
    int f;
    char* of;
    char prefixo[50];
    int c;
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                  QUERY9                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n\n");
    printf("Listar todos os Utilizadores cujo nome começa com prefixo: \n");
    printf("Prefixo: ");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%[^\n]s",prefixo);
    printf("\n");
    char *arg1[1] = {prefixo};
    query9(cm,f,1,arg1,of,2);
}





void query10mi(CATALOG_MANAGER cm){
    int f;
    char* of;
    char ano[6];
    char mes[6];
    char* arg1[2];
    int opcao = -1;
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*                 QUERY10                  *\n");
    printf("*                                          *\n");
    printf("********************************************\n");
    printf("Irão lhe ser apresentadas várias métricas da aplicação\n");
    printf("1. Total\n");
    printf("2. Anual\n");
    printf("3. Mensal\n");
    printf("0. Sair!\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    while (opcao != 0)
        switch (opcao){
            case 1:
                query10(cm,f,0,NULL,of,2);
                opcao = 0;
                break;

            case 2:
                printf("Ano: ");
                scanf("%s",ano);
                arg1[0]= ano;
                query10(cm,f,1,arg1,of,2);
                opcao = 0;
                break;
            
            case 3:
                printf("Ano: ");
                scanf("%s",ano);
                printf("Mês: ");
                scanf("%s",mes);
                arg1[0]= ano;
                arg1[1]= mes;
                query10(cm,f,2,arg1,of,2);
                opcao = 0;
                break;

            case 0:
                clearScreen();
                exit(0);

            default:
                printf("Opção Inválida, escolha novamente!:\n");
                printf("1. Total\n");
                printf("2. Anual\n");
                printf("3. Mensal\n");
                printf("0. Sair!\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
        }    
}




void menu(){
    int escolha = -1;
    char path[100];
    printf("Por favor indique qual o caminho do dataset a processar!\n");
    printf("Path: \n");
    scanf("%s", path);
    char* arrayPaths[8];
    char* pathOutput = strdup("Resultados");
    pathsFich(path, pathOutput, arrayPaths);
    CATALOG_MANAGER cm = newCatalogManager();
    allFilesProcessed(cm, arrayPaths);
    free(pathOutput);
    for(int i = 0; i < 8; i++){
        free(arrayPaths[i]);
    }
    while(escolha != 0){
        menuHead();
        printf("1. Query 1\n");
        printf("2. Query 2\n");
        printf("3. Query 3\n");
        printf("4. Query 4\n");
        printf("5. Query 5\n");
        printf("6. Query 6\n");
        printf("7. Query 7\n");
        printf("8. Query 8\n");
        printf("9. Query 9\n");
        printf("10. Query 10\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        

        switch(escolha){
            case 1:
                query1mi(cm);
                break;

            case 2:
                query2mi(cm);
                break;

            case 3:
                query3mi(cm);
                break;

            case 4:
                query4mi(cm);
                break;

            case 5:
                query5mi(cm);
                break;

            case 6:
                query6mi(cm);
                break;

            case 7:
                query7mi(cm);
                break;

            case 8:
                query8mi(cm);
                break;

            case 9:
                query9mi(cm);
                break;

            case 10:
                query10mi(cm);
                break;

            case 0:
                printf("Obrigado! Até breve!\n");
                clearScreen();
                exit(0);
                break;

            default:
                printf("Escolha Inválida, Tente outra vez!\n");
        }


    }


}
