# Mastermind

This is a simple command-line game written in C where the player has to guess a secret code.

## How to Play

The game generates a secret code of length 4, consisting of digits from 0 to 8. The player's task is to guess this code. The game provides feedback on each guess, indicating how many digits are correctly placed and how many are misplaced.

## Code Structure

The code consists of several functions:

- `GenerateSecretCode(char *code)`: This function generates the secret code that the player has to guess.
- `CheckValidGuessts(char *guess)`: This function checks if the player's guess is valid. A valid guess is a string of 4 digits from 0 to 8, with no repeating digits.
- `ReadGuessts(char *guess)`: This function reads the player's guess from the standard input.
- `CounterPlaces(char *secretCode, char *guessCode)`: This function compares the player's guess with the secret code and counts how many digits are correctly placed and how many are misplaced.
- `UserAttempts(char *secretCode,char *guessCode, int maxRound)`: This function manages the game rounds, prompting the player for their guess and providing feedback.
- `main(int argc, char *argv[])`: The main function of the program. It initializes the game and manages the game loop.

## How to Run

To compile the game, use a C compiler such as gcc:

```
gcc secret_code_game.c -o secret_code_game
```
To run the game:
```
./secret_code_game
```
You can also specify the secret code and the maximum number of rounds as command-line arguments:
```
./secret_code_game -c 1234 -t 10
```
