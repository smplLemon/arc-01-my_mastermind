CC = gcc
CFGC = -g -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET = my_mastermind

$(TARGET):$(SOURCE)
	$(CC) $(CFGC) -o $@ $^

.PHONY:fclean

fclean:
	@rm -r $(TARGET)
