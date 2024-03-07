CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind

all: $(TARGET)

$(TARGET): my_mastermind.c
	$(CC) $(CFLAGS) -o $(TARGET) my_mastermind.c

clean:
	rm -f $(TARGET)
