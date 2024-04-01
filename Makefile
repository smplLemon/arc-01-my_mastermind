CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SOURCE = my_mastermind.c
TARGET = my_mastermind

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

fclean:
	rm -f $(TARGET)


	# Descriprion
"
Mastermind is a code-breaking game where the player attempts to guess a secret code composed of four digits.
The my_random() ensures a unique and random secret code for each game session.
The mis_pl_well_pl_checker() compares the secret code with the player's guess to determine how well-placed and misplaced pieces should be counted.
The check() prompts the user to enter guesses, validates the input, checks the guesses against the secret code, and provides feedback. The function continues until the player either guesses the correct code or reaches the specified number of rounds.
The all() serves as the entry point for the program. 
"
# Task
"
Task is to create the full inplementation of Mastermind game
"
# Usage
"
  Run the game with the following command:
  first type make to terminal and then type
  ./my_mastermind". this runs game and if you want change secret code "-c secret code", attemtps "-t attempts".
"
# Installation
" 
  To install the game, clone the repository and compile the source code.
  git colone
"
author: Abdurahmon Bahadirov