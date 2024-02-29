#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind_h.h"
#define CD_LEN 4

char* scrt_cd = NULL;
int MX_ATMT = 11; 

int main(int ac, char** av){
    scrt_cd = calloc(sizeof(char), CD_LEN + 1);
    if(scrt_cd == NULL) {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    for(int i = 1; i < ac; i++){
        if(strcmp(av[i], "-c") == 0 && i + 1 < ac){
            strncpy(scrt_cd, av[i + 1], CD_LEN);
            scrt_cd[CD_LEN] = '\0';
        } else if(strcmp(av[i], "-t") == 0 && i + 1 < ac){
            MX_ATMT = atoi(av[i + 1]);
        }
    }
    if(strlen(scrt_cd) != CD_LEN){
        srand(time(NULL));
        randit(scrt_cd);
    }
    char gues[CD_LEN + 1];
    int wel_plcd, misplcd, round = 0;
    printf("Can you guess the secret code?\nPlease enter a valid guess\n");
    
    while(round < MX_ATMT){
        printf("---\nRound %d\n>", round);
        fflush(stdout);
        if(rd_input(gues) != 0){
            printf("Error reading input.\n");
            free(scrt_cd);
            return EXIT_FAILURE;
        }
        gues[CD_LEN] = '\0';

        if(!validation(gues)){
            printf("Invalid input!\n");
            continue;
        }
        guess(gues, scrt_cd, &wel_plcd, &misplcd);

        if(is_correct(wel_plcd)){
            free(scrt_cd);
            return EXIT_SUCCESS;
        }
        prnt_res(wel_plcd, misplcd);
        round++;
    }
    free(scrt_cd);
    return EXIT_SUCCESS;
}
