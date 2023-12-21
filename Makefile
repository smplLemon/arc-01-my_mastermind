CC=gcc
CFLAGS=-Wall -Wextra -Werror

EXEC=my_mastermind

OBJ=main.o my_mastermind.o

$(EXEC): $(OBJ)
			$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJ)

fclean: clean
			rm -f $(EXEC)

re: fclean $(EXEC)

.PHONY: clean fclean re
