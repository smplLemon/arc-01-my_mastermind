## Description

Mastermind is a classic code-breaking game where the player attempts to guess a secret code within a limited number of attempts. The game provides feedback to guide the player towards figuring out the correct code.

## Task

The objective of the Mastermind game is to guess the secret code created by the computer. The secret code consists of a sequence of colored pegs. As the player, you need to make guesses and receive feedback after each guess, allowing you to deduce the correct code.

## Usage

To play the Mastermind Game, follow these steps:
1. Compile the code using a C compiler by running the following command in a terminal: gcc main.c -o mastermind_game
2. Start the game by running the following command: ./mastermind_game (-c <code>) (-t <attempts>)

Optional Arguments:

-c <code>: Specify a custom secret code. The code should be a sequence of colored pegs. If not provided, a random secret code will be generated.
-t <attempts>: Specify the number of attempts the player has to guess the code. If not provided, the default value is 10.

#Installation

To install and run the game, follow these steps:

Clone this repository or download the source code files.
Open a terminal and navigate to the directory containing the source code files.
Compile the code by running the following command: gcc main.c -o mastermind_game
Start the game by running the compiled executable: ./mastermind_game
