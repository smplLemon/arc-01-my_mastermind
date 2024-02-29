CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = my_mastermind.c
OBJS = $(SRCS:.c=.o)
TARGET = my_mastermind

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
