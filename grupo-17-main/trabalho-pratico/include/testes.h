#ifndef TESTES_H
#define TESTES_H

#include "output.h"

typedef struct Estatisticas;

int compararLinhasArquivos(const char *path1, const char *path2);

void compararArquivosEmPastas(const char *pathFolder1, const char *pathFolder2);

#endif