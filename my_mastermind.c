#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *my_random() {
    srand(time(NULL));
    char* code = (char *)malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; i++) {
        code[i] = rand() % 9 + '0';
        for (int j = 0; j < i; j++) {    
            if (code[i] == code[j]) {
                i--;
                break;
            }
        }
    }
    code[4] = '\0';
    return code;
}

int is_incorrect(char *input) {
    if (strlen(input) != 4) {
        printf("Wrong input! Please enter 4 digits.\n");
        return 1;
    } 
    
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input! Please enter digits between 0 and 8.\n");
            return 1;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input! Digits should be unique.\n");
                return 1;
            }
        }
    }
    
    return 0;
}

void evaluate_guess(char *code, char *guess) {
    int well = 0, missed = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == guess[i]) well++;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (guess[i] == code[j] && i != j) missed++;
        }
    }
    if (well == 4) {
        printf("Congrats! You found the secret code: %s\n", code);
        exit(0);
    } else {
        printf("Well placed pieces: %d\n", well);
        printf("Misplaced pieces: %d\n", missed);
    }
}

int main(int argc, char **argv) {
    int attempts = 10;
    char *code = NULL;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            attempts = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-c") == 0) {
            code = argv[i + 1];
        }
    }
    
    if (code == NULL) code = my_random();
    
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    
    char input[5];
    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i);
        printf(">");
        fgets(input, sizeof(input), stdin);
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0'; // Removing newline character
        }
        if (is_incorrect(input)) {
            i--; // Decrease attempt if input is incorrect
            continue;
        }
        evaluate_guess(code, input);
    }
    
    printf("Attempts finished. The secret code was: %s\n", code);
    
    return 0;
}
