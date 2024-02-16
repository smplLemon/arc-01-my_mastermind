## Welcome to My Mastermind Game!

This is a simple implementation of the Mastermind game in C.

## Task

Your task is to guess a secret code within a limited number of attempts.

## Description

The program generates a random 4-digit code with digits between 0 and 8. You need to guess this code within a certain number of attempts. After each guess, the program will provide feedback on how many digits are correctly placed (well-placed pieces) and how many digits are correct but in the wrong position (misplaced pieces).

## Installation

To install and run the game, follow these steps:

1. Clone this repository to your local machine.
2. Compile the C code using a C compiler such as GCC.
3. Run the compiled executable file.

Example:
```
gcc my_mastermind.c -o my_mastermind
./my_mastermind
```

## Usage

Once the game is running, follow the prompts to input your guesses. You can also use command-line arguments to customize the game:

- Use `-t` followed by a number to set the number of attempts (default is 10).
- Use `-c` followed by a 4-digit code to set the secret code manually. If not provided, a random code will be generated.

Example:
```
./my_mastermind -t 15 -c 1234
```

Enjoy playing Mastermind!