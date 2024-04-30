#! /bin/bash

CC= gcc
DEBUG= -Wall -g -lpthread
DEP= server.o init.o exitserver.o  signal_handler.o create_infra.o delete_infra.o process_request.o

server: ${DEP}
	${CC} ${DEBUG} -o server ${DEP}

%.o:%.c
	${CC} ${DEBUF} -c $^

clean:
	sudo touch server
	sudo rm server
	sudo rm *.o
