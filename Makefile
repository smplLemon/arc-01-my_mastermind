CC = gcc
CFLAGS = -Wall -Wextra -Werror
COURCES = my_mastermind.c
TARGET = my_mastermind

$(TARGET):$(COURCES)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f *.o
fclean: clean
	@rm -f $(TARGET)