CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = My_mastermaid.c
OBJ = $(SRC:.c=.o)
TARGET = My_mastermaid

all : $(TARGET)

$(TARGET) : $(OBJ)
 $(CC) $(CFLAGS) -o $(TARGET) $(OBJ) 

$(OBJ) : $(SRC)
 $(CC) $(CFLAGS) -c $(SRC)

clean:
 rm -f *.o

fclean: clean
 rm -f $(TARGET)

re: fclean all