CC = gcc
CFLAGS = -Wall -Wextra -Werror

TARGET = My_Mastermaind
SRCS = My_Mastermaind.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

re: fclean all