CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean

all: my_mastermind

my_mastermind: my_mastermind.c
  $(CC) $(CFLAGS) -o my_mastermind my_mastermind.c

clean:
  rm -f my_mastermind

fclean: clean