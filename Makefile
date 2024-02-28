CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = my_mastermind

SRCS = my_mastermind.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

fclean: clean
	rm -f $(TARGET)
