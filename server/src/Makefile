CC = gcc
CFLAGS = -Wall
PREFIX_CC = cross_

.PHONY: clean

all: $(PREFIX_CC)server

$(PREFIX_CC)server: $(PREFIX_CC)server.o $(PREFIX_CC)utils.o $(PREFIX_CC)rsa.o $(PREFIX_CC)commands.o
	${CROSS_COMPILE}$(CC) $(CFLAGS) $^ -o ../$(PREFIX_CC)server -lpthread

$(PREFIX_CC)server.o: server.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c server.c -o $@

$(PREFIX_CC)commands.o: commands.h commands.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c commands.c -o $@

$(PREFIX_CC)utils.o: utils.h utils.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c utils.c -o $@

$(PREFIX_CC)rsa.o: rsa.h rsa.c
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c rsa.c -o $@

test: $(PREFIX_CC)utils.o $(PREFIX_CC)test.c $(PREFIX_CC)rsa.o
	clear
	${CROSS_COMPILE}$(CC) $(CFLAGS) -c test.c -o test.o
	${CROSS_COMPILE}$(CC) $(CFLAGS) $^ -o utest -lpthread
	./utest
	rm -rf ./utest
	make clean

clean:
	@rm -rf *.o ../$(PREFIX_CC)server
	@echo "Cleaned"

