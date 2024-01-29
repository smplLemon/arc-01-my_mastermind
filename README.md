# arc-01-my_mastermind


## Task
What is the problem? And where is the challenge?

Since I haven't worked in C for a long time, I had to remember some functions and I had a hard time compiling some functions.

## Description
How have you solved the problem?

My friends helped me to solve this problem. For example I had to accept "string" from the user every time. But I didn't know to accept "String". A boy named Ulugbek helped me make it

## Installation
How to install your project? npm install? make? make re?

I #include <stdio.h> in my program #include <string.h> #include <stdlib.h> #include <time.h> #include <stdbool.h> I used the #include <unistd.h> libraries

## Usage
How does it work?

In this project, I downloaded each job one by one into functions. The first thing I started with was whether there is a secret key or should I enter it through the Random function. If a secret key is entered after -c, it will save it, otherwise it will generate it randomly. I created a random function for each number. If the random number is not equal to the previous numbers and if it is not 9, it will take it, otherwise it will randomize it again. If a number is given after -t, the round will change, otherwise it will set the number of rounds to 10. Now the user starts playing. If a number larger or smaller than 4 digits is entered, or if one number is used more than once, the answer "wrong input" is returned and the round is replayed, that is, the order number of the round does not change. "Congratz! You did it!" the answer is returned if it cannot find "Well placed pieces:n
 Miss placed pieces:m will be returned. We repeat this game until the number of rounds. If ctr + D is pressed, the program will exit. I did it using ASCII code.

