# Mastermind

This is a simple command-line game where the player attempts to guess a secret code within a limited number of attempts. The game provides feedback to the player after each guess to help them refine their subsequent guesses.

## Getting Started

### Prerequisites

To compile and run this game, you need a C compiler installed on your system. This code has been tested with GCC compiler.

### Compilation

To compile the game, navigate to the directory containing the source code files and execute the following command:

```bash
gcc -o code_breaker code_breaker.c

./code_breaker [-t NUM_ATTEMPTS] [-c SECRET_CODE]

```
$ ./code_breaker -t 8
Will you find the secret code?
Please enter a valid guess:
> 1234
--- Round 1
Well place pieces: 1
Missed place pieces: 2
> 0456
--- Round 2
Well place pieces: 0
Missed place pieces: 2
> 6780
--- Round 3
Well place pieces: 1
Missed place pieces: 1
> 6789
--- Round 4
Well place pieces: 2
Missed place pieces: 0
> 6785
--- Round 5
Well place pieces: 3
Missed place pieces: 0
> 6784
--- Round 6
Well place pieces: 4
Missed place pieces: 0
Congratz! You did it!
