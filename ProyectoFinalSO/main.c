#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define SIZE_TABLA_PAGINA  256
#define TAMANO_PAGINA 256
#define MAX_CARACTERES_INPUT 7
#define FRAME_NUMBERS 256

signed int transformarTipo(char *num);
int obtenerFrame(int pageNumber);
void inicializarTablaPaginas(void);
void  bringFromStorage (int contadorFrame, int pageNumber);
int obtenerValorMemoria(int frameNumber, int offset);
int obtenerDireccionFisica(int frameNumber, int offset);
void guardarArchivo(int direccionLogica, int direccionFisica, int valorEnMemoria);


int tablaPaginas[SIZE_TABLA_PAGINA] = {0};
char memoriaFisica[FRAME_NUMBERS][TAMANO_PAGINA];
int contadorFrame = 0;
FILE *fd_destino, *file, *backing;



int main(int argc , char *argv[] ){


 char lector[MAX_CARACTERES_INPUT] = {0};

 if (argc != 3){

     fprintf(stderr,"Use: ./pagindemand sourceFile targetFile.\n");
     exit(EXIT_FAILURE);
 
 }


 if( argc == 3){

    file = fopen(argv[1], "r");
    inicializarTablaPaginas();

    if(!file){  	  
	 printf("Valor del errno: %d\n", errno );
	 fprintf(stderr, "No se puede abrir dicho archivo, el error es: %s\n", strerror(errno)); 	 
         exit (EXIT_FAILURE);
     }

    else{

        int contador = 0;
        fd_destino = fopen(argv[2],"wt");
        if(!fd_destino){  	  
	        printf("Valor del errno: %d\n", errno );
	        fprintf(stderr, "No se pudo crear dicho archivo, el error es: %s\n", strerror(errno)); 	 
            exit (EXIT_FAILURE);
        }

        while( fgets(lector, MAX_CARACTERES_INPUT, file) ){
            contador ++;
            int direccionLogica = transformarTipo(lector);
            int pagIndice = (direccionLogica >> 8) & 0x00FF;
            int offset = (direccionLogica & 0x00FF);
            int frameNumber = obtenerFrame(pagIndice);
            int valorEnMemoria = obtenerValorMemoria(frameNumber, offset);
            int direccionFisica = obtenerDireccionFisica(frameNumber, offset);
            guardarArchivo(direccionLogica, direccionFisica, valorEnMemoria);          
	    }
        
     exit (EXIT_SUCCESS);
 
    }
 }
 
}

signed int transformarTipo(char *num){     
    char *ptr;
    unsigned int valor;
    valor = strtoul(num, &ptr, 10);
    return valor;
}


int obtenerFrame(int pageNumber){

    if(tablaPaginas[pageNumber] != 256){     
        return tablaPaginas[pageNumber];
    }
    
    tablaPaginas[pageNumber] = contadorFrame;
    bringFromStorage (contadorFrame, pageNumber);
    contadorFrame ++;  
    return tablaPaginas[pageNumber];


}

void  bringFromStorage (int contadorFrame, int pageNumber){

    backing = fopen("BACKING_STORE.bin","rb");
    if(!backing){  	  
        printf("Valor del errno: %d\n", errno );
        fprintf(stderr, "No se puede abrir el archivo de BACKING_STORE.bin , el error es: %s\n", strerror(errno)); 	 
            exit (EXIT_FAILURE);
        }

     if (fseek(backing, pageNumber * TAMANO_PAGINA, SEEK_SET) != 0){
                printf("Valor del errno: %d\n", errno );
                fprintf(stderr, "Direccion de pagina invalida \n");
                exit (EXIT_FAILURE);
        }
    
        if (fread(memoriaFisica[contadorFrame], sizeof(signed char), TAMANO_PAGINA, backing) == 0){
                printf("Valor del errno: %d\n", errno );
                fprintf(stderr, " Hubo un error al leer el Backing Store \n");
                exit (EXIT_FAILURE);
            }
}

int obtenerValorMemoria(int frameNumber, int offset){
    return memoriaFisica[frameNumber][offset];
}

int obtenerDireccionFisica(int frameNumber, int offset){
    return ((frameNumber << 8) | offset);
}

void inicializarTablaPaginas(void){
    int i;
    for (i = 0; i< 256; i++)
        tablaPaginas[i] = 256;
}

void inicializarMemoriaFisica(void){
    int i;
    int j;
    for( i = 0; i < FRAME_NUMBERS; i++){
        for( j = 0; j < TAMANO_PAGINA; j++)
         memoriaFisica[i][j] = 0;
    }
}



void guardarArchivo(int direccionLogica, int direccionFisica, int valorEnMemoria){
        if(fprintf (fd_destino, "Virtual address: %d Physical address: %d Value: %d \n", direccionLogica, direccionFisica, valorEnMemoria) < 0 ){
            printf("Valor del errno: %d\n", errno );
            fprintf(stderr, "No se pudo escribir en el archivo de destino , el error es: %s\n", strerror(errno)); 	 
            exit (EXIT_FAILURE);
        }
}


