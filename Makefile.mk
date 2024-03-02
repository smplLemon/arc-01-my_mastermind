TARGET = my_ngram
CC = gcc 
SRC = my_ngram.c
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