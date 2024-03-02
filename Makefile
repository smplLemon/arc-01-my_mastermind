CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = mastermind

SRCS = mastermind.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
  $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

.c.o:
  $(CC) $(CFLAGS) -c $< -o $@

clean:
  rm -f $(OBJS) $(TARGET)
