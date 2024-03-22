## Welcome
Yeshmuratov Javohir

## Description
This program is a simple guessing game where the player attempts to guess a secret code. The code generates a random 4-digit code without repetition, and the player has a limited number of attempts to guess the code.

## Task
The task of this program is to provide an interactive game environment where players can guess the secret code and receive feedback on their guesses.

## Usage
1.Compile the source code using a C compiler such as gcc.
2.Run the compiled executable file with optional command-line arguments.
Command-line Arguments.
-t <attempts>: Sets the number of attempts allowed for guessing the code. If not specified, the default value is 10.
-c <code>: Allows specifying the secret code to be guessed. If not provided, a random code will be generated.

## Installation
To install the program, clone the repository and compile the source code using a C compiler.
git clone <repository_url>
cd <repository_directory>
gcc guessing_game.c -o guessing_game.