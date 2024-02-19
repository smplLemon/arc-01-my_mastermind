## Welcome to Master_mind project

## The task
This program includes the required standard C libraries: <stdio.h>, <stdlib.h>, <string.h>, <unistd.h> and <time.h>. These libraries provide functions for I/O, string manipulation, memory allocation, and timing operations.The function my_random programs a random four-digit code.The function is_incorrect validates the data entered by the user.

## Description
Mastermind is a game composed of 9 pieces of different colors.
The player has 10 attempts to find the secret code. After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8''9'.

If the player finds the code, he wins, and the game stops. A misplaced piece is a piece that is present in the secret code but that is not in a good position.

## Installation
Use a C compiler like `gcc` to compile the code. For example:
```
gcc -o mastermind mastermind.c
``` 

## Usage
The game can be executed from the command line with optional parameters:
The game can be executed from the command line with optional parameters:

./mastermind -c [secret_code] -t [number_of_attempts]

- -c specifies the secret code to be guessed. If not provided, a random code will be generated.
- -t specifies the number of attempts allowed. The default is 10 attempts.




