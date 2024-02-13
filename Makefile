TARGET = my_mastermind
SRC = my_mastermind.c
CFLAGS = -Wall -Wextra -Werror

all: $(TARGET)

$(TARGET): $(SRC)
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

fclean: clean

re: fclean all