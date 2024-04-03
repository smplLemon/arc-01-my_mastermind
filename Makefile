CC = gcc 
CFLAGS = -Wall -Wextra -Werror 
TARGET = mastermind 
SRCS = my_mastermind.c 
OBJS = $(SRCS:.c=.o) 
 
all: $(TARGET) 
 
$(TARGET): $(OBJS) 
 $(CC) $(CFLAGS) $(OBJS) -o $(TARGET) 
 
%.o: %.c mastermind.h 
 $(CC) $(CFLAGS) -c $< -o $@ 
 
clean: 
 rm -f $(OBJS) $(TARGET) 
 
re: clean all 
 
.PHONY: all clean re
