CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = mastermaind

all: $(TARGET)

$(TARGET): my_mastermind.o
	$(CC) $(CFLAGS) my_mastermind.o -o $(TARGET)

mastermind.o: mastermaind.c
	$(CC) $(CFLAGS) -c my_mastermind.c

clean:
	rm -f $(TARGET) *.o
