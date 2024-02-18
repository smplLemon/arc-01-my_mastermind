## Welcome to Mastermind
To'layev Javlon

This is a simple implementation of the Mastermind game in C.

## Introduction

Mastermind is a classic code-breaking game where one player sets a secret code, and the other player tries to guess the code within a certain number of rounds. After each guess, the setter provides feedback about how many digits are correct and how many are in the correct position.

## How to Play

To play the game, compile the source code using a C compiler such as gcc:
Replace <rounds> with the desired number of rounds and <code> with the secret code (4 digits).

## Gameplay

1. The game will prompt you to enter a guess for the secret code.
2. You enter a 4-digit code, making sure each digit is between 0 and 8 and there are no duplicate digits.
3. After each guess, the game will provide feedback:
   - Well placed pieces: Number of digits in the correct position.
   - Misplaced pieces: Number of digits that are correct but in the wrong position.
4. You continue guessing until you correctly guess the code or reach the specified number of rounds.

## Files

- mastermind.c: Contains the source code for the game.
- README.md: This file, providing instructions and information about the game.

## Dependencies

- Standard C libraries: <stdio.h>, <stdbool.h>, <stdlib.h>, <time.h>, <string.h>, <unistd.h>

## Problems
I faced several difficulties during the preparation of this project.
I solved these problems by watching video tutorials about c.


## Contributing

If you find any issues or have suggestions for improvements, feel free to open an issue or create a pull request.