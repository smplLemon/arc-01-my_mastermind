G = gcc
TARGET = my_mastermind
SRC = my_mastermind.c
FLAGS = -Wall -Wextra -Werror 

$(TARGET) : $(SRC)
	@$(G) $(FLAGS) -o $(TARGET) $(SRC)

.PHONY : fclean

fclean :
	@rm -r $(TARGET)