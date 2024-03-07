#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mastermind_h.h"  
#include "master_h.h"
#define CD_LEN 4

char* initialize_game(int ac, char** av, int* MX_ATMT){
    char* scrt_cd = calloc(sizeof(char), CD_LEN + 1);
    if(scrt_cd == NULL){
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < ac; i++){
        if(strcmp(av[i], "-c") == 0 && i + 1 < ac){
            strncpy(scrt_cd, av[i + 1], CD_LEN);
            scrt_cd[CD_LEN] = '\0';
        } 
        else if(strcmp(av[i], "-t") == 0 && i + 1 < ac){
            *MX_ATMT = atoi(av[i + 1]);
        }
    }
    return scrt_cd;
}
