CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -O0
SOURCES = my_mastermind.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = my_mastermind

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean fclean re

clean:
	@rm -f $(TARGET) $(OBJECTS) core

fclean: clean
	@rm -f $(TARGET)

re: fclean $(TARGET)
