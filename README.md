Description
This C program implements the classic game of Mastermind, where the player attempts to guess a secret code within a limited number of rounds. The code offers a command-line interface for customizing the game parameters and provides feedback on the player's guesses.

Game Overview
In Mastermind, the player must decipher a secret code consisting of four unique numbers between 0 and 8. The game allows a specified number of rounds for the player to guess the code. After each guess, the game provides feedback on the correctness of the guess, indicating the number of well-placed and misplaced pieces.

Features
Customizable Secret Code: Players can either input their own secret code or have one generated randomly by the program.
Variable Number of Rounds: The number of rounds can be adjusted via command-line arguments.
Feedback Mechanism: After each guess, the game provides feedback to guide the player towards the correct solution.
Error Handling: The program validates user input to ensure it meets the game's requirements.
Tasks
Secret Code Handling: The program generates or accepts a secret code from the user.
Input Validation: Validates user input to ensure it meets the game's criteria.
Game Loop: Executes the game loop, allowing the player to make guesses until the code is cracked or the rounds are exhausted.
Feedback Generation: Provides feedback on the correctness of the player's guesses.
Win Condition Check: Determines if the player has correctly guessed the secret code.
Usage
Compile the code: gcc -o mastermind mastermind.c

Run the executable: ./mastermind [options]

Options:

-c [code]: Set the secret code manually (must be 4 unique digits).
-t [rounds]: Set the number of rounds (default is 10).
Installation
Ensure you have a C compiler installed, such as GCC, to compile and run the program.