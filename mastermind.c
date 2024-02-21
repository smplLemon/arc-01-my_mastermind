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

int checkgues(char *gues, char *code, int LEN){
    int well = 0, misd = 0;
    int *usd_cds = (int *)calloc(LEN, sizeof(int));

    for(int i = 0; i < LEN; ++i){
        if(gues[i] == code[i]){
            well++;
            usd_cds[i] = 1;
        }
    }

    for(int i = 0; i < LEN; ++i){
        if(!usd_cds[i]){
            for(int j = 0; j < LEN; ++j){
                if(i != j && gues[i] == code[j]){
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

void play(int atm, char *code, int LEN){
    char gues[LEN + 1];

    for(int rnd = 0; rnd < atm; ++rnd){
        printf("\nRound %d\n>", rnd + 1);

        if(fgets(gues, LEN + 2, stdin) == NULL){
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        if(gues[strlen(gues) - 1] != '\n'){
            printf("Invalid input! Please enter %d digits.\n", LEN);
            while (getchar() != '\n'); 
            rnd--;
            continue;
        }

        gues[strcspn(gues, "\n")] = '\0';

        if(checkgues(gues, code, LEN)){
            printf("Congratz! You did it!\n");
            return;
        }
    }

    printf("Game over! You are failed.\n");
}
