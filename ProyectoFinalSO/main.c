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
     //Abre el archivo con las direcciones logicas.
    file = fopen(argv[1], "r");
    inicializarTablaPaginas();

    if(!file){  	  
	 printf("Valor del errno: %d\n", errno );
	 fprintf(stderr, "No se puede abrir dicho archivo, el error es: %s\n", strerror(errno)); 	 
         exit (EXIT_FAILURE);
     }

    else{

        //Abre el archivo de destino
        fd_destino = fopen(argv[2],"wt");
        if(!fd_destino){  	  
	        printf("Valor del errno: %d\n", errno );
	        fprintf(stderr, "No se pudo crear dicho archivo, el error es: %s\n", strerror(errno)); 	 
            exit (EXIT_FAILURE);
        }

        // Bucle en donde se llaman los diferentes metodos que generan el resultado deseado
        while( fgets(lector, MAX_CARACTERES_INPUT, file) ){
            int direccionLogica = transformarTipo(lector);
            int pagIndice = (direccionLogica >> 8) & 0x00FF;
            int offset = (direccionLogica & 0x00FF);
            int frameNumber = obtenerFrame(pagIndice);
            int valorEnMemoria = obtenerValorMemoria(frameNumber, offset);
            int direccionFisica = obtenerDireccionFisica(frameNumber, offset);
            guardarArchivo(direccionLogica, direccionFisica, valorEnMemoria);    
            printf("Se genero el archivo de forma exitosa");      
	    }
    fclose(fd_destino); 
    fclose(file);
    exit (EXIT_SUCCESS);
 
    }
 }
 
}

// Metodo usado para transformar los datos leidos desde el archivo de las direcciones logicas
signed int transformarTipo(char *num){     
    char *ptr;
    unsigned int valor;
    valor = strtoul(num, &ptr, 10);
    return valor;
}

// Devuelve el numero del frame de un pageNumber en caso de existir, caso contrario genera un nuevo frame number disponible y lo asigna a ese page number
int obtenerFrame(int pageNumber){

    if(tablaPaginas[pageNumber] != 256){     
        return tablaPaginas[pageNumber];
    }
    
    tablaPaginas[pageNumber] = contadorFrame;
    bringFromStorage (contadorFrame, pageNumber);
    contadorFrame ++;  
    return tablaPaginas[pageNumber];


}

//Permite leer desde el Storage hacia memoria en caso de fallos de pagina, usa el numero de pagina y el numero de frame para lograrlo.
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

    fclose(backing);

}

//Devuelve el valor almacenado en la "memoria fisica" en funcion del numero del frame y el offset
int obtenerValorMemoria(int frameNumber, int offset){
    return memoriaFisica[frameNumber][offset];
}

//Devuelve la Dirccion Fisica en funcion del numero de frame y el offset
int obtenerDireccionFisica(int frameNumber, int offset){
    return ((frameNumber << 8) | offset);
}

//Inicializa la Tabla de Paginas en un valor de 256, se seteo con ese valor ya que habian paginas con valor de "0"
void inicializarTablaPaginas(void){
    int i;
    for (i = 0; i< 256; i++)
        tablaPaginas[i] = 256;
}

//Inicializa la matriz que actua como memoria fisica para este proyecto
void inicializarMemoriaFisica(void){
    int i;
    int j;
    for( i = 0; i < FRAME_NUMBERS; i++){
        for( j = 0; j < TAMANO_PAGINA; j++)
         memoriaFisica[i][j] = 0;
    }
}


//Metodo usado para guardar en el archivo especificado la direccion logica, direccion fisica, y valor obtenido de memoria
void guardarArchivo(int direccionLogica, int direccionFisica, int valorEnMemoria){
        if(fprintf (fd_destino, "Virtual address: %d Physical address: %d Value: %d \n", direccionLogica, direccionFisica, valorEnMemoria) < 0 ){
            printf("Valor del errno: %d\n", errno );
            fprintf(stderr, "No se pudo escribir en el archivo de destino , el error es: %s\n", strerror(errno)); 	 
            exit (EXIT_FAILURE);
        }
}


