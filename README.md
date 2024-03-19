# arc-01-my_mastermind

# Welcome to My Mastermaind Game

# Task
*This program is a simple implementation of a guessing game where the player tries to guess a secret code within a limited number of attempts. The game provides feedback on the correctness of the guesses, indicating how many digits are correctly placed and how many are misplaced.
# Description
*The game generates a secret code consisting of four unique digits between 0 and 7. The player then tries to guess the code within a specified number of attempts. After each guess, the game provides feedback on the accuracy of the guess, indicating the number of correctly placed digits and the number of misplaced digits.
# Installation
*To install and compile the game, follow these steps:
*Clone the repository or download the source code files.
*Compile the source code using a C compiler such as gcc. For example:gcc -o guess_game.c
*Run the compiled executable.
# Usage
*Once the game is compiled and executed, follow these instructions to play:
*If no arguments are provided, a random secret code will be generated, and the game will *start with default settings (9 attempts).
*Optionally, you can provide command-line arguments to customize the game:
*-t <attempts>: Specify the number of attempts the player has to guess the code.
*-c <code>: Provide a specific secret code to guess.
*Enter your guesses when prompted. Each guess should consist of four digits between 0 and 7, without any duplicates.
*After each guess, the game will provide feedback on the correctness of the guess:
*"Congratz! You did it!" if the guess is correct.
*Otherwise, it will indicate the number of correctly placed digits and the number of misplaced digits.
*Keep guessing until you either guess the correct code or run out of attempts.
*Once the game ends, you can choose to play again by restarting the executable.
*Enjoy playing the guessing game!