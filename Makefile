CC=gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_Mastermind
SRC = my_Mastermind.c

$(TARGET) : $(SRC)
  $(CC) $(CFLAGS) -o $@ $<

.PHONY : fclean

fclean:
  rm -f $(TARGET)