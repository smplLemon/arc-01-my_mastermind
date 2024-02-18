# My Mastermind

## Description
My Mastermind is an implementation of the famous Mastermind game. The game is composed of 9 pieces of different colors. A secret code is then composed of 4 distinct pieces. The player has 10 attempts to find the secret code. After each input, the game indicates to the player the number of well-placed pieces and the number of misplaced pieces.
However we will use numbers ranging from 0 to 8 instead of colors.
## Usage

The program receives following parameters: -c and -t. Former for manipulating the secret code while the latter one to change the number of attempts. by defaults secret code is generated and attempts is defaulted to 10.

./my_mastermind -c "0123" -t 8

## Examples
Will you find the secret code?
Please enter a valid guess
---
Round 0
>1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Congratz! You did it

## License
I wish it was licensed under MIT but no it's not.