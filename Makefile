CC = gcc
CFLSGS = -g -Wall -Wextra -Werror
SOURCE = my_mastermind.c
TARGET = my_mastermind

$(TARGET):$(SOURCE)
  $(CC) $(CFLSGS) -o $@ $^

.PHONY: fclean 

fclean:
  @rm -r $(TARGET)
