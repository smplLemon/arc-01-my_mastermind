## Description
my_mastermind is a command-line implementation of the classic Mastermind game. In this game, players attempt to guess a secret code within a limited number of attempts. After each guess, the game provides feedback to help the player refine their subsequent guesses.

## Task
The task of this project is to create a functional Mastermind game in C, following the provided specifications. The program should allow customization of the secret code and the number of attempts, and it should provide accurate feedback on the player's guesses.

## Usage
The my_mastermind program supports several command-line options to customize gameplay:

-c specifies the secret code. If not provided, a random code will be generated.
-t specifies the number of attempts. Default is 10.

## Installation
    ```
    gcc -o my_mastermind my_mastermind.c
    ```

 Replace `<secret_code>` with the secret code you want to use for the game, and `<number_of_attempts>` with the desired number of attempts. If you don't specify a secret code or the number of attempts, default values will be used.

4. **Play the Game**: Follow the prompts to make your guesses and receive feedback until you either guess the secret code correctly or run out of attempts.

