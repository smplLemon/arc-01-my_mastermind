CC = gcc 
FLAGS = -Wall -Wextra -Werror 
TARGET = my_mastermind 
 
 
all : $(TARGET) 
 
$(TARGET): my_mastermind.c 
 $(CC) $(FLAGS) -o $(TARGET) my_mastermind.c 
 
clean : 
 rm -f $(TARGET) 
 
fclean : clean 
 # Files Deleted 
 
re: fclean all
