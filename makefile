CC = gcc
CFSCV = -g -Wall -Wextra -Werror
SOURCE = mastermind.c
TARGET = mastermind

$(TARGET):$(SOURCE)
	$(CC) $(CFSCV) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)