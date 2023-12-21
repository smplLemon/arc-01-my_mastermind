CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = my_mastermind.c
OBJ = $(SRC:.c=.o)
EXEC = my_mastermind

all: $(EXEC)

$(EXEC): $(OBJ)
			$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJ) $(EXEC)

fclean: clean
			# Add any additional clean-up commands here, e.g., remove other generated files

re: fclean all
