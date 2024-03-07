**# Secret Code Game**

**## Overview**

This repository contains a command-line game written in C where players attempt to guess a 4-digit secret code. The code can be either randomly generated or provided by the user. Digits in the code are unique and range from 0 to 8.

**## Installation**

There are two primary ways to play the game:

**1. Compiling the code yourself:**

**Requirements:**

* A C compiler installed on your system (e.g., GCC, Clang)
* Basic understanding of command-line usage

**Steps:**

1. **Obtain the source code:** Download the game's C source code files (e.g., `a.c` or `a.out`).
2. **Open a terminal:** Navigate to the directory containing the source code using the `cd` command.
3. **Compile the code:** Use your C compiler to compile the source code into an executable. The exact command depends on your compiler and operating system, but a typical example using GCC is:

   ```bash
   gcc my_mastermind.c
   ```

   Replace `a.c` and `a.out` with the actual filenames of your source code and executable, respectively.
4. **Run the game:** Once compiled, execute the program with desired arguments:

   ```bash
   ./a.out -c 1234 -t 5
   ```

**2. Using a pre-compiled executable:**

If you don't have a C compiler or prefer not to compile the code, you might find pre-compiled executables online for specific operating systems. However, **exercise extreme caution** when downloading executables from untrusted sources.

**## Gameplay**

1. **Run the program:** Follow the installation instructions above to launch the game.
2. **Guess the code:** You'll be prompted to enter your guess, which must be a 4-digit number where each digit is unique and between 0 and 8.
3. **Receive feedback:** After each guess, the game provides two hints:
   - **Well placed pieces:** The number of digits that are correct and in the correct position within the code.
   - **Misplaced pieces:** The number of digits that are correct but in the wrong position within the code.
4. **Continue guessing:** Use the feedback to refine your future guesses until you crack the secret code or exhaust your attempts.

**## Game Termination**

The game can end in three ways:

1. **Correct guess:** You successfully guess the secret code, leading to a congratulatory message.
2. **Exhausted attempts:** You run out of allowed attempts without guessing the code.
3. **Manual interruption:** You can stop the game at any time by pressing `Ctrl+C` or `Ctrl+D` in the terminal, but unsaved progress will be lost.

**## Rules**

* Each digit in the code and your guess must be between 0 and 8.
* No two digits in the code or your guess can be the same.
* Your guess must be exactly 4 digits long.

**## Command-Line Arguments**

The game accepts two optional command-line arguments:

* `-c <code>`: Provide a custom secret code for the game (e.g., `-c 1234`).
* `-t <attempts>`: Set a custom number of attempts for the game (e.g., `-t 10`).

**## Code Breakdown**

The code likely includes functions for:

* `generate_code()`: Generates a random 4-digit code.
* `is_valid_input(char *guess)`: Checks if the player's guess is valid.
* `getin()`: Reads the player's guess from the standard input.
* `check_guess(char *code, char *guess, int *well_placed, int *misplaced)`: Compares the guess with the secret code and provides feedback.
* `arguments(int argc, char *argv[], char **code, int *attempts)`: Processes command-line arguments.
* `main(int argc, char *argv[])`: The main function of the program.

**## Example Usage**

```bash
./a.out OR ./a.exe # Plays with a randomly generated code and default attempts
./a.out -c 1234 -t 8  # Uses the provided custom code and attempts
```

**## Enjoy the game!**
