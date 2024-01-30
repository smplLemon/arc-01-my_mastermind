CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: my_mastermind

my_mastermind: main.c
  $(CC) $(CFLAGS) -o $@ $^

clean:
  rm -f my_mastermind

fclean: clean

re: fclean all