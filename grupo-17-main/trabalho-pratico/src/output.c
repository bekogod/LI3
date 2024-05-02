#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#define MAX_LINE_SIZE 1024

FILE* openFile(char* path, char* mode){
    FILE * f = fopen(path, mode);
    if(f==NULL){
        perror("Error a abrir ficheiro output");
        return NULL;
    }
    return f;
}

void writeQuery1User(char* name, char* sex, int age, char* country_code,char * passport, int nof, int nor, double total_spent, int formatFlag, FILE* fo, int fot){
    int i=1;
    if(fot == 1){
        if (formatFlag == 1) {
            fprintf(fo, "--- %d ---\n",i);
            fprintf(fo, "name: %s\n", name);
            fprintf(fo, "sex: %s\n", sex);
            fprintf(fo, "age: %d\n", age);
            fprintf(fo, "country_code: %s\n", country_code);
            fprintf(fo, "passport: %s\n", passport);
            fprintf(fo, "number_of_flights: %d\n", nof);
            fprintf(fo, "number_of_reservations: %d\n", nor);
            fprintf(fo, "total_spent: %.3f\n", total_spent);
            i++;
        } 

        else {
            fprintf(fo, "%s;%s;%d;%s;%s;%d;%d;%.3f\n", name, sex, age, country_code, passport, nof, nor, total_spent);
        }
    }
    if(fot == 2){
        printf("--- %d ---\n",i);
        printf("name: %s\n", name);
        printf("sex: %s\n", sex);
        printf("age: %d\n", age);
        printf("country_code: %s\n", country_code);
        printf("passport: %s\n", passport);
        printf("number_of_flights: %d\n", nof);
        printf("number_of_reservations: %d\n", nor);
        printf("total_spent: %.3f\n", total_spent);
    }
}


void writeQuery1FLight(char* airline,char* plane_model,char *origin,char* dest,char * depdate, char * arrdate, int passengers,int delay,int formatFlag, FILE* fo, int fot){
    int i=1;
    if(fot == 1){
        if (formatFlag == 1) {
            fprintf(fo, "--- %d ---\n",i);
            fprintf(fo, "airline: %s\n", airline);
            fprintf(fo, "plane_model: %s\n", plane_model);
            fprintf(fo, "origin: %s\n", origin);
            fprintf(fo, "destination: %s\n", dest);
            fprintf(fo, "schedule_departure_date: %s\n", depdate);
            fprintf(fo, "schedule_arrival_date: %s\n", arrdate);
            fprintf(fo, "passengers: %d\n", passengers);
            fprintf(fo, "delay: %d\n", delay);
            i++;

        } else {
            fprintf(fo, "%s;%s;%s;%s;%s;%s;%d;%d\n", airline, plane_model, origin, dest, depdate, arrdate, passengers, delay);
        }
    }

    if(fot == 2){
        printf("--- %d ---\n",i);
        printf("airline: %s\n", airline);
        printf("plane_model: %s\n", plane_model);
        printf("origin: %s\n", origin);
        printf("destination: %s\n", dest);
        printf("schedule_departure_date: %s\n", depdate);
        printf("schedule_arrival_date: %s\n", arrdate);
        printf("passengers: %d\n", passengers);
        printf("delay: %d\n", delay);
    }

}


void writeQuery1Reservation(char* hotel_id, char* hotel_name, int hotel_stars, char* begin_date, char* end_date, char * includes_breakfast, int nights, double total_price, int formatFlag, FILE* fo, int fot) {
    int i = 1;
    if(fot == 1){
        if (formatFlag == 1) {
            fprintf(fo, "--- %d ---\n",i);
            fprintf(fo, "hotel_id: %s\n",hotel_id);
            fprintf(fo, "hotel_name: %s\n", hotel_name);
            fprintf(fo, "hotel_stars: %d\n",hotel_stars);
            fprintf(fo, "begin_date: %s\n", begin_date);
            fprintf(fo, "end_date: %s\n", end_date);
            fprintf(fo, "includes_breakfast: %s\n",includes_breakfast);
            fprintf(fo, "nights: %d\n",nights);
            fprintf(fo, "total_price: %.3f\n",total_price);
        } else {
            fprintf(fo, "%s;%s;%d;%s;%s;%s;%d;%.3f\n", hotel_id, hotel_name,hotel_stars, begin_date, end_date,includes_breakfast,nights,total_price);
        }
    }
    if(fot == 2){
        printf("--- %d ---\n",i);
        printf("hotel_id: %s\n",hotel_id);
        printf("hotel_name: %s\n", hotel_name);
        printf("hotel_stars: %d\n",hotel_stars);
        printf("begin_date: %s\n", begin_date);
        printf("end_date: %s\n", end_date);
        printf("includes_breakfast: %s\n",includes_breakfast);
        printf("nights: %d\n",nights);
        printf("total_price: %.3f\n",total_price);
    }
}

