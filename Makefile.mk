TARGET = my_mastermind
CC = gcc 
SRC = my_mastermind.c
FLAGS = -Wall -Wextra -Werror 

all : $(TARGET)
$(TARGET) : $(SRC)
 $(CC) $(FLAGS) -o $(TARGET) $(SRC)


clean : 
 rm  -r $(TARGET) 
 .PHONY : fclean

fclean:
 rm -rf $(TARGET)

re : fclean all
