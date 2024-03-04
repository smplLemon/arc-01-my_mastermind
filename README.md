# Welcome to My Mastermind

Hello. Welcome to my mastermind

## Task

Mastermind is a game composed of 9 pieces of different colors. A secret code is then composed of 4 distinct pieces.

The player has 10 attempts to find the secret code. After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.

If the player finds the code, he wins, and the game stops. A misplaced piece is a piece that is present in the secret code butthat is not in a good position.

You must read the player's input from the standard input.

Your program will also receive the following parameters: -c [CODE]: specifies the secret code. If no code is specified, a random code will be generated. -t [ATTEMPTS]: specifies the number of attempts; by default, the playerhas 10 attempts.

## Description

Mastermind is a game composed of 9 pieces of different colors. A secret code is then composed of 4 distinct pieces.

The player has 10 attempts to find the secret code. After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

**Functions:**

- **String Manipulation Functions:**
  - `my_strlen`: Measures the length of a string.
  - `my_strcmp`: Compares two strings.
  - `my_strncpy`: Copies characters from the source string src to the destination string dest, up to a maximum of n characters.
- **Input Validation Functions:**
  - `isddigit`: Checks if a string contains only valid digits (0-8).
  - `CheckDuplicates`: Ensures a string doesn't contain duplicate digits.
  - `CheckInputErrors`: Validates user input for length, digit content, and duplicates.
- **Game Logic Functions:**
  - `genSecretCode`: Generates a random secret code with no duplicates.
  - `readInpVal`: Reads user input from the console.
  - `CheckCorrection`: Compares a guess with the secret code and provides feedback.
- **Main Game Function:**
  - `myMastermind`: Handles game setup, input, turn-taking, and win/loss conditions.

**Overall Program Flow:**

1. **Initialization:**
   - Command-line arguments can be used to set the secret code (`-c`) or maximum guesses (`-t`).
   - If a secret code isn't provided, a random one is generated.
2. **Game Loop:**
   - The player is prompted to make a guess within a specified number of rounds.
   - Input is validated for length, digit content, and duplicates.
   - Guesses are compared to the secret code, and feedback is provided on correctly placed and misplaced digits.
   - The game continues until the player wins by guessing the code correctly or runs out of guesses.

**Additional Notes:**

- The code uses custom implementations for string manipulation functions (`my_strlen`, `my_strcmp`, `my_strchr`) instead of standard library functions.
- The feedback provided to the player (`Well placed pieces` and `Misplaced pieces`) is slightly different from the traditional Mastermind rules, which typically use black and white pegs to indicate correct and misplaced digits, respectively.

## Installation

```
git clone https://github.com/sxnpaii/arc-01-my_mastermind.git
```

## Step-by-Step Usage Guide for the Mastermind Game:

**1. Compile the code:**

- Open a terminal in the directory where you saved the code.
- Run the following command: `make`
- This will create an executable file named `my_mastermind`.

**2. Run the game:**

- Open a new terminal window.
- Run the following command: `./my_mastermind` (replace `./` with the path to your executable if different)

**3. Optional command-line arguments:**

- `-c <secret_code>`: Set the secret code manually (provide digits within 0-8, no duplicates).
- `-t <max_guesses>`: Set the maximum number of guesses (default: 10).

**4. Start playing:**

- The game will display information about the secret code length and maximum guesses.
- On each turn, you'll be prompted to enter a guess (4 digits within 0-8).
- Ensure your guess doesn't have any duplicate digits!
- After entering your guess, you'll receive feedback:
  - `Well placed pieces`: Number of digits in your guess that are correct and in the right position.
  - `Misplaced pieces`: Number of digits in your guess that are correct but in the wrong position.
- Continue guessing until you either:
  - Guess the correct code within the allowed turns and win.
  - Run out of guesses and lose.

**5. Example gameplay:**

- Game starts with default settings (secret code randomly generated, 10 guesses).
- You enter guess "1234".
- Feedback: "1 Well placed piece, 0 Misplaced pieces".
- You continue guessing based on the feedback until you:
  - Win: Guess the correct code (e.g., "4567") and get the message "Congratz! You did it!".
  - Lose: Run out of guesses and see the message "Game Over!".

**6. Tips:**

- Analyze the feedback from previous guesses to make informed choices.
- Try not to waste guesses by repeating digits you know are not in the code.
- Remember, the secret code **does not** use repeated digits.

**Have fun cracking the code!**
