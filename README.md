## Description
This program is a simple description of the Mastermind game which showed in codespace. The Mastermind game involves guessing a secret code within a limited number of attempts, these attempts for 10 only or you set by yourself. The code provides feedback on the correctness of the guessed code.

## Task
The task of the program is to allow the user to guess the secret code within a specified number of rounds that mainly 10. Code calcylates each guess and provides feedback on the number of well-placed and misplaced pieces.

## Usage
To use the program, do these steps:

Compilation: Compile the program using a C compiler. For example:
Copy code
gcc -o mastermind mastermind.c
Execution: Execute the compiled program with optional command-line arguments. -c <secret_code>: you can choose a secret code consisting of 4 unique digits.
-t <round_counter>: You can set the round of this game (settled for 10).
in bash:
Copy code firstly
./mastermind -c 1234 -t 15
Gameplay: Follow the prompts to enter guesses for the secret code. Enter 4 unique digits for each guess.
Outcome: The program will provide feedbeck after each guess, indicating the number of well-placed and misplaced pieces. If the secret code is guessed correctly within the specified number of rounds, the game ends with a congratulatory message.

## Installation
No installation is required. Simply compile the provided C code using a C compiler, and the executable will be generated for execution. Ensure that the necessary C standard libraries are available in your environment for compilation.
