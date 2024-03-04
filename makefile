CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: mastermind

mastermind: mastermind.o
    $(CC) $(CFLAGS) -o mastermind mastermind.o

mastermind.o: mastermind.c
    $(CC) $(CFLAGS) -c mastermind.c

clean:
    rm -f mastermind mastermind.o