#!/bin/bash
CC=gcc
DEBUG=-Wall -g
DEP=adder.o

adder:${DEP}
	${CC} ${DEBUG} -o adder ${DEP}
adder.o:adder.c
	${CC} ${DEBUG} -c adder.c

clean:
	touch adder
	rm adder
	rm *.o
	
