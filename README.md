## Author
Yeshmuratov Javohir

## Description
Guess the Code is a simple console-based game where the player attempts to guess a secret code. The code is four digits long, and the player has a limited number of attempts to guess the correct combination. The game provides feedback on well-placed and misplaced pieces after each guess.

## Task
Your goal is to guess the four-digit secret code. Enter your guess at each round, and the game will inform you of the number of well-placed and misplaced pieces. Keep guessing until you correctly identify the code or run out of attempts.

## Usage
Compile the Program:

bash
Copy code
gcc filename.c -o guess_game
Run the Program:

bash
Copy code
./guess_game -c <secret_code> -t <attempts>
Optional command-line arguments:

-c: Specifies the secret code. If not provided, a random code will be generated.
-t: Specifies the number of attempts. The default is 9.
Gameplay:

Enter a four-digit code at each round.
Receive feedback on well-placed and misplaced pieces.
Continue guessing until you correctly identify the code or run out of attempts.
Enjoy the Game!

## Installation
No specific installation is required. Ensure you have a C compiler installed on your system, such as GCC, to compile and run the program. If needed, adjust the command-line arguments to customize the game experience. Have fun playing Guess the Code!
