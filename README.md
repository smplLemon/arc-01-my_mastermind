## Welcome to My Mastermind Game

## Task
In this section, you will gather all the necessary information about your Mastermind game.

## Description
Provide a brief overview of the **Mastermind** game, emphasizing its gameplay and rules. The game is centered around guessing a variable code. Users' guesses are evaluated, providing them feedback.

Game Concepts:
- In each turn, users attempt to guess the correct code.
- Users must provide a 4-digit code in each turn.
- Feedback is given to users in each turn, including:
  - "Well placed pieces": Number of correctly placed digits.
  - "Missed placed pieces": Number of incorrectly placed digits.
- The game continues until users guess the code or run out of attempts.

## Installation
Describe the installation steps and configurations needed for the game. This includes dependencies, download links, and setup instructions.

## Usage
Provide instructions on how to run and play the game.

- **Installation**:
  - The game requires **C** programming language and **gcc** compiler.
  - Download the game code from your GitHub repository.
  - Navigate to the game directory in the terminal.
  - Execute the following command in the terminal:

    ```bash
    gcc -o mastermind mastermind.c
    ```

- **Running the Game**:
  - To run the game, execute the following command in the terminal:

    ```bash
    ./mastermind
    ```

- **Options**:
  - Users can customize game parameters with command-line options:
    - `-t` - Number of attempts (e.g., `-t 10`).
    - `-c` - Set a specific code (e.g., `-c 1234`).

- **Playing the Game**:
  - Start the game by typing ">", then enter "Play game".
  - You will be prompted to enter a 4-digit code.
  - Feedback and responses will guide you through the game.
  - Continue playing until you guess the code or the game ends.
