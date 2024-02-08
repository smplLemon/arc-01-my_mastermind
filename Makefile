CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

all: mastermind

mastermind: mastermind.o my_mastermind.o
	$(CC) $(CFLAGS) $^ -o $@

mastermind.o: mastermind.c mastermind.h
	$(CC) $(CFLAGS) -c $< -o $@

my_mastermind.o: my_mastermind.c mastermind.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f mastermind *.o
