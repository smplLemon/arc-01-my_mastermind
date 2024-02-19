# Welcome to Mastermind

## Task

The program implements the Mastermind game, where the player needs to guess a secret code.

## Description

This program generates a random secret code or accepts a custom code from the user. The player has a limited number of attempts to guess the code correctly. After each guess, the program provides feedback on the correctness of the guessed digits and their positions.

## Installation

No installation is required. Simply compile the provided source code using a C compiler:

```bash
gcc mastermind.c -o mastermind

./mastermind -t 12 -c 1234