void writeQuery2(int iteration, char * id, char * data, char * type, int flag, int formatFlag, FILE* fo, int fot){
    if(fot == 1){
        if (formatFlag == 1){
            fprintf(fo, "--- %d ---\n",iteration);
            fprintf(fo, "id: %s\n",id);
            if(flag == 0){
                fprintf(fo, "date: %s\n", data);
                fprintf(fo, "type: %s\n", type);
            }
            else {
                fprintf(fo, "date: %s\n", data);
            }
        } else{
            if (flag == 0) fprintf(fo, "%s;%s;%s\n", id, data, type);
            else fprintf(fo, "%s;%s\n", id, data);
        }
    }

    if(fot == 2){
        printf("--- %d ---\n",iteration);
            printf("id: %s\n",id);
            if(flag == 0){
                printf("date: %s\n", data);
                printf("type: %s\n\n", type);
            }
            else {
                printf("date: %s\n\n", data);
            }
    }
}

void writeQuery3(double class,int formatFlag,FILE *fo, int fot){
    if(fot == 1){
        if(formatFlag == 1){
            fprintf(fo,"--- 1 ---\n");
            fprintf(fo,"rating: %.3f\n",class);
        }
        else{
            fprintf(fo,"%.3f\n",class);
        }
    }
    if(fot == 2){
        printf("--- 1 ---\n");
        printf("rating: %.3f\n",class);
    }
}

void writeQuery4(int i, char* reserva_id, char* date1, char* date2, char* user_id, int rating, double total_price, int formatFlag, FILE* fo, int fot){

    if(fot == 1){
        if(formatFlag == 1){
            fprintf(fo,"--- %d ---\n",i);
            fprintf(fo, "id: %s\n",reserva_id);
            fprintf(fo, "begin_date: %s\n", date1);
            fprintf(fo, "end_date: %s\n",date2);
            fprintf(fo, "user_id: %s\n", user_id);
            fprintf(fo, "rating: %d\n", rating);
            fprintf(fo, "total_price: %.3f\n",total_price);
        }
        else{
            fprintf(fo,"%s;%s;%s;%s;%d;%.3f\n",reserva_id,date1,date2,user_id,rating,total_price);
        }
    }

    if(fot == 2){
        printf("--- %d ---\n",i);
        printf( "id: %s\n",reserva_id);
        printf( "begin_date: %s\n", date1);
        printf( "end_date: %s\n",date2);
        printf( "user_id: %s\n", user_id);
        printf( "rating: %d\n", rating);
        printf( "total_price: %.3f\n\n",total_price);

    }

}

void writeQuery5(int i, char* voo_id, char* data_partida, char* dest, char* airline, char* plane_model, int formatFlag, FILE* fo, int fot){

    if(fot ==1){
        if(formatFlag == 1){
            fprintf(fo,"--- %d ---\n",i);
            fprintf(fo, "id: %s\n",voo_id);
            fprintf(fo, "schedule_departure_date: %s\n", data_partida);
            fprintf(fo, "destination: %s\n",dest);
            fprintf(fo, "airline: %s\n", airline);
            fprintf(fo, "plane_model: %s\n", plane_model);
        }
        else{
            fprintf(fo,"%s;%s;%s;%s;%s\n",voo_id, data_partida, dest, airline, plane_model);
        }
    }

    if(fot == 2){
        printf("--- %d ---\n",i);
        printf( "id: %s\n",voo_id);
        printf( "schedule_departure_date: %s\n", data_partida);
        printf( "destination: %s\n",dest);
        printf( "airline: %s\n", airline);
        printf( "plane_model: %s\n\n", plane_model);

    }

}

