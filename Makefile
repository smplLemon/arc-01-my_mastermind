CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCE = my_Mastermind.c
TARGET = my_mastermind

$(TARGET):$(SOURCE)
	$(CC) $(CFLAGS) -o $@ $^
.PHONY: fclean
fclean:
	@rm -r $(TARGET)
re: fclean
