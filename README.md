## Welcome to my_mastermind

Welcome to my_mastermind, a simple implementation of the Mastermind game in C.

## Task

The task is to guess the secret code within a limited number of attempts.

## Description

The program generates a secret code of four digits. The digits can range from 0 to 8, and each digit in the code is unique. The player needs to guess this code. After each guess, the program provides feedback indicating the number of correctly placed digits and the number of correctly guessed digits but in the wrong position.

## Installation

To install and run my_mastermind, follow these steps:

1. Clone the repository:

```
git clone <repository_url>
```

2. Compile the program:

```
gcc -o my_mastermind my_mastermind.c
```

3. Run the program:

```
./my_mastermind
```

## Usage

Follow the instructions provided by the program to input your guesses. Each guess should consist of four digits ranging from 0 to 8. After each guess, the program will provide feedback to help you refine your subsequent guesses. Try to guess the secret code within the specified number of attempts to win the game.

