CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99

TARGET = secret_code

$(TARGET): secret_code.o
    $(CC) $(CFLAGS) -o $(TARGET) secret_code.o

secret_code.o: secret_code.c
    $(CC) $(CFLAGS) -c secret_code.c

clean:
    rm -f $(TARGET) *.o
