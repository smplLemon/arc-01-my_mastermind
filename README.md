# My Mastermind

This is a project to implement a simplified version of the Mastermind board game in C programming language.

## Task

The main task is to develop a game interface that allows players to make educated guesses and receive immediate feedback from the computer on their correctness.

1. Specifications: Write a program called mastermind; it will be an implementation of the famous game.
2. Name: my_mastermind

## Description

Mastermind is a mind game where players try to guess a secret code by making educated guesses and receiving feedback on the accuracy of their guesses. This C program implements the classic Mastermind game, allowing players to challenge the computer to crack the secret code.

Mastermind is a game composed of 9 pieces of different colors.A secret code is then composed of 4 distinct pieces.The player has 10 attempts to find the secret code.After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.
If the player finds the code, he wins, and the game stops.A misplaced piece is a piece that is present in the secret code butthat is not in a good position.

## Requirements

- Your code must be compiled with the flags -Wall -Wextra -Werror.
- Multiline macros are forbidden
- You should have multiple file .c but it's forbidden to include them - (#include another_file.c) use your Makefile to compile them together.
- Macros with logic (while/if/variables/...) are forbidden

## Installation

1. Clone the repository using git clone https://github.com/username/My-Mastermind.git
2. Navigate to the project directory using cd My-Mastermind
3. Open the project in your preferred code editor
4. Start the game by running c main.c in the terminal
5. Installations:

## Usage

After the installation is complete, you can run the program using the command provided in the documentation.

1. Prerequisites: Ensure you have a C compiler installed.
2. Download: Download the project source code.
3. Compilation: Open a terminal and navigate to the project directory. Run the following command to compile the code:

```
gcc mastermind.c -o mastermind
```

4. Execution: Run the compiled executable file:

```
./mastermind
```

5. Gameplay: Follow the on-screen instructions to play the game. Make guesses and receive feedback until you crack the secret code or run out of attempts.

## Gameplay

To start the game, run c main.c in the terminal. You will be prompted to select the game mode (classic, colored, or grayscale). The classic mode uses the standard set of colors, while the colored and grayscale modes use additional colors or grayscale variations, respectively.

After selecting the game mode, you will be asked to choose the number of colors and the length of the code. You can then make your guess by entering a series of numbers corresponding to the color choices.

The game will provide feedback after each guess, showing you the number of correct matches and the number of near matches. Continue making guesses until you find the hidden code.

## Features

- Different game modes (classic, colored, and grayscale)
- Customizable number of colors and code length
- Instant feedback on the accuracy of your guesses
- Replayability

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to fork the repository and submit pull requests for any features, bug fixes, or improvements.

## The Core Team

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt="Qwasar SV -- Software Engineering School's Logo" src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
