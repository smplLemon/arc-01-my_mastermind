TARGET = my_mastermind
CC = gcc
SRC = my_mastermind.c
FLAGS = -Wall -Wextra -Werror

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(FLAGS) -o $(TARGET) $(SRC)

clean:
    rm -f $(TARGET)

.PHONY: fclean

fclean: clean
    rm -f $(TARGET)

re: fclean all