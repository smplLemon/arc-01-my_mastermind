#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mastermind.h"

int main(int ac, char *av[]){
    char kod[5]; 

    if(ac > 1 && strcmp(av[1], "-c")== 0 && ac > 2){
        strncpy(kod, av[2], 4);
        kod[4] = '\0';
    }
    else{
        srand(time(NULL));
        for(int i = 0; i < 4; ++i){
            kod[i] = '0' + rand() % 9;
        }
        kod[4] = '\0';
    }

    init(kod); 
    play(10); 
    return 0;
}
 