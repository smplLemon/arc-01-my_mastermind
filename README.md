# Welcome to My Mastermind
***

## Task
Write a program called mastermind; it will be an implementation of the famous game.

## Description
Mastermind is a game composed of 9 pieces of different colors.
A secret code is then composed of 4 distinct pieces.

The player has 10 attempts to find the secret code.
After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.

If the player finds the code, he wins, and the game stops.
A misplaced piece is a piece that is present in the secret code butthat is not in a good position.

You must read the player's input from the standard input.

Your program will also receive the following parameters:
-c [CODE]: specifies the secret code. If no code is specified, a random code will be generated.
-t [ATTEMPTS]: specifies the number of attempts; by default, the playerhas 10 attempts.

## Installation
You can use the make command to compile the code and generate an executable file, and then run make re to recompile the code after making changes to it.

## Usage
The code is a simple implementation of the Mastermind game. It generates a random code of length 4 composed of digits, and the player has 10 attempts to guess the code. After each attempt, the program will provide feedback on the number of digits that are well-placed and mis-placed. The code and number of attempts can be changed through command-line arguments.
