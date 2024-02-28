CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET = my_mastermind

all : $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean fclean

clean:
	rm -fr $(TARGET).o

fclean: clean
	rm -fr $(TARGET)
