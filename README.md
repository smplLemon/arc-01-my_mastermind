**Mastermind Game**

This code implements a simple version of the classic code-guessing game Mastermind. 

**How to Play**

1. Compile and run the program.
2. You can optionally specify the number of attempts using the `-t` flag followed by the desired number (default is 10).
3. You can optionally specify the secret code directly using the `-c` flag followed by the 4-digit code (without quotes). If not provided, a random code will be generated.
4. The game will prompt you to enter a guess. Each guess must be a 4-digit number with unique digits (no repetitions).
5. The game will provide feedback on your guess, indicating the number of correctly placed digits ("correctly placed pieces") and the number of digits that are correct but in the wrong position ("misplaced pieces").
6. You have a set number of attempts to guess the secret code correctly.

**Code Breakdown**

* **Functions:**
    * `generate_random_code()`: Generates a random 4-digit secret code with unique digits.
    * `check_input_validity(char *input)`: Checks if the user's guess is a valid 4-digit number with unique digits.
    * `evaluate_guess(char *code, char *guess, int *good, int *unitized)`: Compares the guess with the secret code and calculates the number of correctly placed digits and misplaced digits.
* **Main Function:**
    * Parses command-line arguments for the number of attempts and optional secret code.
    * Generates a random code if not provided as an argument.
    * Starts the game loop:
        * Prompts the user for a guess.
        * Validates the user's guess.
        * Evaluates the guess and provides feedback.
        * Checks if the guess is correct. The game ends if the guess is correct or the maximum number of attempts is reached.

**Compiling and Running**

1. Save the code as `my_mastermind.c`.
2. Compile the code using a C compiler like GCC:

```bash
gcc my_mastermind.c -o my_mastermind
```

3. Run the program:

```bash
./my_mastermind
```

4. You can optionally specify the number of attempts and secret code:

```bash
./my_mastermind -t 15 -c 1234
```

This will run the game with 15 attempts and the secret code set to 1234.
