## Mastermind Game in C
Numonov G'ofuramin 
## Overview

Mastermind is a code-breaking game for two players. One player, the codemaker, creates a secret code. The other player, the codebreaker, tries to guess the code by making guesses. The codemaker gives feedback on each guess, indicating how many digits are correct and in the correct position, and how many are correct but in the wrong position.
## Description

The game is played on a 4x4 grid. The codemaker chooses a secret code of four digits, each of which can be any number from 0 to 8. The codebreaker then makes guesses, one at a time. After each guess, the codemaker gives feedback by indicating how many digits are correct and in the correct position (called "well placed"), and how many are correct but in the wrong position (called "missed placed").

The codebreaker has a limited number of guesses to find the secret code. If the codebreaker guesses the correct code within the allotted number of guesses, they win the game. Otherwise, the codemaker wins.
## Installation

To install the game, simply clone the repository and compile the code:


git clone https://github.com/username/mastermind-c.gitcd mastermind-c
make
## Usage

To play the game, run the following command:


./mastermind