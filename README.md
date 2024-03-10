## Mastermind Game

	This is a console-based implementation of the popular Mastermind game. The objective of the game is to guess a secret code consisting of 4 unique digits (from 0 to 8) within a given number of attempts.
	The program accepts command-line arguments to customize the secret code and the number of attempts.

## Installation

	Clone the repository or download the source code file (mastermind.c).
	Open a terminal and navigate to the directory containing the source code file.
	Compile the code using the following command:
```
	make
```
	After successful compilation, the mastermind executable will be created in the same directory.

## Usage

	Run the compiled program with the following options:

```
	./mastermind [-c custom_code] [-t number_of_attempts]
```
	-c custom_code: Specify a custom secret code (4 unique digits, no spaces). If not provided, a random secret code will be generated.
	-t number_of_attempts: Specify the number of attempts allowed. The default value is 10.

## Example

```
	./mastermind -c 1234 -t 5
```
	In this example, the secret code is set to "1234", and the number of attempts allowed is set to 5.