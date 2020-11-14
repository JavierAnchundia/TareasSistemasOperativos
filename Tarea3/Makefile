CC = gcc
CFLAGS = -Wall -g -o

all: build sudoku 

build: 
	mkdir -p build

sudoku: main.o
	$(CC) $(CFLAGS) build/sudoku	main.o -pthread


main.o: main.c
	$(CC) -c main.c


clean:
	rm *.o build/*

