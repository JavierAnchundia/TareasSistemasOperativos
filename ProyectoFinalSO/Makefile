CC = gcc
CFLAGS = -Wall -g -o

all: build pagindemand 

build: 
	mkdir -p build

pagindemand: main.o
	$(CC) $(CFLAGS) build/pagindemand	main.o 


main.o: main.c
	$(CC) -c main.c


clean:
	rm *.o build/*

