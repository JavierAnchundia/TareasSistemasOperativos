CC = gcc
CFLAGS = -Wall -g -o

all: build main

build: 
	mkdir -p build

main: main.o 
	$(CC) $(CFLAGS) build/mycat main.o

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o build/*
