# Mastermind

This is a simple implementation of the Mastermind game in C. The game generates a secret code of 4 digits, and the player needs to guess the code within a certain number of attempts.

## How to Run

To compile and run the program, follow these steps:

1. Make sure you have a C compiler installed (e.g., gcc).
2. Clone or download the source code files.
3. Open a terminal and navigate to the directory where the files are located.
4. Compile the code using the following command:
    ```
    gcc mastermind.c -o mastermind
    ```
5. Run the compiled program with optional command-line arguments:
    - Use `-c` followed by a 4-digit code to set a specific secret code.
    - Use `-t` followed by a number to set the maximum number of attempts.

Example:
    ```
    ./mastermind -c 1234 -t 12
    ```

## Gameplay

- The player needs to guess a 4-digit secret code within a limited number of attempts.
- Each guess will be evaluated, showing the number of correctly placed digits and the number of misplaced digits.
- If the player guesses the correct code within the attempts limit, they win; otherwise, the game ends.

## Files

- `mastermind.c`: Contains the source code for the Mastermind game.
- `README.md`: This file, providing instructions and information about the game.

## Notes

- The secret code can be set manually using command-line arguments.
- The default maximum number of attempts is 10 if not specified.
