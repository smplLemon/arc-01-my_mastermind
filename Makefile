TARGET = master_mind
CC = gcc 
SRC = master_mind.c
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