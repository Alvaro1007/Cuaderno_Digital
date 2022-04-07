#include <stdio.h>
#include <stdlib.h>
#include "matriculas.h"
#include <string.h>

Matricula* getMatriculas (int *arraySize){
	FILE *fich;
	Matricula *data;
	char c;
	int lineas=1,i,size;
	
	if((fich = fopen("Files/Matriculas/matriculas.txt", "r")) == NULL){
		printf("NO SE HA PODIDO ABRIR EL ARCHIVO DE MATRICULAS, SE VA A CREAR UNO NUEVO.\n");
	}
	else{
		fseek(fich,0,SEEK_END);
		size=ftell(fich);
		rewind(fich);
		
		while((c=fgetc(fich))!=EOF){
			if(c=='\n'){
				lineas++;
			}
		}
		rewind(fich);
		
		if((data=(Matricula*)(malloc(lineas * sizeof(Matricula)))) == NULL){
			printf("ERROR A LA HORA DE RESEVAR MEMORIA PARA LA ESTRUCTURA MATRICULAS\n");
		}
		
		for(i=0;i<=lineas;i++){
			fscanf(fich, "%d-%d\n", &(data[i].id_mat), &(data[i].id_alum));
		}
		
		if(size==0)	lineas=0;
	}
	
	fclose(fich);
	*arraySize = lineas;
	
	return data;	
}

void setMatriculas(Matricula* data, int i){
	FILE *fich;
	int lineas;
	
	if((fich = fopen("Files/Matriculas/matriculas.txt", "w")) == NULL){
		printf("ERROR, NO SE ENCUENTRA EL FICHERO DESTINO.\n");
	}
	else{
		for(lineas=0;lineas<i;lineas++){
			fprintf(fich, "%.4d-%.6d", data[lineas].id_mat, data[lineas].id_alum);
			if(lineas+1 < i){
				fprintf(fich,"\n");
			}
		}
	}
	
	fclose(fich);
}


void listarMatriculas(Matricula *data, int arraySize){
	int i;
	
	for(i=0;i<arraySize;i++){
		imprimeMatricula(data[i]);
		printf("\n");
	}
}


void imprimeMatricula(Matricula m){
   printf("\n -Materia:%.4d\n -Alumno: %.6d\n",m.id_mat, m.id_alum);
}


void listaMateriasAlumno(Matricula *data, int arraySize, int id_alum){
	int i;
	
	for(i=0; i<arraySize;i++){
		if(id_alum==data[i].id_alum){
			printf("MATRICULA %d\n",i+1);
			imprimeMatricula(data[i]);
			printf("\n");
		}
	}	
}

void addMatricula(Matricula** matriculas, int* nMatriculas, int id_alum){
	int i;
	
	printf("A%cADIR MATRICULA\n\n", 165);
	
	if(((*matriculas) = realloc((*matriculas), (*nMatriculas+1) * sizeof(Matricula))) == NULL){
			printf("Error, no hay suficiente memoria disponible.\n");
	}
	
	i = (*nMatriculas);
		
	*nMatriculas=*nMatriculas + 1;
	(*matriculas)[i].id_alum = id_alum;
	
	cambiarMateria(i, &*matriculas);
	
	
	
	listaMateriasAlumno(&**matriculas, *nMatriculas, id_alum);
}

void modificarMatricula(Matricula** data, int nMatriculas, int id_alum){
	
	int i, j, aux, encontrado=0, cont=1; 
	
	printf("MODIFICAR MATRICULA\n\n");
	//listamos las matriculas de un alumno 
	listaMateriasAlumno(&**data, nMatriculas, id_alum);
	//seleccionamos la matricula que deseamos modificar mediante un menu basico
	printf("Que matricula desea modificar?: ");
	scanf("%d",&aux);
	fflush(stdin);
	
	cambiarMateria(aux-1, &*data);
}

void eliminarMatricula(Matricula** data, int* nMatriculas, int id_alum){
	int i, aux; 
	printf("ELIMINAR CALIFICACIONES\n\n");
	
	listaMateriasAlumno(&**data, *nMatriculas, id_alum);

	printf("Que matricula desea eliminar?: ");
	scanf("%d",&aux);
	fflush(stdin);
	
	imprimeMatricula((*data)[aux-1]);
	
	printf("\nDesea eliminar la matricula %d?(Escriba '1' si asi lo desea): ",aux);
	scanf("%d",&i);
	fflush(stdin);
	if (i!=1) printf("Operacion cancelada, volviendo al men%c\n", 163);
	else{			
	
		((*data)[aux-1].id_mat) = ((*data)[(*nMatriculas-1)].id_mat);
		((*data)[aux-1].id_alum) = ((*data)[(*nMatriculas-1)].id_alum);
		
	// Reasignamos la memoria reservada y actualizamos el numero de materias
		(*data) = realloc((*data), (*nMatriculas-1) * sizeof(Matricula));
		(*nMatriculas)=(*nMatriculas-1);
	}
}


void cambiarMateria(int id, Matricula** data){
	int materia;
	
	printf("Introduce la nueva materia: ");
	scanf("%d",&materia);
	
	(*data)[id].id_mat = materia;
	printf("\n");	
}





