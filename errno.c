#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <unistd.h>
#include "mastermind_h.h"
#include "master_h.h"
#define CD_LEN 4

int rd_input(char* guess){
    int chars_read = 0;
    char result;
    int frst_rn = 1;
    int count;
    
    while((count = read(STDIN_FILENO, &result, 1)) != -1){
        if(frst_rn && !count){
            exit(0);
        }
        if(frst_rn){
            frst_rn = 0;
        }
        
        if(result == '\n'){   
            guess[chars_read] = '\0';
            return 0;
        } 
        else if(chars_read >= CD_LEN){
            while(read(STDIN_FILENO, &result, 1) && result != '\n');
            return 1;
        } 
        else if(result < '0' || result > '9'){
            if(result == '\n'){
                exit(0);
            }
            while(read(STDIN_FILENO, &result, 1) && result != '\n');
            return 1;
        } 
        guess[chars_read++] = result;
    }
    return 1;
}

int is_correct(int wlplcd){
    if(wlplcd == 4){
        printf("Congratz! You did it!\n");
        return 1;
    }
    return 0;
}
void prnt_res(int wlplcd, int misd){
    printf("Well-placed pieces: %d\nMisplaced pieces: %d\n", wlplcd, misd);
}
