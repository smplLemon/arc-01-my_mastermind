CC = gcc
CFLAGS = -Wall -Wextra

all: mastermind

mastermind: main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f mastermind *.o