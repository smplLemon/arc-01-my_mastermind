CC = gcc
TARGET = mastermind
CFLAGS = -Wall -Wextra -Werror
SRC = mastermind.c
OBJ = mastermind.o 

.PHONY : all clean fclean re

all : $(TARGET)

$(TARGET) : $(OBJ)
	gcc $(CFLAGS) -o $(TARGET) $(OBJ) 

$(OBJ) : $(SRC)
	gcc $(CFLAGS) -c $(SRC)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all 