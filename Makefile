TARGET = my_mastermind
OBJ = my_mastermind.o
SRC = my_mastermind.c
CFLAGS = -Wall -Wextra -Werror
CC = gcc

.PHONY: all clean fclean re

all : $(TARGET)
$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f *.o

fclean : clean
	rm -f $(TARGET)

re: fclean all
