    ## Welcome to my_mastermind

This is your game management system.

## Task

The main task of this project is to provide the user with the opportunity to play a game of guessing a secret code consisting of digits by correctly entering them.

## Description

This game allows the user to demonstrate their intellectual abilities. The user tries to guess a secret code consisting of selected digits by the program, and in each move, the program evaluates the user's entered code and provides information to the user about which digits are in the correct positions and which digits are in the incorrect positions.

## Installation

To download the project, follow these steps:

1. Clone the repository:

   ```bash
   git clone <repository_url>
   ```

2. Navigate to the cloned directory:

   ```bash
   cd my_mastermind
   ```

3. Install the program:

   ```bash
   make install
   ```

## Usage

To run the program, enter the following commands:

```bash
./my_mastermind -t <number_of_moves> -c <secret_code>
```

- `-t`: Number of moves. The number of attempts for guessing the secret code. (Optional, default is 10 moves)
- `-c`: Secret code. (Optional, automatically generated if not provided)

The user is provided with instructions according to the provided code and number of moves. The results are displayed on the screen after the game ends.
