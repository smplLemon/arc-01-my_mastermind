CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind

all: $(TARGET)

$(TARGET): my_mastermind.c mastermind.c mastermind.h
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f $(TARGET)

fclean: clean

re: fclean all
