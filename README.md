## Overview
Mastermind or Master Mind is a code-breaking game for two players invented in Israel. It resembles an earlier pencil and paper game called Bulls and Cows that may date back a century.
The idea of the game is for one player (the code-breaker) to guess the secret code chosen by the other player (the code-maker). The code is a sequence of 4 colored pegs chosen from six colors available. The code-breaker makes a serie of pattern guesses - after each guess the code-maker gives feedback in the form of 2 numbers, the number of pegs that are of the right color and in the correct position, and the number of pegs that are of the correct color but not in the correct position - these numbers are usually represented by small black and white pegs.

## Features

- Interactive Mastermind game with a user-friendly interface.
- Customizable game settings, such as code length and the number of allowed guesses.
- Well-designed feedback to help the codebreaker refine their guesses.

## Getting Started

### Installation

Navigate to the project directory:

```bash
 cd my_mastermind
```

Build the project using the provided Makefile:

```bash
 make -f Makefile.mak
```

### Usage

- Start the game:

  ```bash
    ./mastermind [-c secret_code] [-t attempts]
  ```

- Optional command line arguments:

-c: Set the secret code manually. If not provided, a random code will be generated.
-t: Set the number of attempts. Default is 10.

- Gameplay
  Follow the on-screen prompts to make guesses. The game provides feedback on each guess, and you can enter "stop" at any time to end the game.
