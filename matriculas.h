#include <stdio.h>
#ifndef _MATRICULAS_
#define _MATRICULAS

typedef struct{
	int id_mat;
	int id_alum;
}Matricula;

Matricula* getMatriculas (int *arraySize);
void setMatriculas(Matricula* data, int i);

void listarMatriculas(Matricula *data, int arraySize);
void imprimeMatricula(Matricula m);

#endif