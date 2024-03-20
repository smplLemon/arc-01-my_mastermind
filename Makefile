CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = my_mastermind
SRC = my_mastermind.c
OBJ = my_mastermind.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)

fclean: clean

.PHONY: all clean fclean
