CC = gcc
CFLAGS = -Wall -Werror -std=c99

my_mastermind: my_mastermind.c
	$(CC) $(CFLAGS) -o my_mastermind my_mastermind.c

clean:
	rm -f my_mastermind

fclean: clean
	rm -f mastermind

re: fclean all