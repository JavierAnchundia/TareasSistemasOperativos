CC = gcc
CFLAGS = -Wall -g -o

all: build timeshmm timepipe

build: 
	mkdir -p build

timeshmm: timeshmm.o
	$(CC) $(CFLAGS) build/timeshmm	timeshmm.o -lrt


timepipe: timepipe.o
	$(CC) $(CFLAGS) build/timepipe timepipe.o -lrt

timeshmm.o: timeshmm.c
	$(CC) -c timeshmm.c


timepipe.o: timepipe.c
	$(CC) -c timepipe.c

clean:
	rm *.o build/*

