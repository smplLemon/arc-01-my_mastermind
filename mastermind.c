#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h> 
#include "mastermind.h"
#define LN 4
#define ou 0

void init(void) {
    printf("Find the Code\nGuess...\n");
    printf("---\n");
}

void display(int well, int misd) {
    printf("Well-placed: %d\nMis-placed: %d\n---\n", well, misd);
}

int checkGuess(char *guess, char *code) {
    int well = ou;
    int misd = ou;
    int usdcd[LN] = {ou}; 

    for(int i = ou; i < LN; ++i) {
        if(guess[i] == code[i]) {
            well++;
            usdcd[i] = 1;
        }
    }

    for(int i = ou; i < LN; ++i) {
        if(!usdcd[i]) {
            for(int j = ou; j < LN; ++j) {
                if(i != j && guess[i] == code[j]) {
                    misd++;
                    break;
                }
            }
        }
    }

    display(well, misd);
    return well == LN;
}

void play(int atm) {
    char guess[5];

    for(int round = 1; round <= atm; ++round) {
        printf("Round %d\n>", round);

        for(int i = ou; i < LN; ++i) {
            char c;
            if(read(ou, &c, 1) == -1) {
                perror("Error reading input");
                exit(EXIT_FAILURE);
            }
            if(c == '\n') { 
                i--; 
                continue;
            }
            if(!isdigit(c)) { 
                printf("Invalid input! Please enter digits.\n");
                i--; 
                continue;
            }
            guess[i] = c; 
        }
        guess[LN] = '\0'; 

        if(checkGuess(guess, "4321")) {
            printf("Congrats!\n");
            return;
        }
    }

    printf("Game over! You lost.\n"); 
}
