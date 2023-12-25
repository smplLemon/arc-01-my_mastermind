# Mastermind Game

## Description
This program is an implementation of the Mastermind game. In the Mastermind game, the player has 10 attempts to guess a secret code of 4 distinct pieces. After each guess, the game indicates the number of well-placed pieces and the number of misplaced pieces.

## Task
 Mastermind is a game composed of 9 pieces of different colors. A secret code is then composed of 4 distinct pieces. The player has 10 attempts to find the secret code. After each input, the game indicates to the player the number of well-placed pieces and the number of misplaced pieces.

## Installation and Usage
1. Clone the repository:

   ```
   git clone <repository_url>
   cd my-mastermind
   ```

2. Compile the program using the provided Makefile:

   ```
   make
   ```

3. Run the program:

   ```
   ./my_mastermind [-c <CODE>] [-t <ATTEMPTS>]
   ```

   Optional arguments:
   - `-c <CODE>`: Specifies the secret code. If not provided, a random code will be generated.
   - `-t <ATTEMPTS>`: Specifies the number of attempts (default is 10).

4. Follow the on-screen instructions to play the game. Enter your guesses and receive feedback until you find the secret code or run out of attempts.

## Example Usage
```
./my_mastermind -c "0123"
```

This will start the game with the specified secret code "0123".

### Example

```bash
./my_mastermind -c "0123"
Will you find the secret code?
Please enter a valid guess.
---
Round 0
>1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Congratz! You did it!
```