void writeQuery6 (int i, char* origin, int n_total_passageiros, int formatFlag, FILE* fo, int fot){

    if(fot == 1){
        if(formatFlag == 1){
            fprintf(fo,"--- %d ---\n",i);
            fprintf(fo, "name: %s\n",origin);
            fprintf(fo, "passengers: %d\n", n_total_passageiros);
        }
        else{
            fprintf(fo,"%s;%d\n", origin, n_total_passageiros);
        }   
    }

    if(fot == 2){
        printf("--- %d ---\n",i);
        printf( "name: %s\n",origin);
        printf( "passengers: %d\n\n", n_total_passageiros);
    }

}

void writeQuery7 (int i, char* origin, int median, int formatFlag, FILE* fo, int fot){

    if(fot ==1){
        if(formatFlag == 1){
            fprintf(fo,"--- %d ---\n",i);
            fprintf(fo, "name: %s\n",origin);
            fprintf(fo, "median: %d\n", median);
        }
        else{
            fprintf(fo,"%s;%d\n", origin, median);
        } 
    }

    if(fot == 2){
        printf("--- %d ---\n",i);
        printf( "name: %s\n",origin);
        printf( "median: %d\n\n", median);

    }

}

void writeQuery8 (int revenue, int formatFlag, FILE* fo,int fot){

    if(fot == 1){
        if(formatFlag == 1){
            fprintf(fo,"--- 1 ---\n");
            fprintf(fo, "revenue: %d\n", revenue);
        }
        else{
            fprintf(fo,"%d\n", revenue);
        } 
    }

    if(fot ==2){
        printf("--- 1 ---\n");
        printf( "revenue: %d\n", revenue);

    }

}

void writeQuery9 (int i, char* user_id, char* name, int formatFlag, FILE* fo, int fot){

    if(fot ==1){
        if(formatFlag == 1){
            fprintf(fo,"--- %d ---\n",i);
            fprintf(fo, "id: %s\n", user_id);
            fprintf(fo, "name: %s\n", name);
        }
        else{
            fprintf(fo,"%s;%s\n", user_id, name);
        }   
    }

    if(fot == 2){
        printf("--- %d ---\n",i);
        printf( "id: %s\n", user_id);
        printf( "name: %s\n\n", name);
    }

}

void writeQuery10 (int i, char* time, int time_type, int n_users, int n_voos, int n_pass, int n_pass_unic, int n_reservas, int formatFlag, FILE* fo,int fot){

    if(fot ==1){
        if(formatFlag == 1){
            fprintf(fo,"--- %d ---\n",i);

            //verificar o type de data (ano, mes, dia)
            // time é um ano
            if (time_type == 0) fprintf(fo, "year: %d\n", atoi(time));
            // time é um mês
            if (time_type == 1) fprintf(fo, "month: %d\n", atoi(time));
            // time é um dia
            if (time_type == 2) fprintf(fo, "day: %d\n", atoi(time));

            fprintf(fo, "users: %d\n", n_users);
            fprintf(fo, "flights: %d\n", n_voos);
            fprintf(fo, "passengers: %d\n", n_pass);
            fprintf(fo, "unique_passengers: %d\n", n_pass_unic);
            fprintf(fo, "reservations: %d\n", n_reservas);
        }
        else{
            fprintf(fo,"%d;%d;%d;%d;%d;%d\n", atoi(time), n_users, n_voos, n_pass, n_pass_unic, n_reservas);
        }  
    }

    if(fot ==2){

        printf("--- %d ---\n",i);
        //verificar o type de data (ano, mes, dia)
        // time é um ano
        if (time_type == 0) printf("year: %d\n", atoi(time));
        // time é um mêsprintf(
        if (time_type == 1) printf("month: %d\n", atoi(time));
        // time é um diaprintf(
        if (time_type == 2) printf("day: %d\n", atoi(time));

        printf("users: %d\n", n_users);
        printf("flights: %d\n", n_voos);
        printf("passengers: %d\n", n_pass);
        printf("unique_passengers: %d\n", n_pass_unic);
        printf("reservations: %d\n\n", n_reservas);

    }
}

void writeEnter(FILE* fo){  
    fprintf(fo,"\n");
}
    
