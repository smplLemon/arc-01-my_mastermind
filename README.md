# Mastermind Game

This is a simple command-line implementation of the Mastermind game in C.

## Description

Mastermind is a code-breaking game where the player tries to guess a secret code within a limited number of attempts. In this implementation, the player must guess a 4-digit code consisting of digits 0-8. After each guess, the program provides feedback indicating the number of correctly placed digits and the number of misplaced digits.

## Usage

To run the game, compile the code using a C compiler. You can specify the number of attempts using the `-t` option and provide a custom secret code using the `-c` option.

$ gcc mastermind.c -o mastermind
$ ./mastermind -t 10 -c 1234

markdown
Copy code

If you don't provide the `-c` option, a random code will be generated for you.

## Options

- `-t <attempts>`: Set the number of attempts allowed (default is 10).
- `-c <code>`: Set a custom secret code for the game.

## How to Play

1. Run the program.
2. Enter your guess when prompted.
3. The program will provide feedback on your guess.
4. Keep guessing until you either correctly guess the code or run out of attempts.

## Example

$ ./mastermind -t 5
Will you find the secret code?
Please enter a valid guess:
Round 1

1234
Correctly placed pieces: 2
Misplaced pieces: 1

Round 2

5678
Correctly placed pieces: 0
Misplaced pieces: 2
...
Congratulations! You did it!

csharp
Copy code

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.# Mastermind Game

This is a simple command-line implementation of the Mastermind game in C.

## Description

Mastermind is a code-breaking game where the player tries to guess a secret code within a limited number of attempts. In this implementation, the player must guess a 4-digit code consisting of digits 0-8. After each guess, the program provides feedback indicating the number of correctly placed digits and the number of misplaced digits.

## Usage

To run the game, compile the code using a C compiler. You can specify the number of attempts using the `-t` option and provide a custom secret code using the `-c` option.

$ gcc mastermind.c -o mastermind
$ ./mastermind -t 10 -c 1234

markdown
Copy code

If you don't provide the `-c` option, a random code will be generated for you.

## Options

- `-t <attempts>`: Set the number of attempts allowed (default is 10).
- `-c <code>`: Set a custom secret code for the game.

## How to Play

1. Run the program.
2. Enter your guess when prompted.
3. The program will provide feedback on your guess.
4. Keep guessing until you either correctly guess the code or run out of attempts.

## Example

$ ./mastermind -t 5
Will you find the secret code?
Please enter a valid guess:
Round 1

1234
Correctly placed pieces: 2
Misplaced pieces: 1

Round 2

5678
Correctly placed pieces: 0
Misplaced pieces: 2
...
Congratulations! You did it!



## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.