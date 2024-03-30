# arc-01-my_mastermind

#For each exercise, you will have to create a folder and in this folder, you will have additional files that contain your work. Folder names are provided at the beginning of each exercise under submit directory and specific file names for each exercise are also provided at the beginning of each exercise under submit file(s).

#SPECIFICATIONS
Write a program called mastermind; it will be an implementation of the famous game.

NAME
my_mastermind

SYNOPSIS
my_mastermind [-ct]

DESCRIPTION
Mastermind is a game composed of 9 pieces of different colors. A secret code is then composed of 4 distinct pieces.

The player has 10 attempts to find the secret code. After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.

If the player finds the code, he wins, and the game stops. A misplaced piece is a piece that is present in the secret code butthat is not in a good position.

You must read the player's input from the standard input.

Your program will also receive the following parameters: -c [CODE]: specifies the secret code. If no code is specified, a random code will be generated. -t [ATTEMPTS]: specifies the number of attempts; by default, the playerhas 10 attempts.

Example 00

PROMPT>./my_mastermind -c "0123"
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
Congratz! You did it!.

#Technical information
you must create a Makefile, and the ouput is the command itself It will contain rule all/clean/fclean (re => fclean + all)

You can use:

printf(3)
write(2)
read(2)
rand() (/ srand())
time()
atoi()
strcmp()
You can NOT use:
Any functions/syscalls which does not appear in the previous list
Yes, it includes exit.

#Technical information
you must create a Makefile, and the ouput is the command itself It will contain rule all/clean/fclean (re => fclean + all).
#Your mastermind needs to handle the sequence Ctrl + d. It's End Of File. It's consider as a normal execution.

#Output formats
When your program starts, you must display:
Will you find the secret code?
Please enter a valid guess
When the user wins, you must display:
Congratz! You did it!
When the user enters an invalid code, you must respect the following format:
Well placed pieces: X
Misplaced pieces: Y
X and Y are two digits with the correct values.

Requirements
Your code must be compiled with the flags -Wall -Wextra -Werror.
Multiline macros are forbidden
You should have multiple file .c but it's forbidden to include them (#include another_file.c) use your Makefile to compile them together.
Macros with logic (while/if/variables/...) are forbidden.
