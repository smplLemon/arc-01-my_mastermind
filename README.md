## Task
The challenge lies in implementing the game logic, including generating a random secret code, receiving and validating user input, evaluating the guess, and providing feedback to the player.

## Description
Mastermind is a game composed of 9 pieces of different colors. A secret code is then composed of 4 distinct pieces. The player has 10 attempts to find the secret code. After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces. Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'. If the player finds the code, he wins, and the game stops. A misplaced piece is a piece that is present in the secret code butthat is not in a good position.I set up a C project with necessary libraries (stdio.h, stdlib.h, string.h, time.h) and defined constants for the game (max_attempts, code_length, colors).I created many functions like makeSecretCode to generate a random secret code using the rand() function. I stored the input in a buffer (guess) and null-terminated it to form a string.I implemented the evaluateGuess function to compare the user's guess with the secret code and calculate the number of well-placed and misplaced pieces.I used a for loop to iterate through the game rounds (attempts) and break the loop if the user guesses the code correctly or runs out of attempts.
At the beginning of the game, a secret code of a specified length is generated randomly. The code is made up of digits from 0 to 8.The player is given a certain number of attempts to guess the secret code. The number of attempts is specified by the player or defaults to 10.The game consists of several rounds, each representing a player's guess. The player enters a guess for the secret code.After each guess, the program evaluates the guess and provides feedback to the player. The game continues until the player correctly guesses the secret code or runs out of attempts. If the player guesses the code correctly, a congratulatory message is displayed. Otherwise, the game reveals the secret code and ends.



## Installation
git clone https://github.com/yourusername/my_mastermind.git
cd mastermind
make

## Usage
In order to use this project, you write below to terminal. 
./my_mastermind
./my_mastermind -c secret code -t attempt number
To stop the game or end of file, enter "Ctrl+d
