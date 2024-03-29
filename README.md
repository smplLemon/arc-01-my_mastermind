# Welcome to my_mastermind

## Task

The task is to create a command-line implementation of the Mastermind game.

## Description

Mastermind is a code-breaking game where one player (the code maker) creates a secret code, and the other player (the code breaker) attempts to guess the code within a certain number of attempts. After each guess, the code maker provides feedback to the code breaker on the correctness of the guess.

The secret code consists of a sequence of four numbers (0-8) chosen without replacement. The code breaker makes guesses by entering sequences of four numbers. After each guess, the code maker provides feedback in terms of "well-placed pieces" (correct numbers in correct positions) and "missed-placed pieces" (correct numbers in incorrect positions). The game continues until the code breaker guesses the code correctly or exhausts the allowed number of attempts.

## Installation

To install and run the `my_mastermind` program, follow these steps:

1. Clone the repository:

   ```
   git clone <repository-url>
   ```

2. Navigate to the directory:

   ```
   cd my_mastermind
   ```

3. Compile the program:

   ```
   gcc -Wall -Wextra -o my_mastermind my_mastermind.c
   ```

## Usage

To play the game, run the compiled program with optional command-line arguments:

```
./my_mastermind -c <secret-code> -t <attempts>
```

- `<secret-code>`: Optional. Specify the secret code to be guessed by the code breaker. If not provided, a random code will be generated.
- `<attempts>`: Optional. Specify the maximum number of attempts allowed for guessing the code. Default is 10.

Follow the on-screen instructions to make guesses and interact with the game. Use Ctrl+C to exit the game at any time.
