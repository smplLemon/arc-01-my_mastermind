# Description
- This program parses the text received as command line arguments and finds how many times each character occurs. It then prints the repeating characters and their numbers to the screen.
# Task
- The my_str function takes a string of characters and calculates the length of the string. This function scans the incoming character string, finds the number of characters up to the null character ('\0'), and returns the result.
- The function my_array takes an array of integers (array) and a string of characters (str). This function scans an array of characters and uses the ASCII value of each character to increment the corresponding index in the "array" array. If the character is a double quote (""), it ignores that character. This function returns the number of occurrences of each character in the character array in the array array.
# Usage
- The program analyzes the characters for each text and prints the repeated characters and their numbers on the screen.
- For example, when you run the above command, you might get the following output:
,:2
H: 1
T: 1
a: 1
d:1
e: 1
i: 2
l: 3
it is: 2
r: 1
p:3
t:4
u:1
w: 1
- This output shows the number of occurrences of characters and their ASCII values.
# Installation
- By using GCC compilation
gcc my_mastermind.c -o
mastermind 
- This command compiles a file named mastermind.c to create an executable named program.
- By passing texts as command line arguments when running the program. For example:
./mastermind "Hello world!" "This is a test."
- This command starts an executable program and says "Hello, world!" and "This is a test." gives its text as an argument to the program.