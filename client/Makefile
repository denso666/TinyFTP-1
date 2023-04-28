CC = gcc
CFLAGS = -Wall
LIB = ../server/src/
PREFIX_CC = cross_
.PHONY: clean

all: ./program/$(PREFIX_CC)librsa.so

./program/$(PREFIX_CC)librsa.so: $(PREFIX_CC)rsa.o
	${CROSS_COMPILE}$(CC) $(CFLAGS) -shared -o ./program/$(PREFIX_CC)librsa.so $(PREFIX_CC)rsa.o

$(PREFIX_CC)rsa.o: $(LIB)rsa.h $(LIB)rsa.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c -fPIC $(LIB)rsa.c -o $(PREFIX_CC)rsa.o

clean:
	@rm -rf *.o ./program/*.so
	@echo "Cleaned"

