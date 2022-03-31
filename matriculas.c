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
	printf("\n -Id_Materia: %.4d\n -Id_Alumno: %.6d\n",m.id_mat,m.id_alum);
}























