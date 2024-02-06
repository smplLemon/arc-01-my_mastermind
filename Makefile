Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = mastermind
SRC = mastermind.c

all: $(TARGET)

$(TARGET): $(SRC)
  $(CC) $(CFLAGS) -o $@ $<

clean:
  rm -f $(TARGET)
