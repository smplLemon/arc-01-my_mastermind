# Welcome to My Mastermind

---

## Task

This program simulates the classic Mastermind game, where the player tries to guess a secret code within a limited number of rounds.

## Description

The program generates a secret code consisting of four digits. The player has multiple rounds to guess the code. After each guess, the program provides feedback on how many digits are correctly placed (well-placed pieces) and how many digits are correct but not in the correct position (misplaced pieces). The player wins if they guess the code within the specified rounds.

## Installation

No installation is required. Simply compile the provided C code using a C compiler, and the executable will be generated for execution. Ensure that the necessary C standard libraries are available in your environment for compilation.

## Usage

To use the program, follow these steps:
To use the program, do these steps:

Compilation: Compile the program using a C compiler. For example:
Copy code
gcc -o mastermind mastermind.c
Execution: Execute the compiled program with optional command-line arguments. -c <secret_code>: Specify a custom secret code consisting of 4 unique digits.
-t <round_count>: Specify the number of rounds (default is 10).
bash
Copy code
Execution: Execute the compiled program with optional command-line arguments. -c <secret_code>: you can choose a secret code consisting of 4 unique digits.
-t <round_counter>: You can set the round of this game (settled for 10).
in bash:
Copy code firstly
./mastermind -c 1234 -t 15
Gameplay: Follow the prompts to enter guesses for the secret code. Enter 4 unique digits for each guess.
Outcome: The program will provide feedback after each guess, indicating the number of well-placed and misplaced pieces. If the secret code is guessed correctly within the specified number of rounds, the game ends with a congratulatory message.
Outcome:

### The Core Team

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>