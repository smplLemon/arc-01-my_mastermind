# My Mastermind Project

## Welcome to My Mastermind!

This is a simple implementation of the classic game **Mastermind** implemented in the **C programming language**.
The game is played against the computer, where the computer generates a random code and the player has to guess it.

## Table of Contents

- [How to Play](#how_to_play)
- [Features](#features)
- [Task](#task)
- [Description](#description)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Future Improvements](#future_improvements)
- [License](#license)
- [Notes](#notes)
- [The Core Team](#the_core_team)

## How to Play

1. At the start of the game, the computer generates a secret code consisting of a sequence of colored pegs.
2. The player needs to enter their guessed code.
3. After each guess, the computer provides feedback in the form of colored and white pegs.
    - A color peg represents a correctly guessed color in the correct position.
    - A white peg represents a correctly guessed color but in the wrong position.
4. Based on the feedback, the player needs to use a combination of logic and deduction to gradually determine the secret code.
5. The game continues until the player successfully guesses the code or exceeds the maximum number of attempts.

## Features

- Random code generation by the computer.
- Input validation to ensure a valid code is entered.
- Feedback system to help the player make informed guesses.
- Limit on the number of attempts to avoid overly long games.
- User-friendly interface with clear instructions.

## Task

For each exercise, you will have to create a folder and in this folder, you will have additional files that contain your work.
Folder names are provided at the beginning of each exercise under submit directory and specific file names for each exercise are also provided at the beginning of each exercise under submit file(s)

Submit files:

    Makefile - *.c - *.h


### Specifications

Write a program called mastermind; it will be an implementation of the famous game.

### Name

- my_mastermind

### Synopsis

- my_mastermind [-ct]

## Description

This project is a console-based implementation of the popular game Mastermind using the C programming language.
Mastermind is a code-breaking game, where the player must guess the correct combination of colors within a certain number of attempts.

## Requirements

To run this game on your system, you need to have a C compiler installed.
If you don't have a C compiler, you can install **gcc** compiler on Windows/Linux by running the following command:

```
mingw-get install gcc.
```

```
sudo apt-get install build-essential
```

For Windows users, you can install **MinGW** which includes the **gcc** compiler.

## Installation

1. Clone the repository or download the source code files.
2. Open a terminal window and navigate to the directory where the files are located.
3. Compile the C file using the following command:
   ```
   gcc mastermind.c -o mastermind
   ```
4. Run the compiled program by executing the generated executable:
   ```
   ./mastermind
   ```
5. Follow the on-screen instructions to play the game.

## Usage

1. Clone this repository or download the source code files.
2. Open a terminal or command prompt and navigate to the project directory.
3. Compile the source code using the following command:

```
gcc -o mastermind mastermind.c
```

4. Run the game with the following command:

```
./mastermind
```

## Future Improvements

- Implement difficulty levels to increase or decrease the number of possible colors and code length.
- Add a leaderboard to track high scores.
- GUI implementation for a more visually pleasing experience.

Feel free to contribute by opening pull requests or suggesting improvements!

## License

This project is licensed under the [MIT License](LICENSE).

## Notes

- The feedback provided after each guess assists the player in refining their subsequent guesses.
- The randomization of the secret code ensures a different game experience each time.
- Feel free to modify the number of colors, number of attempts, or any other aspects of the game to suit your preferences. 

Enjoy playing Mastermind in C!

## The Core Team

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
