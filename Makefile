CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = my_mastermind
SRC = my_mastermind.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
          $(CC) $(CFLAGS) -o $@ $^

clean:
          rm -f $(TARGET)