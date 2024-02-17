# Welcome to "Mastermind"

This program is a simple implementation of the Mastermind game in C. The Mastermind game is a code guessing game in which the player tries to guess a secret code in a certain number of attempts.

## Instructions

1. **Compiling**: Compile the code using a C compiler. For example: gcc mastermind.c -o mastermind

2. **Launch**:

- Run the program without command line arguments to play the game with a randomly generated secret code.
- Run the program with secret code as command line argument to play with specific code. For example:
  ```
  ./mastermind -c 1234
  ```

3. **Gameplay**:

- The player has 10 attempts to guess the secret code.
- The player must enter a 4-digit number without repeating digits.
- After each attempt, the program will give feedback on the correctness of the guess.

4. **Feedback**:

- "Correctly positioned" indicates the number of digits in the correct position.
- "Incorrectly positioned" indicates the number of correct digits in the incorrect position.

5. **End game**:

- If the player guesses the secret code correctly, he wins.
- If the player exhausts all attempts, the secret code will be revealed.

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt="Qwasar SV -- Software Engineering School's Logo" src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
