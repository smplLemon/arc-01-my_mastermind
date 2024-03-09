# Mastermind  

This program implements a simple version of the Mastermind game in C. Mastermind is a logic-based code-breaking game where the player attempts to guess a secret code within a limited number of attempts.

## How to Use

### Compilation

To compile the program, use the following command:

```
gcc -o mastermind mastermind.c
```

### Execution

Run the compiled program with optional command-line arguments:

```
./mastermind [-c <secret_code>] [-t <max_rounds>]
```

- `<secret_code>` (optional): Set the secret code manually. If not provided, a random secret code will be generated.
- `<max_rounds>` (optional): Set the maximum number of rounds (attempts) allowed. Default is 10.

### Gameplay

The player's objective is to guess the secret code within the given number of rounds. Upon each guess, the program will provide feedback on the correctness of the guess.

- If a digit in the guess matches both its value and its position in the secret code, it is considered a well-placed piece.
- If a digit in the guess matches a digit in the secret code but is in a different position, it is considered a misplaced piece.

The game continues until the player guesses the correct code or exhausts the maximum number of rounds.

## Files

- `mastermind.c`: Contains the C source code for the Mastermind game.
- `README.md`: This file, providing instructions and information about the program.

## Code Explanation

- `GenerateSecretCode`: Function to generate a random secret code.
- `CheckValidGuess`: Function to check the validity of the player's guess.
- `ReadGuess`: Function to read the player's guess from standard input.
- `CounterPlaces`: Function to compare the secret code with the player's guess and provide feedback.
- `UserAttempts`: Function to handle the game rounds and user attempts.
- `main`: Entry point of the program, parses command-line arguments, generates or takes the secret code, and initiates the game.

## Example

```
./mastermind -c 1234 -t 10
```

This command starts the game with the secret code set to "1234" and allows a maximum of 10 rounds.

## Note

- The program assumes a four-digit secret code.
- The player's guess must be a four-digit number.
- Digits in the secret code range from 0 to 8.
- Only one-digit values are allowed for simplicity.
- Error handling for invalid inputs is implemented.

Enjoy playing Mastermind!
