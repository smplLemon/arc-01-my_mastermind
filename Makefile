CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SOURCE = my_mastermind.c
TARGET = my_mastermind
OBJECT = my_mastermind.o

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECT)

$(OBJECT) : $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE)

clean :
	rm -f *.o

fclean:
	rm -f $(TARGET)