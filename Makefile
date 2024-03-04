CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

SRC = main.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
    $(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(EXECUTABLE)
