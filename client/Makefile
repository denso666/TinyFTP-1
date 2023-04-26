CC = gcc
CFLAGS = -Wall
LIB = ../server/src/

.PHONY: clean

all: ./program/librsa.so

./program/librsa.so: rsa.o
	${CROSS_COMPILE}$(CC) $(CFLAGS) -shared -o ./program/librsa.so rsa.o

rsa.o: $(LIB)rsa.h $(LIB)rsa.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c -fPIC $(LIB)rsa.c -o rsa.o

clean:
	@rm -rf *.o ./program/*.so
	@echo "Cleaned"

