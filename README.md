## Welcome to my Mastermind

### Description

This program is a simple implementation of the Mastermind game, showcased in Codespace. Mastermind involves guessing a secret code within a limited number of attempts, typically set to 10 or customizable by the user. The code provides feedback on the correctness of the guessed code.

### Task

The program's task is to enable users to guess the secret code within a specified number of rounds, primarily set to 10. It calculates each guess and provides feedback on the number of correctly placed and misplaced pieces.

### Usage

To use the program, follow these steps:

1. **Compilation**: Compile the program using a C compiler. For example:

    ```
    gcc -o mastermind mastermind.c
    ```

2. **Execution**: Execute the compiled program with optional command-line arguments.
    - `-c <secret_code>`: Choose a secret code consisting of 4 unique digits.
    - `-t <round_counter>`: Set the number of rounds for the game (default is 10).
    
    Example in bash:

    ```
    ./mastermind -c 1234 -t 15
    ```

3. **Gameplay**: Follow the prompts to enter guesses for the secret code. Enter 4 unique digits for each guess.

4. **Outcome**: After each guess, the program will provide feedback, indicating the number of well-placed and misplaced pieces. If the secret code is guessed correctly within the specified number of rounds, the game ends with a "Congratz! You did it!" message.

### Installation

No installation is required. Simply compile the provided C code using a C compiler, such as in VsCode, and the executable will be generated for execution. Ensure that the necessary C standard libraries are available in your workspace for compilation.
