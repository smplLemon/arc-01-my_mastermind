CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = mastermind

all: $(TARGET)

$(TARGET): mastermind.c
	$(CC) $(CFLAGS) -o $(TARGET) mastermind.c

clean:
	rm -f $(TARGET)
