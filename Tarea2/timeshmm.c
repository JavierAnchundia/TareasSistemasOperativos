#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>

int main(int argc , char *argv[] ){

	
	
	pid_t pid;
	int status;
 	struct timeval startTime;
	struct timeval endTime;
	int shm_fd;
	void* ptr;
	
	const char* name = "memoryShare";
	const int SIZE = 4096;

	pid = fork();

	if (pid == -1){
   		printf("No se pudo hacer fork, intente de nuevo");
 		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		
		int i;	
		char *argv_list[30] = {};
		
		
		

		for( i = 1; i < argc; i++){
			argv_list[i-1]=argv[i];
		}
	 
		argv_list[argc]= NULL;
		
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
		ftruncate(shm_fd, SIZE);
		ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

		
		gettimeofday(&startTime,NULL);
		sprintf(ptr, "%ld", startTime.tv_usec);
		
		execvp(argv[1], argv_list);	
	
	}

	else{
	        if (waitpid(pid, &status, 0) > 0){

			gettimeofday(&endTime,NULL);
			char* temp;
			shm_fd = shm_open(name, O_RDONLY, 0666);
			ptr = mmap (0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	
		
			long tiempo_inicial = strtol((char*)ptr,&temp,10);
			

			printf("Elapsed time: %ld microseconds\n", (endTime.tv_usec - tiempo_inicial));
        		shm_unlink(name);
			printf("Ejecucion Terminada Exitosamente\n");
                	exit(0);
				
		}
		else{
            		printf("Hubo un fallo con el waitpid\n");
			exit(EXIT_FAILURE);
		}
		
	}
	
	exit(0);
}

