CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = my_mastermind
SRCS = my_mastermind.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)
