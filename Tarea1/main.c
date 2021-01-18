#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc , char *argv[] ){


 char entradaTeclado[16];
 int readBytes;
 int writedBytes;
 int filefd;
 char data[128];

 if (argc > 2){

     fprintf(stderr,"Use: mycat namefile.\n");
     exit(EXIT_FAILURE);
 
 }


 if( argc == 1){
    
     while ( (readBytes = read (0, entradaTeclado, sizeof(entradaTeclado) ) ) > 0){
     	writedBytes = write(1, entradaTeclado, readBytes); 
        if(writedBytes == -1){
		printf("Valor del errno: %d\n", errno );
		fprintf(stderr, "No se puede escribir en la consola, el error es: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
     }
    
     exit (EXIT_SUCCESS);
 
 }

 else{

     filefd = open(argv[1], O_RDONLY, 0 );

     if(filefd == -1){  	  
	 printf("Valor del errno: %d\n", errno );
	 fprintf(stderr, "No se puede abrir dicho archivo, el error es: %s\n", strerror(errno)); 	 
         exit (EXIT_FAILURE);
     }

     else{

         while( (readBytes = read(filefd, data, sizeof(data) ) ) > 0 ){
         	write(1, data, readBytes);
	 	if(writedBytes == -1){
			printf("Valor del errno: %d\n", errno );
                	fprintf(stderr, "No se puede escribir en la consola, el error es: %s\n", strerror(errno));
                      	exit(EXIT_FAILURE);
        	}
	 }
	 
	 close(filefd); 
			
	 if(readBytes == -1){
	        printf("Valor del errno: %d\n", errno );
                fprintf(stderr, "No se puede leer ese archivo, el error es: %s\n", strerror(errno));
		exit (EXIT_FAILURE);
	 }

	 exit (EXIT_SUCCESS);
	 
    }		
 }
}
