CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = mastermind
SRCS = main.c my_mastermind.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c my_mastermind.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
