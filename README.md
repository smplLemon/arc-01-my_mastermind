# Mastermind Game

In this program, you can play the "Mastermind" game where you have to guess a sequence of numbers.

## Game Description

The game is based on the following rules:

- There is a secret 4-digit code.
- Digits can range from 0 to 8 (each digit can be the same).
- In each of your guesses, the program calculates the value of your proposed numbers.
- If one of your proposed numbers is in the correct position in the secret code, the program considers this number as "correct".
- If one of your proposed numbers is in the secret code but in the wrong position, the program considers this number as "incorrect".
- You have 10 attempts.
- If you don't find the secret code within 10 attempts, the program informs you of the failure.

## Installation

To install the program, follow these steps:

1. Download the program.
2. Open your terminal and navigate to the directory where the program is located.
3. Compile the program using the following command:

    ```bash
    gcc -o mastermind mastermind.c
    ```

4. Start the game by running the following command:

    ```bash
    ./mastermind
    ```

## Additional Information

- You can change the secret code by using the `-c` flag followed by the desired code.
- You can specify the number of attempts with the `-t` flag (default value: 10).

## Reporting Issues

If you encounter any issues with the program, please report them to us. Provide as much information as possible about the issue.