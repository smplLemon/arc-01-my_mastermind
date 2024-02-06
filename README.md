## Welcome to my_mastermind

## Task

The code provided implements a command-line game called "Mastermind." The game involves guessing a secret code within a limited number of attempts. The code contains functions for string manipulation, random number generation, input validation, and checking the correctness of the guessed code.

## Description

The code consists of several functions:
 `my_strlen`: Calculates and returns the length of a given string `str_1`.
 `my_strcmp`: Compares two strings `str_1` and `str_2`. Returns 0 if the strings are equal and 1 if they are different.
 `my_strcpy`: Copies the contents of string `p2` to `p1` and returns `p1`.
 `my_atoi`: Converts a string `str_1` to an integer and returns the result.
 `check_character`: Checks if a character `c` is present in the string `str1`. Returns 1 if found, 0 otherwise. `my_random`: Generates a random 4-digit code with non-repeating digits.
 `my_scanf`: Reads a string of characters from the standard input and returns it.
 `repetation_check`: Checks if a guessed code `guescode` has repeated digits. Returns 1 if there are no repetitions, 0 otherwise.
 `wrong_input_check`: Performs input validation on a guessed code `guescode`. Returns 1 if the code is valid, 0 otherwise.
 `mis_pl_well_pl_checker`: Compares the secret code and the player's guess, calculates the number of well-placed and misplaced pieces, and prints the result.
 `my_mastermind2`: Implements the game logic, taking the number of attempts and the secret code as parameters. Handles user input, checks the validity of guesses, and calls `mis_pl_well_pl_checker` to evaluate each guess.
 `my_mastermind`: Parses command-line arguments and sets up the game parameters. If no secret code is provided, it generates a random code using `my_random` function.
The `main` function initializes the game by calling `my_mastermind` and passing the command-line arguments.

## Installation

To compile the code, use a C compiler such as `gcc`. For example:
```
gcc -o mastermind mastermind.c
```

## Usage

The game can be executed from the command line with optional parameters:

```
./mastermind -c [secret_code] -t [number_of_attempts]
```

- `-c` specifies the secret code to be guessed. If not provided, a random code will be generated.
- `-t` specifies the number of attempts allowed. The default is 10 attempts.

During the game, the program will prompt for input, and the user should enter a 4-digit code. The program will provide feedback on the correctness of the guess, including the number of well-placed and misplaced pieces.
Please note that the code assumes the standard input and output streams for user interaction.