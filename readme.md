## Mastermind Game in C

### Overview

Mastermind is a code-breaking game for two players. One player, the codemaker, creates a secret code. The other player, the codebreaker, tries to guess the code by making guesses. The codemaker gives feedback on each guess, indicating how many digits are correct and in the correct position, and how many are correct but in the wrong position.

### Features

* Command-line interface
* Randomly generated secret code
* Configurable number of attempts
* Feedback on each guess
* Win/lose message

### Description

The game is played on a 4x4 grid. The codemaker chooses a secret code of four digits, each of which can be any number from 0 to 8. The codebreaker then makes guesses, one at a time. After each guess, the codemaker gives feedback by indicating how many digits are correct and in the correct position (called "well placed"), and how many are correct but in the wrong position (called "missed placed").

The codebreaker has a limited number of guesses to find the secret code. If the codebreaker guesses the correct code within the allotted number of guesses, they win the game. Otherwise, the codemaker wins.

### Getting Started

#### Installation

To install the game, simply clone the repository and compile the code:

```
git clone https://github.com/username/mastermind-c.git
cd mastermind-c
make
```

#### Usage

To play the game, run the following command:

```
./mastermind
```

You can specify the number of attempts and the secret code as command-line arguments. For example, to play a game with 15 attempts and a secret code of 1234, you would run the following command:

```
./mastermind -t 15 -c 1234
```

### Example Gameplay

The following is an example of a game of Mastermind:

```
Will you find the secret code?
Please enter a valid guess:
> 1234
---
Round 0
Well place pieces: 0
Missed place pieces: 0
> 1567
---
Round 1
Well place pieces: 0
Missed place pieces: 1
> 2345
---
Round 2
Well place pieces: 1
Missed place pieces: 1
> 1342
---
Round 3
Well place pieces: 2
Missed place pieces: 1
> 1243
---
Round 4
Well place pieces: 3
Missed place pieces: 0
> 1234
---
Round 5
Well place pieces: 4
Missed place pieces: 0
Congrats! You did it!
```

In this example, the codebreaker guesses the secret code (1234) in 5 attempts.