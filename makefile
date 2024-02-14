CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind
SRC = my_mastermind.c 

$(TARGET) : $(SRC)
	gcc $(CFLAGS) -o $(TARGET) $(SRC)

.Phony: fclean 


fclean:
	rm -r $(TARGET)