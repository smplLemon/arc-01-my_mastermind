OBJ = mastermind.o  my_mastermind.o
CFLAGS = -Wall -Wextra -Werror 
TARGET = my_mastermind
CC = gcc

.PHONY : all clean fclean re

all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS)  -o $@ $^


.c.o:
	$(CC) -c $^ 

clean :
	rm -f *.o

fclean : clean
	rm -f $(TARGET)	


re: fclean all	