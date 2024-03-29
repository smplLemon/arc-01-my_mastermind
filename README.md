## Welcome

Welcome to the secret code guessing game! This simple C program allows you to test your code-cracking skills by guessing a randomly generated secret code.

## Task

Your task is to guess the secret code within a limited number of attempts. The code consists of four digits, and each digit is unique.

## Description

The game will prompt you to enter your guess for the secret code. After each guess, the program will provide feedback on how close your guess was to the actual code.

If a digit in your guess matches a digit in the secret code and is in the correct position, it will be considered a "well-placed piece." If a digit in your guess matches a digit in the secret code but is in the wrong position, it will be considered a "misplaced piece."

You have a limited number of attempts to guess the code. If you guess the code correctly within the given attempts, you win the game! Otherwise, you lose.

## Installation

To compile and run the program:

1. Clone the repository or download the source code files.
2. Navigate to the directory containing the source code files.
3. Compile the program using a C compiler. For example:
   ```
   gcc -o secret_code_game secret_code_game.c
   ```
4. Run the compiled executable. For example:
   ```
   ./secret_code_game
   ```

Follow the on-screen instructions to play the game and enjoy!
