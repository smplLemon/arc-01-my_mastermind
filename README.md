## Welcome to my_Mastermind.c

# Task

This code performs a guessing game, that is, it creates a hidden code, checks whether the guess code entered by the user matches the secret code, and prints the result to the terminal. Everyone probably knows the `Mastermind game`, in which the player gets one point for each correct guess, and the player with the most points at the end of the game wins. The main task of my code is to create a simple representation of this `Mastermind game`.
 I hope you will like this code.

I used the libraries in this code:
 `stdio.h` - standard input output; `stdlib.h` - to allocate memory, that is, to allocate space from memory; `time.h` - to generate random numbers, to manage time; `unistd.h` - to read from standard input.

# Description

The `main()` function requires command-line arguments: `argc`, `argv` to determine the hidden code and the number of attempts allowed. This function is mainly responsible for the mygame function.

The `my_game()` function accepts command line arguments as parameters. This function is the main function responsible for starting the guessing game. This function analyzes the command line arguments to determine the hidden code and the number of Mastermind game attempts. Then it uses the provided parameters to start the game. calls another function, the user is prompted to enter guesses, and the program provides feedback on the correctness of each guess.
 Cycles through the command line arguments using a for loop.
 Allocates memory for the secret code. If there is no secret code, it generates a random code using a special `my_random_code()` function.`0 - Round `is declared in this function.

The `right_try_wrong_try()` function takes a secret code and an approximate code as parameters. In this function, correct and wrong attempts are considered. That is, if one of the approximate codes matches the hidden code, the player is given one point. If everything matches, the player wins.

 The `incorrect_input_checking()` function takes an approximate code as a parameter and checks whether the code is entered incorrectly. If more than 4 numbers are entered, or if 1 number is repeated, the function returns 0.

A string is copied using the `my_scanf()` function.

 `my_random_code()` a random code consisting of 4 numbers is generated using a special function.

The `check_mark()` function takes a pointer to a character and a character as parameters. This function checks for a character in the given character string.

 The `my_atoi()` function takes a pointer to a character as a parameter and converts the string representation of an integer to a real integer value.

The `my_strcpy()` function takes two arguments and copies the contents of one string to another.

 The function `my_strcmp()` accepts pointers to two characters as parameters and compares the two strings character by character and returns 0 if they are equal or 1 otherwise.

The `my_strlen()` function takes a pointer to a character as a parameter and calculates the length of the string by iterating through its characters until `'\0'` occurs.

# Installation

To compile the code, use a C compiler such as `gcc`. For example:
```
gcc -o Mastermind my_Mastermind.c
```
# Usage

The game can be executed from the command line with optional parameters:

./mastermind -c [hidden_code] -t [number_of_attempts]

- -c specifies the secret code to be guessed. If not provided, a random code will be generated.
- -t specifies the number of attempts allowed. The default is 10 attempts.
