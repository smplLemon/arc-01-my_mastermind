CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = my_mastermind* c/my_string.c
TARGET = my_mastermind

$(TARGET):
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: fclean

fclean: clean

clean:
	@rm -rf $(TARGET)

make re:
	@rm -rf $(TARGET)
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
