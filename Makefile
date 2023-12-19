OBJ = my_mastermind.o
TARGET = mastermind
CC = gcc
CFLAGS = -Wall -Wextra -Werror
all : $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

.c.o :
	$(CC) -c $^
clean :
	rm -f *o
fclean : clean
	rm -f $(TARGET)
re : fclean all