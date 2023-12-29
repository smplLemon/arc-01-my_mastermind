# Mastermind Game

This is a simple implementation of the classic Mastermind game in C.

## Task

- [x] You will need to create a folder and in this folder will be additional files containing your work.
- [x] Folder names must start with special file names and also contain ( Makefile - _.c - _.h).
- [x] The player must follow the Mastermind game rules.
- [x] A player is allowed to guess multiple times.
- [x] Guesses entered by the player are checked and feedback is given whether they are correct or incorrect.

## Description

The player has several attempts to find the secret code. If the player finds the code, he wins and the game stops. A misplaced part is a part that is present in the secret code but not in good condition.


## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/JunaevAzamat/arc-01-my_mastermind.git
    cd mastermind
    ```

2. Build the project:

    ```bash
    make
    ```

3. Run the game:

    ```bash
    ./my_mastermind -c SECRET_CODE -t MAX_ATTEMPTS
    ```

    - Replace `SECRET_CODE` with the secret code you want to use.
    - Replace `MAX_ATTEMPTS` with the maximum number of attempts allowed (optional, default is 10).

## Game Rules

- The secret code consists of 4 digits.
- Each digit can be from 0 to 9.
- Digits in the code cannot be repeated.

## Usage

- Enter your guess for the secret code.
- The game will provide feedback on your guess:
  - Number of correctly placed digits.
  - Number of misplaced digits.

## Examples

```bash
./my_mastermind -c 1234 -t 10
