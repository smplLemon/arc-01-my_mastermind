# Mastermind Game

This is a simple implementation of the classic Mastermind game in C.

## Features

- **Classic Mode:** The traditional Mastermind game mode.
- **Colored Mode:** A mode with colored pegs.
- **Grayscale Mode:** A mode with grayscale pegs.

## Getting Started

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
