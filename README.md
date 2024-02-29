## Welcome to [My Mastermind]

## Task
Write a C program to play a guessing game where the player tries to guess a secret code.

## Description
This C program generates a secret code consisting of four digits between 0 and 9. The player has to guess the code within a certain number of rounds. After each guess, the program provides feedback on the correctness of the guessed digits and their positions.

## Installation
No installation is required. Simply compile the C code using a C compiler such as GCC.

## Usage
To use the program, run the compiled executable with optional command-line arguments:
- `-t [rounds]`: Specify the number of rounds for the game (default is 10).
- `-c [code]`: Provide a custom secret code for the game. If not provided, a random code will be generated.

### Example Usage:
./guessing_game -t 15 -c 1234