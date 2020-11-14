#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <pthread.h>





       int matriz2[9][9] = {5, 3, 4, 6, 7, 8, 9, 1, 2,
        	     	   6, 7, 2, 1, 9, 5, 3, 4, 8,
			   1, 9, 8, 3, 4, 2, 5, 6, 7,
			   8, 5, 9, 7, 6, 1, 4, 2, 3,
			   4, 2, 6, 8, 5, 3, 7, 9, 1,
			   7, 1, 3, 9, 2, 4, 8, 5, 6,
			   9, 6, 1, 5, 3, 7, 2, 8, 4,
			   2, 8, 7, 4, 1, 9, 6, 3, 5,
			   3, 4, 5, 2, 8, 6, 1, 7, 9,};

	int matriz[9][9] = {5, 3, 4, 6, 7, 8, 9, 1, 2,
                           6, 7, 2, 1, 9, 5, 3, 4, 8,
                           1, 9, 8, 1, 4, 2, 5, 6, 7,
                           8, 5, 9, 7, 6, 1, 4, 2, 3,
                           4, 2, 6, 8, 5, 3, 3, 9, 1,
                           7, 1, 3, 9, 2, 4, 8, 5, 6,
                           9, 6, 1, 5, 3, 7, 2, 8, 4,
                           2, 8, 7, 4, 1, 2, 6, 3, 5,
                           3, 4, 5, 2, 8, 6, 1, 7, 9,};


int resultados[11] = {1,1,1,1,1,1,1,1,1,1,1};
void *verificadorFilas2(void *row);
void *verificadorColumnas(void *column);
void *verificadorCuadrante(void *cuadrante);



typedef struct 
{

	int row;
	int column;

} parameters;


int main(int argc , char *argv[] ){

	pthread_t filasT;
        pthread_t colT;
	pthread_t cuadrantes[9];
	bool valido;
	int i;
	int j;
	for(i=0;i<9;i++){
		printf("Fila %d: ", i+1);
		for(j=0;j<9;j++){
			printf("  %d",matriz[i][j]);
		}
		printf("\n");
	}

	pthread_create(&filasT, NULL, verificadorFilas2, NULL);
	pthread_create(&colT, NULL, verificadorColumnas, NULL);

		
	int actualHilo = 0;
	for(int i=1; i<10; i = i+3){
		for(int j=1; j<10; j = j+3){
			
			
			parameters *data = (parameters*) malloc(sizeof(parameters));
			data->row=i;
			data->column=j;
			pthread_create(&cuadrantes[actualHilo], NULL, verificadorCuadrante, data);
			actualHilo = actualHilo + 1;
		}
	}

	for(int i=0; i<9;i++){
		pthread_join(cuadrantes[i],NULL);
	}

	
	
	pthread_join(filasT, NULL);
	pthread_join(colT, NULL);
	printf("Resultados: ");
	for(int i=0; i<11;i++){
		if(resultados[i] == 0) { valido = false; }

		printf(" %d", resultados[i]);
	}	
	printf("\n");

	if(valido){
		printf("El Sudoku es valido\n");
	}
	else{
		printf("El Sudoku no es valido\n");
	}

	exit(0);
}

void *verificadorFilas2(void *row){
        int i;
        int j;
        for(i=0;i<9;i++){
                bool comprobacion[9] = {false, false, false, false, false, false, false, false, false};
		
                
                for(j=0;j<9;j++){

			if (comprobacion[matriz[i][j] -1]){	
				printf("Hubo un error en la fila: %d, se repitio el valor de: %d\n", i + 1 , matriz[i][j]);
				resultados[9] = 0;
				pthread_exit(0);
			}

                        comprobacion[matriz[i][j] -1] = true;
		
                        }
               
        }
}

void *verificadorColumnas(void *column){
        int i;
        int j;
        for(i=0;i<9;i++){
                bool comprobacion[9] = {false, false, false, false, false, false, false, false, false};
                for(j=0;j<9;j++){

                        if (comprobacion[matriz[j][i] -1]){
                                printf("Hubo un error en la columna: %d, se repitio el valor de: %d\n", i + 1 , matriz[j][i]);
				resultados[10]=0;
                                pthread_exit(0);

                        }
			
	                comprobacion[matriz[j][i] -1] = true;
                }
                
        }
}

void *verificadorCuadrante(void *cuadrante){
        
	parameters *data = (parameters *)cuadrante;
	int inicioRow = (data -> row) - 1;
        int inicioCol = (data -> column) -1 ;
  	int limiteRow = inicioRow + 3;
	int limiteCol = inicioCol + 3;
	int indiceModificar;

	switch(inicioRow){
		case 0:
			if(inicioCol == 0){ indiceModificar = 0;}

			if(inicioCol == 3){ indiceModificar = 1;}

			if(inicioCol == 6){ indiceModificar = 2;}
			break;

		case 3:
			
                        if(inicioCol == 0){ indiceModificar = 3;}

                        if(inicioCol == 3){ indiceModificar = 4;}

                        if(inicioCol == 6){ indiceModificar = 5;}
			break;

		case 6:	
			if(inicioCol == 0){ indiceModificar = 6;}

                        if(inicioCol == 3){ indiceModificar = 7;}

                        if(inicioCol == 6){ indiceModificar = 8;}
			break;
	
	}

		
        bool comprobacion[9] = {false, false, false, false, false, false, false, false, false};

	for(int i = inicioRow;i<limiteRow;i++){
                
                
               
                for(int j = inicioCol; j<limiteCol;j++){
				
                        if (comprobacion[matriz[i][j] -1]){
                                printf("Hubo un error en el cuadrante que contiene al valor con la fila %d y columna %d, se repitio el valor de: %d\n", i + 1, j + 1 , matriz[i][j]);
				resultados[indiceModificar] = 0;
                                pthread_exit(0);
                        }

                        comprobacion[matriz[i][j] -1] = true;

                        
                        }
               
	}

	
}

