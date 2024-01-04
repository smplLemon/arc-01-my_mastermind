CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c
OBJS = $(SRCS:.c=.o)
TARGET = mastermind

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
 $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
 $(CC) $(CFLAGS) -c $< -o $@

clean:
 rm -f $(OBJS) $(TARGET)
