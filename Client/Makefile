#!/bin/bash
CC=gcc
DEBUG=-Wall -g
DEP=client1.o

c1:${DEP}
	${CC} ${DEBUG} -o c1 ${DEP}
client1.o:client1.c
	${CC} ${DEBUG} -c client1.c

clean:
	touch c1
	pkill -f c1
	rm c1
	rm *.o
	
