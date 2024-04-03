# arc-01-my_mastermind
# Task
This code program creates a "hmm" game. In this game, the user has to find the 4-digit numerical code selected by the computer. Each number can be between 0 and 9, and the numbers must be different from other numbers. The user enters 4 numbers each time and the program compares with the code selected by the computer. If the user places the numbers correctly, the program will say "Congratz! You did it!" writes and the game ends. Otherwise, the program tells the user how the example was placed correctly and how it was placed incorrectly, and gives the user the opportunity to try again.
# Description
*This code program is written in C language. This program has the following features:
*uniq_check: This function checks whether the given character occurs in the given string.
*unique: This function checks for non-repeating characters in the given string.
*code_creat: This function generates a random 4-digit numeric code.
*input_code: Accepts the code entered by the user.
*well_miss: Compares the code entered by the user with the code selected by the computer and counts the number of correct numbers.
*wrong_check: Checks the code entered by the user and gives an opportunity to try again if it is wrong.
*start: Helper function to start the game.
*main: Main function. The command takes string arguments and specifies the correct code to end the game.
# Installation
*Follow these steps to download this code:

*git clone <repository_url>
*cd <cloned_directory>
*gcc -o hmm hmm.c ./h/my_string.c
# Usage
*Run the following commands to run the program:

*./hmm -c <secret_code> -t <rounds>
*For example:
./hmm -c 1234 -t 10
This command will run the program to start a 10-try game that selects the numeric code 1234.