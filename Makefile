CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic

all: mastermind

mastermind: mastermind.o
	$(CC) $(CFLAGS) -o $@ $^

mastermind.o: mastermind.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f mastermind mastermind.o
