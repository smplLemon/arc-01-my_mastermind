CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SOURCE = my_mastermind.c
TARGET = my_mastermind

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

fclean:
	rm -f $(TARGET)