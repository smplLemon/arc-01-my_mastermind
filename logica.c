#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mastermind_h.h"  
#include "master_h.h"
#define CD_LEN 4

int play_game(char* scrt_cd, int MX_ATMT){
    if(strlen(scrt_cd) != CD_LEN){
        srand(time(NULL));
        randit(scrt_cd);
    }
    char gues[CD_LEN + 1];
    int wel_plcd, misplcd, round = 0;
    printf("Will you find the secret code? \nPlease enter a valid numbers\n");

    while(round < MX_ATMT){
        printf("---\nRound %d\n>", round);
        fflush(stdout);

        if(rd_input(gues) != 0){
            printf("Error reading input.\n");
            continue;  
        }
        gues[CD_LEN] = '\0';

        if(!validation(gues)){
            continue;  
        }
        guess(gues, scrt_cd, &wel_plcd, &misplcd);

        if(is_correct(wel_plcd)){
            free(scrt_cd);
            return EXIT_SUCCESS;
        }
        prnt_res(wel_plcd, misplcd);
        round++;
        
        if(round == 10){
            printf("Sorry, you couldn't find the secret code.\n");
        }
    }
    free(scrt_cd);
    return EXIT_FAILURE;
}
