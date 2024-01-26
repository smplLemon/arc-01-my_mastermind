#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mastermind.h"

void init(char *kod) {
    printf("Find the Cod\n Guess...\n");
    printf("---\n");
}

void display(int well, int misd) {
    printf("Well-placed: %d\nMisplaced: %d\n---\n", well, misd);
}

int checkgess(char *gess, char *kod){
    (void)kod;

    int well = 0;
    int misd = 0;

    for (int i = 0; i < 4; ++i) {
        if (gess[i] == kod[i]) {
            well++;
        } else {
            for (int j = 0; j < 4; ++j) {
                if (i != j && gess[i] == kod[j]) {
                    misd++;
                    break;
                }
            }
        }
    }

    display(well, misd);

    return well == 4;
}

void play(int atm) {
    char gess[5];

    for (int round = 0; round < atm; ++round) {
        printf("Round %d\n>", round);
        
        for (int i = 0; i < 4; ++i) {
            char c;
            if (read(0, &c, 1) <= 0 || c == '\n') {
                exit(EXIT_SUCCESS); 
            }
            gess[i] = isdigit(c) ? c : '0'; 
        }
        gess[4] = '\0';

        if (checkgess(gess, "0123")) {
            printf("Congrats!\n");
            return;
        }
    }

    printf("Game over! U r lost.\n");
}
