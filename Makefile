CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCE = my_Mastermind.c
TARGET = my_Mastermind

$(TARGET) : $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: fclean

fclean:
	@rm -rf $(TARGET)
