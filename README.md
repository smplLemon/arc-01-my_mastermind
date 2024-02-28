## My mastermind Game
### Description
This project  is a console-based implementation of the classic Mastermind game without colors. In Mastermind, the player has 10 attempts to guess a secret code consisting of 4 distinct pieces. After each guess, the game provides feedback on the number of well-placed or miss-placed.
### Task
The challenge is to create a Mastermind game in which the player is given 10 attempts to guess a secret code from 4 different elements. After each attempt, the game reports the number of correctly guessed elements and the number of incorrectly guessed elements.
### How to Play
Clone the repository:


``` sh
git clone <repository_url>
cd myMastermindGame
```
Compile the program using the provided Makefile:

``` sh
make
```
Run the program:


``` sh
./my_mastermind [-c <CODE>] [-t <ATTEMPTS>]
```
### Optional arguments:

- -c <CODE>: Specifies the secret code. If not provided, a random code will be generated.
- -t <ATTEMPTS>: Specifies the number of attempts (default is 10).
Follow the on-screen instructions to play the game. Enter your guesses and receive feedback until you find the secret code or run out of attempts.