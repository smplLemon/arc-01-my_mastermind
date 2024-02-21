#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mastermind.h"
#define LEN 4
#define NUMS 9
#define DFLT_ATM 10

int main(int ac, char *av[]) {
    char code[LEN + 1];
    int atm = DFLT_ATM;

    srand(time(NULL));

    for(int i = 1; i < ac; i += 2){
        if(strcmp(av[i], "-c") == 0){
            strncpy(code, av[i + 1], LEN);
            code[LEN] = '\0';
        } else if(strcmp(av[i], "-t") == 0){
            atm = atoi(av[i + 1]);
        }
    }

    if(code[0] == '\0'){
        for(int i = 0; i < LEN; ++i){
            code[i] = '0' + rand() % NUMS;
        }
        code[LEN] = '\0';
    }

    init();
    play(atm, code, LEN);

    return 0;
}
