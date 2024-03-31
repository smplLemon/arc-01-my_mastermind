# Welcome to my game Mastermaind
# Task
*This program is a simple implementation of a guessing game in which the player tries to guess a secret code within a limited number of attempts. the game provides feedback on the correctness of the guesses, indicating how many numbers are placed correctly and how many are placed incorrectly.
# Description
*The game generates a secret code consisting of four unique numbers from 0 to 7. The player then tries to guess the code within a certain number of attempts. After each guess, the game provides feedback on the accuracy of the guess, indicating the number of correctly placed digits and the number of incorrectly placed digits.
# Installation
*To install and compile the game, follow these steps:
*Clone the repository or download the source code files.
*Compile the source code using a C compiler such as gcc. For example: gcc -o guess_game.c
* Run the compiled executable.
# Usage
*Once the game is compiled and running, follow these instructions to play:
*If no arguments are provided, a random secret code will be generated and the game *will start with default settings (9 attempts).
*If desired, you can provide command line arguments to configure the game:
*-t <attempts>: Specify the number of attempts the player must guess the code.
*-c <code>: Specify a specific secret code to guess.
* Enter your guesses when prompted. Each guess must be four digits from 0 to 7, with no duplicates.
*After each guess, the game will provide feedback on the correctness of the guess:
*"Congratulations! You did it!" if the assumption is correct.
*Otherwise, the number of correctly placed digits and the number of incorrectly placed digits will be indicated.
*Keep guessing until you guess the correct code or you run out of attempts.
*After completing the game, you can continue the game by restarting the executable file.
* Enjoy the guessing game!