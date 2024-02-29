#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind_h.h"

int rd_input(char* gues){
    if (read(0, gues, 4 + 1) == -1){
        printf("Error reading input.\n");
        return 1;
    }
    return 0;
}

int is_correct(int well_placed){
    if (well_placed == 4){
        printf("Congratz! You guessed it right!\n");
        return 1;
    }
    return 0;
}
void prnt_res(int well_placed, int misplaced){
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
}
