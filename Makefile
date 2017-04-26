CFLAFS = -g -Wall -Wextra -pedantic -std=c99

all: main

clean:
	rm *.o bin/*

main: main.o leapfrog.o physUtils.o arrayUtils.o fileio.o
	gcc $(CFLAGS) -o bin/main main.o leapfrog.o physUtils.o arrayUtils.o fileio.o -lm

main.o: main.c fileio.h leapfrog.h
	gcc $(CFLAGS) -c main.c

physUtils.o: physUtils.c arrayUtils.h
	gcc $(CFLAGS) -c physUtils.c

arrayUtils.o: arrayUtils.c arrayUtils.h
	gcc $(CFLAGS) -c arrayUtils.c

fileio.o: fileio.c
	gcc $(CFLAGS) -c fileio.c

leapfrog.o: leapfrog.c arrayUtils.h physUtils.h fileio.h
	gcc $(CFLAGS) -c leapfrog.c
