CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = my_mastermind

all: $(TARGET)

$(TARGET): my_mastermind.c
	$(CC) $(CFLAGS) -o $(TARGET) my_mastermind.c

clean:
	rm -f $(TARGET)

fclean: clean
	# Add any additional clean-up commands here, e.g., remove other generated files

re: fclean all
