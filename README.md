## Welcome to my_mastermind

Welcome to my_mastermind, a simple mastermind game implemented in C.

## Task

The task is to guess the secret code within a limited number of attempts by entering valid guesses.

## Description

The program generates a secret code consisting of four unique digits (0-8) and prompts the user to guess the code. After each guess, the program provides feedback on the number of correctly placed digits (well) and the number of digits that are present in the code but are in the wrong position (missed).

## Installation

To install and run the program:

1. Download the source code either by cloning the repository or downloading the ZIP file.
2. Navigate to the directory containing the source code files.
3. Compile the code using a C compiler. For example, using GCC:

```bash
gcc -o my_mastermind my_mastermind.c
```

4. Execute the compiled binary file.

```bash
./my_mastermind
```

## Usage
Once you've installed and run the program, follow these steps to play the game:

The program will prompt you to enter a valid guess.
Enter a 4-digit code consisting of digits from 0 to 8.
The program will provide feedback on your guess, indicating the number of well-placed pieces (digits in the correct position) and missed-placed pieces (correct digits but in the wrong position).
Continue guessing until you either guess the correct code or exhaust your attempts.
You can also customize the number of attempts by using the `-t` option followed by the desired number of attempts when running the program.



The program can be executed from the command line with the following options:

- `-t <attempts>`: Specify the number of attempts allowed to guess the code. By default, it's set to 10.
- `-c <code>`: Provide a predefined secret code instead of generating a random one.

Example usage:

```bash
./my_mastermind -t 15 -c 1234
```

This command sets the number of attempts to 15 and uses the predefined secret code "1234".

Once the program is running, it prompts the user to enter guesses. The user should input a four-digit code each time and receive feedback until either the correct code is guessed or the maximum number of attempts is reached.

Enjoy playing the mastermind game!
