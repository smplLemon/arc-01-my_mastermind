## Secret Code Game

**## Overview**

This repository contains a command-line game written in C where players attempt to guess a 4-digit secret code. The code can be either **randomly generated** or **provided by the user**. Digits in the code are **unique** and range from **0 to 8**.

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

   Replace `my_mastermind.c` and `my_mastermind` with your actual filenames.
4. **Run the game:** Execute the program with desired arguments:

   ```bash
   ./my_mastermind -c 1234 -t 5
   ```

**2. Using a pre-compiled executable:**

Pre-compiled executables might be available online, but **exercise extreme caution** when downloading from untrusted sources. **It is highly recommended to compile the code yourself from a trusted source for security reasons.**

**## Gameplay**

1. **Run the program:** Follow the installation instructions above.
2. **Guess the code:** Enter your guess, a 4-digit number with **unique digits** between **0 and 8**.
3. **Receive feedback:** After each guess, the game provides:
   - **Well placed pieces:** Number of correct digits in the **correct position**.
   - **Misplaced pieces:** Number of correct digits in the **wrong position**.
4. **Continue guessing:** Use the feedback to refine your future guesses until you **crack the code** or **exhaust your attempts**.

**## Game Termination**

The game ends in three ways:

1. **Correct guess:** You successfully guess the code and receive a congratulatory message.
2. **Exhausted attempts:** You run out of allowed attempts.
3. **Manual interruption:** Stop the game anytime using `Ctrl+C` or `Ctrl+D` in the terminal (unsaved progress will be lost).

**## Rules**

* Each digit (code and guess) must be between **0 and 8**.
* No **duplicate digits** are allowed in the code or guess.
* Your guess must be **exactly 4 digits long**.

**## Command-Line Arguments**

The game accepts two optional arguments:

* `-c <code>`: Provide a custom secret code (e.g., `-c 1234`).
* `-t <attempts>`: Set a custom number of attempts (e.g., `-t 10`).

**## Code Breakdown**

The code likely includes functions for:

* **`generate_code()`**: Generates a random 4-digit code.
* **`valid_input(char *guess)`**: Checks if the player's guess is valid.
* **`get_input(char *guess)`**: Reads the player's guess from the standard input.
* **`check_guess(char *code, char *guess, int *well_placed, int *misplaced)`**: Compares the guess with the code and updates the values of `well_placed` and `misplaced` based on the results.
* **`handle_guess(char *code, char *guess, int attempts)`**: Handles the guess evaluation, provides feedback, and checks if the player won. Returns 1 if the player wins, 0 otherwise.
* **`game_loop(char *code, int attempts)`**: Runs the main game loop, handling rounds, player input, feedback, and game termination.
* **`handle_arguments(int argc, char *argv[], char **code, int *attempts)`**: Parses command-line arguments for the code and number of attempts.
* **`main(int argc, char *argv[])`**: The main function of the program.

**## Example Usage**

```bash
./a.out or /a.exe # Play with random code and default attempts
./a.out -c 1234 -t 8  # Play with custom code and attempts
```
