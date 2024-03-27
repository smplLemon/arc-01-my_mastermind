CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind
SRC = my_mastermind.c

$(TARGET): $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY:fclean

fclean:
	rm -f $(TARGET)

 
	