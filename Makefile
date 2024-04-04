CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXEC = guess_game

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    $(RM) $(OBJS) $(EXEC)
