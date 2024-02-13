CC=gcc
CFLAGS=-Wall -Wextra -O2
TARGET=My_mastermaind
OBJS=My_mastermaind.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)
