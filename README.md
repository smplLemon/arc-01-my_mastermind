# Welcome to My Mastermind
## Qwasar

## Task
The task is to implement a command-line Mastermind game in C, where the player has to guess a secret code within a limited number of attempts.

The game should indicate to the player the number of well-placed and misplaced pieces after each guess.

## Description

To solve the problem, the provided C code uses several helper functions to read user input, count well-placed and misplaced pieces, and generate a random secret code if none is provided as a command-line argument.

The mystrcpy function is used to copy strings.

The readinput function reads user input (guesses) and validates the input to ensure it consists of valid pieces ('0' to '8').

The count_wellplaced function compares the user's guess with the secret code and counts the number of well-placed pieces (correct piece in the correct position).

The count_misplaced function counts the number of misplaced pieces (correct piece in the wrong position).

The main function handles command-line arguments, generates a random code if needed, and runs the game loop until the player wins or exhausts all attempts.

## Installation

The project seems to be a simple C program, and it doesn't require any special installation steps other than compiling the code.

To compile the code, you can use the provided Makefile. The make command will build the executable my_mastermind.

##Usage

To run the Mastermind game, use the following command in the terminal:
```bash
./my_mastermind [-c [CODE]] [-t [ATTEMPTS]]
```
The optional -c flag allows you to specify the secret code as a 4-digit number consisting of the pieces '0' to '8'. If not specified, a random code will be generated.

The optional -t flag allows you to set the number of attempts for the player. If not specified, the default number of attempts is 10.

For example, to play the game with a specified secret code and 5 attempts:
```bash
./my_mastermind -c "0123" -t 5

./my_project argument1 argument2
```
The Core Team
Made at Qwasar SV -- Software Engineering School <img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' />
