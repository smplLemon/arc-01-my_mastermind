CC = gcc
CFLAGS = -Wall -Wextra

TARGET = mastermind

all: $(TARGET)

$(TARGET): main.o
    $(CC) $(CFLAGS) -o $@ $^

main.o: main.c
    $(CC) $(CFLAGS) -c $<

clean:
    rm -f $(TARGET) *.o
