CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind
SRC = my_mastermind.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f my_mastermind.o my_mastermind.c

