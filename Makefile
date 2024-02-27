CC = gcc
CFSCV = -g -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET = my_mastermind

$(TARGET):$(SOURCE)
	$(CC) $(CFSCV) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)
