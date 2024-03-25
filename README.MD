# Welcome to my_mastermind

## Task

The task of the `my_mastermind` program is to play the game of Mastermind. The program generates a secret code consisting of four digits from 0 to 8 (inclusive). The player needs to guess the code within a limited number of attempts. After each guess, the program provides feedback on the correctness of the guess. The game continues until the player guesses the code correctly or runs out of attempts.

## Description

The `my_mastermind` program is written in C and consists of several functions to handle different aspects of the game. Here is a brief description of the major functions:

1. `initialize_random()` - Initializes the random number generator based on the current time.

2. `generate_random_code()` - Generates a random four-digit code by randomly selecting digits from 0 to 8 (inclusive) without repetition.

3. `is_invalid_input(char *input)` - Checks if the user's input is valid. It verifies the length of the input, checks if each character is a digit between 0 and 8, and ensures that there are no duplicate digits.

4. `read_user_input()` - Reads the user's input from the command line. It continuously prompts the user for input until a valid input is provided.

5. `evaluate_guess(char *code, char *guess)` - Evaluates the user's guess and provides feedback. It counts the number of well-placed pieces (correct digits in the correct positions) and the number of misplaced pieces (correct digits in the wrong positions) in the guess compared to the secret code.

6. `print_game_start_message()` - Prints the initial game start message to the console.

7. `print_game_result_message()` - Prints the game result message when the player fails to guess the secret code within the given number of attempts.

8. `play_game(int attempts, char *code)` - Manages the gameplay loop. It prompts the user for guesses, evaluates them, and repeats the process until the player guesses the code correctly or runs out of attempts.

9. `get_game_attempts(int argc, char **argv)` - Retrieves the number of attempts for the game from the command line arguments. If the `-t` option is provided, the corresponding argument specifies the number of attempts. If not provided, the default value is 10.

10. `get_game_code(int argc, char **argv)` - Retrieves the secret code for the game from the command line arguments. If the `-c` option is provided, the corresponding argument specifies the code. If not provided, a random code is generated.

11. `main(int argc, char **argv)` - The entry point of the program. It initializes the random number generator, retrieves the number of attempts and the secret code from the command line arguments, and starts the game by calling the `play_game` function.

## Installation

To compile and run the `my_mastermind` program, you need a C compiler installed on your system. Here are the steps to compile and run the program:

1. Save the code provided in a file named `my_mastermind.c`.

2. Open a terminal or command prompt and navigate to the directory where you saved the `my_mastermind.c` file.

3. Run the following command to compile the program:
   ```
   gcc -o my_mastermind my_mastermind.c
   ```

4. After the compilation is successful, you can run the program using the following command:
   ```
   ./my_mastermind
   ```

## Usage

The `my_mastermind` program can be run with or without command line arguments. Here are the usage options:

1. Run the program without any arguments:
   ```
   ./my_mastermind
   ```
   This will start the game with the default number of attempts (10) and a randomly generated secret code.

2. Run the program with the `-t` option to specify the number of attempts:
   ```
   ./my_mastermind -t 15
   ```
   This will start the game with 15 attempts to guess the secret code.

3. Run the program with the `-c` option to specify the secret code:
   ```
   ./my_mastermind -c 1234
   ```
   This will start the game with the provided secret code "1234". Note that the code must be a four-digit number with digits from 0 to 8 (inclusive).

4. Run the program with both the `-t` and `-c` options:
   ```
   ./my_mastermind -t 12 -c 5678
   ```
   This will start the game with 12 attempts and the provided secret code "5678".

5. During the game, you will be prompted to enter your guesses. Each guess should be a four-digit number with digits from 0 to 8 (inclusive). After each guess, the program will provide feedback on the correctness of the guess.

6. If you guess the secret code correctly within the given number of attempts, the programwill display the message "Congratulations! You did it!" and exit.

7. If you run out of attempts without guessing the secret code correctly, the program will display the message "Sorry, you couldn't find the secret code!".

That's all you need to know to install and use the `my_mastermind` program. Have fun playing the game!