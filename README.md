# Mastermind Game

This is a simple implementation of the classic game Mastermind in C, created for the Qwasar.io curriculum.

## Description

Mastermind is a code-breaking game for two players. One player, the codemaker, chooses a secret code consisting of a series of digits. The other player, the codebreaker, tries to guess the code. After each guess, the codemaker provides feedback by indicating how many digits in the guess are correct and well-placed (marked as well place pieces) and how many digits are correct but misplaced (marked as missed place pieces). The codebreaker continues guessing until they either guess the code correctly or run out of attempts.

## How to Play

To play the game, simply compile the provided C code and run the executable. By default, the game will generate a random secret code, and the player will have 10 attempts to guess it. However, you can also specify the number of attempts and even provide your own secret code using command-line arguments.

### Command-line Options

- `-t <attempts>`: Specify the number of attempts allowed. Default is 10.
- `-c <code>`: Provide your own secret code to be guessed by the player.

### Example Usage

```bash
$ gcc mastermind.c -o mastermind
$ ./mastermind           
$ ./mastermind -t 15     
$ ./mastermind -c 1234   
```

## Files

- `mastermind.c`: The source code of the Mastermind game.
- `README.md`: This file, providing instructions and information about the game.

## Requirements

- This program requires a C compiler to build (make).
- It should run on any system with a compatible C environment.