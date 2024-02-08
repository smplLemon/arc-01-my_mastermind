#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mastermind.h" 
#define LN 4

int main(int ac, char *av[]) {
    char code[5];

    if (ac > 1 && strcmp(av[1], "-c") == 0 && ac > 2) {
        strncpy(code, av[2], LN);
        code[LN] = '\0'; 
    } else {
        srand(time(NULL));
        for (int i = 0; i < LN; ++i) {
            code[i] = '0' + rand() % 9;
        }
        code[LN] = '\0'; 
    }

    init(); 
    play(10);

    return 0;
}
