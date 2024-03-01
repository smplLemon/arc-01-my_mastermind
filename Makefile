 CC = gcc
   CFLAGS = -Wall -Wextra -Werror
   TARGET = mastermind
   SRC = mastermind.c
   OBJ = $(SRC:.c=.o)

   all: $(TARGET)

   $(TARGET): $(OBJ)
       $(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

   clean:
       rm -f $(OBJ)

   fclean: clean
       rm -f $(TARGET)