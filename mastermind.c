#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "my_mastermind.h"

char* generate_random_code(char* random_code) {
    const char numbers[] = "0123456789";
    for (int i = 0; i < 4; i++) {
        random_code[i] = numbers[rand() % 10];
    }
    
    random_code[4] = '\0';

    return random_code;
}

void game_status(char* guess, char* secret_code, int* well_placed, int* misplaced) {
    int guess_hist[10] = {0};
    int secret_hist[10] = {0};
    *well_placed = 0;
    *misplaced = 0;

    for (int i = 0; i < 4; i++) {
        if (guess[i] == secret_code[i]) {
            (*well_placed)++;
        }
        else {
            guess_hist[guess[i] - '0']++;
            secret_hist[secret_code[i] - '0']++;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        if (secret_hist[i] < guess_hist[i]) {
            *misplaced += secret_hist[i];
        }
        else {
            *misplaced += guess_hist[i];
        }
    }
}

int is_correct_input(char* input) {
    if (strlen(input) > 4 || strspn(input, "0123456789") != strlen(input)) {
        return 0;
    }
    else {
        return 1;
    }
}
