# arc-01-my_mastermind
my_mastermind
This project is a command-line implementation of the game Mastermind. The goal of the game is to guess a secret code consisting of four numbers. After each guess, the program provides feedback on the correctness of the guess.
Features
Randomly generates a secret code if not provided by the user.
Allows the user to specify the number of attempts.
Validates user input, ensuring it meets the required criteria.
Provides feedback on the correctness of the guesses.
Displays a loading animation at the start of the program.
How to Run
Compile the source code using the following command:
gcc my_mastermind.c -o my_mastermind

Execute the compiled program:
./my_mastermind [-c ] [-t ]
Optional arguments:
-c <code>: Specify a secret code (four numbers) to guess.

-t <attempts>: Specify the number of attempts allowed (default: 10).
Note: If no secret code is provided or the provided code is invalid, a random secret code will be generated.
Gameplay Instructions
The program will display a loading animation and prompt you to enter a valid guess.
Enter your guess as a sequence of four numbers. Each number should be between 0 and 7 (inclusive), with no repeated digits.
After each guess, the program will provide feedback on the correctness of the guess. The feedback consists of two numbers:
Well placed pieces: The number of correctly guessed digits in the correct position.
Misplaced pieces: The number of correctly guessed digits in the wrong position.
Keep guessing until you either correctly guess the secret code or run out of attempts.