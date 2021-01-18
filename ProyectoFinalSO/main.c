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

void printBytes(void *ptr, int size);
void convertirBinario(int number);

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
            //convertirBinario(direccionLogica);
            //convertirBinario(direccionLogica >> 8);
            int pagIndice = (direccionLogica >> 8) & 0x00FF;
            int offset = (direccionLogica & 0x00FF);
            printf("Valor transformado es %d  ", direccionLogica);
            printf ("Numero de pagina es: %d  ", pagIndice);
            int frameNumber = obtenerFrame(pagIndice);
            printf("Frame: %d ", frameNumber);
            int valorEnMemoria = obtenerValorMemoria(frameNumber, offset);
            int direccionFisica = obtenerDireccionFisica(frameNumber, offset);
            printf("Direccion Fisica: %d ", direccionFisica);
            printf ("El offset es: %d \n ", offset);
            guardarArchivo(direccionLogica, direccionFisica, valorEnMemoria);

            //print_bytes(&direccionLogica, sizeof(direccionLogica));
            //printf("El valor transformado a negativo es %u  ",~direccionLogica);
            //printf("Num %d ,Lidea leida: %s",contador,lector);
            //writedBytes = write(1,lector, MAX_CARACTERES_INPUT);
             

            //unsigned long lector2[1];
            //lector2[0] = ~lector[0];
            //write(1,lector2,readBytes);

         	/*write(1, lector, readBytes);
	 	    if(writedBytes == -1){
			    printf("Valor del errno: %d\n", errno );
                fprintf(stderr, "No se puede escribir en la consola, el error es: %s\n", strerror(errno));
                      	exit(EXIT_FAILURE);
        	}*/
	    }
        printf("Esto: %d", contador);
        printf("Size: %ld", sizeof(lector));
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

void printBytes(void *ptr, int size){

    unsigned char *p = ptr;
    int i;
    for (i=0; i<size; i++) {
        printf("%02hhX ", p[i]);
    }
    printf("\n");
}

int obtenerFrame(int pageNumber){

    if(tablaPaginas[pageNumber] != 256){
        
        printf("El valor del frame es: %d ", tablaPaginas[pageNumber]);
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

    printf("El valor obtenido de la MEMORIA es: %d ", memoriaFisica[frameNumber][offset]);
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

void convertirBinario(int number){
    int n, c, k;
  n = number;
  printf("%d in binary number system is:   ", n);

  for (c = 31; c >= 0; c--)
  {
    k = n >> c;

    if (k & 1)
      printf("1");
    else
      printf("0");
  }

  printf("\n"); 
}

void guardarArchivo(int direccionLogica, int direccionFisica, int valorEnMemoria){
        if(fprintf (fd_destino, "Virtual address: %d Physical address: %d Value: %d \n", direccionLogica, direccionFisica, valorEnMemoria) < 0 ){
            printf("Valor del errno: %d\n", errno );
            fprintf(stderr, "No se pudo escribir en el archivo de destino , el error es: %s\n", strerror(errno)); 	 
            exit (EXIT_FAILURE);
        }
}


