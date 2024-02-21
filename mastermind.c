#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mastermind.h"

void init(void){ 
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
}

void display(int well, int misd){
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well, misd);
}

int checkGuess(char *guess, char *code, int LEN){
    int well = 0, misd = 0;
    int *usd_cds = (int *)calloc(LEN, sizeof(int));

    for(int i = 0; i < LEN; ++i){
        if(guess[i] == code[i]){
            well++;
            usd_cds[i] = 1;
        }
    }

    for(int i = 0; i < LEN; ++i){
        if(!usd_cds[i]){
            for(int j = 0; j < LEN; ++j){
                if(i != j && guess[i] == code[j]){
                    misd++;
                    break;
                }
            }
        }
    }

    display(well, misd);
    free(usd_cds);
    return well == LEN;
}

void play(int attempts, char *code, int LEN){
    char guess[LEN + 1];

    for(int round = 0; round < attempts; ++round){
        printf("\nRound %d\n>", round + 1);

        if(fgets(guess, LEN + 2, stdin) == NULL){
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        if(guess[strlen(guess) - 1] != '\n'){
            printf("Invalid input! Please enter %d digits.\n", LEN);
            while (getchar() != '\n'); 
            round--;
            continue;
        }

        guess[strcspn(guess, "\n")] = '\0';

        if(checkGuess(guess, code, LEN)){
            printf("Congratz! You did it!\n");
            return;
        }
    }

    printf("Game over! You are failed.\n");
}
