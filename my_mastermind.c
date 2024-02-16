#include "my_mastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CODE_LENGTH 4

char* parse_arguments(int argc, char *argv[]) {
    char* code = malloc((CODE_LENGTH + 1) * sizeof(char));
    if (code == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        code[i] = rand() % 10 + '0'; 
    }
    code[CODE_LENGTH] = '\0';
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            strncpy(code, argv[i + 1], CODE_LENGTH);
            code[CODE_LENGTH] = '\0';
            i++;
          
            for (int j = 0; j < CODE_LENGTH; j++) {
                if (code[j] < '0' || code[j] > '9') {
                    fprintf(stderr, "Error: Invalid code provided\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    
    return code;
}

void run_mastermind(char* code, int attempts) {
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    
    for (int attempt = 0; attempt < attempts; attempt++) {
        char guess[5];
        printf("---\nRound %d\n>", attempt);
        fflush(stdout);
        
        if (fgets(guess, sizeof(guess), stdin) == NULL) {
            printf("\n");
            break;
        }
        guess[strcspn(guess, "\n")] = '\0'; 
        
        int well_placed = 0;
        int misplaced = 0;
        int code_count[10] = {0};
        int guess_count[10] = {0};
        for (int i = 0; i < CODE_LENGTH; i++) {
            if (code[i] == guess[i]) {
                well_placed++;
            } else {
                code_count[code[i] - '0']++;
                guess_count[guess[i] - '0']++;
            }
        }
        for (int i = 0; i < 10; i++) {
            misplaced += (code_count[i] < guess_count[i]) ? code_count[i] : guess_count[i];
        }
        
        if (well_placed == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            break;
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
        }
    }
}

