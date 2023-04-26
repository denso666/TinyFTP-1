CC = gcc
CFLAGS = -Wall

.PHONY: clean

all: server

server: server.o utils.o rsa.o commands.o
	${CROSS_COMPILE}$(CC) $(CFLAGS) server.o utils.o rsa.o commands.o -o ../server -lpthread

server.o: server.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c server.c -o server.o

commands.o: commands.h commands.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c commands.c -o commands.o

utils.o: utils.h utils.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c utils.c -o utils.o

rsa.o: rsa.h rsa.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c rsa.c -o rsa.o

test: utils.o test.c rsa.o
	clear
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c test.c -o test.o
	${CROSS_COMPILE}$(CC) $(CFLAGS) test.o utils.o rsa.o -o utest -lpthread
	./utest
	rm -rf ./utest
	make clean

clean:
	@rm -rf *.o ../server
	@echo "Cleaned"

