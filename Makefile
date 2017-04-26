CFLAFS = -g -Wall -Wextra -pedantic -std=c99

all: main

clean:
	rm *.o bin/*

main: main.o fileio.o leapfrog.o
	gcc $(CFLAGS) -o bin/main main.o fileio.o leapfrog.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

fileio.o: fileio.c 
	gcc $(CFLAGS) -c fileio.c

leapfrog.o: leapfrog.c arrayUtils.o arrayUtils.h physUtils.o physUtils.h fileio.o fileio.h
	gcc $(CFLAGS) -c leapfrog.c arrayUtils.o physUtils.o fileio.o

arrayUtils.o: arrayUtils.h
	gcc $(CFLAGS) -c arrayUtils.c

physUtils.o: physUtils.h arrayUtils.o arrayUtils.h
	gcc $(CFLAGS) -c physUtils.h arrayUtils.o


