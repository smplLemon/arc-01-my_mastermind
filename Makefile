CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = my_mastermind.c
EXE = mastermind

all: $(EXE)

$(EXE): $(SRC)
  $(CC) $(CFLAGS) -o $(EXE) $(SRC)

clean:
  rm -f $(EXE)
