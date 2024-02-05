CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind
SOURCE_FILES = my_mastermind.c

.PHONY: all clean fclean

all: $(TARGET)

$(TARGET): $(SOURCE_FILES:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCE_FILES:.c=.o)

fclean: clean
	rm -f $(TARGET)
