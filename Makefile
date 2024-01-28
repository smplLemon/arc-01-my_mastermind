CC = gcc
CFLAGS = -Wall -Wextra -Werror
EXECUTABLE = my_mastermind

SRC_FILES = my_mastermind.c
OBJ_FILES = $(SRC_FILES:.c=.o)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)


fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all
