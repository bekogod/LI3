#ifndef OUTPUT_H
#define OUTPUT_H
#include "utily.h"
FILE* openFile(char* path, char* mode);

void writeQuery1User(char* name, char* sex, int age, char* country_code,char * passport, int nof, int nor, double total_spent, int formatFlag, FILE* fo, int fot);

void writeQuery1FLight(char* airline,char* plane_model,char *origin,char* dest,char * depdate, char * deparr, int passengers,int delay,int formatFlag, FILE* fo, int fot);

void writeQuery1Reservation(char* hotel_id, char* hotel_name, int hotel_stars, char* begin_date, char* end_date, char * includes_breakfast, int nights, double total_price, int formatFlag, FILE* fo, int fot);

void writeQuery2(int iteration, char * id, char * data, char * type, int flag, int formatFlag, FILE* fo, int fot);

void writeQuery3(double class,int formatFlag,FILE *fo, int fot);

void writeQuery4(int i, char* reserva_id, char* date1, char* date2, char* user_id, int rating, double total_price, int formatFlag, FILE* fo, int fot);

void writeQuery5(int i, char* voo_id, char* data_partida, char* dest, char* airline, char* plane_model, int formatFlag, FILE* fo, int fot);

void writeQuery6 (int i, char* origin, int n_total_passageiros, int formatFlag, FILE* fo, int fot);

void writeQuery7 (int i, char* origin, int median, int formatFlag, FILE* fo, int fot);

void writeQuery8 (int revenue, int formatFlag, FILE* fo, int fot);

void writeQuery9 (int i, char* user_id, char* name, int formatFlag, FILE* fo, int fot);

//time_type é para saber se em time estamos a passar um dia, mes ou ano, do nº de argumentos que a Q10 recebe
void writeQuery10 (int i, char* time, int time_type, int n_users, int n_voos, int n_pass, int n_pass_unic, int n_reservas, int formatFlag, FILE* fo, int fot);

void writeEnter(FILE* fo);

#endif