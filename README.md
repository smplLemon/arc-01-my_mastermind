# Mastermind Game

This repository contains a simple implementation of the Mastermind game in C. The game generates a secret code, and the player needs to guess the code within a limited number of rounds.

## How to Use

1. Clone the repository to your local machine.
2. Compile the code using a C compiler. For example, using `gcc`:

   ```
   gcc -o mastermind mastermind.c
   ```

3. Run the executable:

   ```
   ./mastermind
   ```

## Command Line Options

The program supports the following command-line options:

- `-c <code>`: Manually set the secret code. The code must be a 4-digit number.
- `-t <rounds>`: Set the maximum number of rounds. The default is 10 rounds.

## Gameplay

1. If you choose to provide the secret code manually using the `-c` option, make sure to follow the format `-c 1234`, where `1234` is the secret code.
2. If you don't provide a secret code, the program will generate one randomly.
3. The game will prompt you to guess the secret code. Enter a 4-digit number as your guess.
4. After each guess, the program will provide feedback on the correctness of your guess.
5. The game continues until you guess the correct code or reach the maximum number of rounds.
6. If you fail to guess the code within the specified rounds, the game will reveal the secret code.

## Example

./mastermind -t 8

This command starts the game with a maximum of 8 rounds. The program will generate a secret code, and you need to guess it within 8 rounds.

## Note

- This implementation of the Mastermind game is a simple version. Contributions to enhance the game's features or improve code efficiency are welcome.
