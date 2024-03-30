CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_mastermind
SRC = my_mastermind.c 

$(TARGET) : $(SRC)
   $(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY:fclean


fclean:
   rm -r $(TARGET)
