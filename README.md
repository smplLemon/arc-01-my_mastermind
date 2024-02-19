## Description
This program is a simple implementation of the Mastermind game in C. The Mastermind game involves guessing a secret code within a limited number of attempts. The code provides feedback on the correctness of the guessed code.

## Task
The task of the program is to allow the user to guess the secret code within a specified number of rounds. The code evaluates each guess and provides feedback on the number of well-placed and misplaced pieces.

## Usage
To use the program, follow these steps:

Compilation: Compile the program using a C compiler. For example:
Copy code
gcc -o mastermind mastermind.c
Execution: Execute the compiled program with optional command-line arguments. -c <secret_code>: Specify a custom secret code consisting of 4 unique digits.
-t <round_count>: Specify the number of rounds (default is 10).
bash
Copy code
./mastermind -c 1234 -t 15
Gameplay: Follow the prompts to enter guesses for the secret code. Enter 4 unique digits for each guess.
Outcome: The program will provide feedback after each guess, indicating the number of well-placed and misplaced pieces. If the secret code is guessed correctly within the specified number of rounds, the game ends with a congratulatory message.

## Installation
No installation is required. Simply compile the provided C code using a C compiler, and the executable will be generated for execution. Ensure that the necessary C standard libraries are available in your environment for compilation.
