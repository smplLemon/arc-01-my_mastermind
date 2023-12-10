#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "my_mastermind.h"

#define CODE_LENGTH 4

void generate_random_code(char* random_code) {
    const char numbers[] = "0123456789";
    for (int i = 0; i < CODE_LENGTH; i++) {
        random_code[i] = numbers[rand() % 10];
    }
    random_code[CODE_LENGTH] = '\0';
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

int is_valid_input(const char* input) {
    if (strlen(input) != CODE_LENGTH || strspn(input, "0123456789") != CODE_LENGTH) {
        return 0;
    }

    for (int i = 0; i < CODE_LENGTH - 1; i++) {
        for (int j = i + 1; j < CODE_LENGTH; j++) {
            if (input[i] == input[j]) {
                return 0;
            }
        }
    }
    
    return 1;
}
