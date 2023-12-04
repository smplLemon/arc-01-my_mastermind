#include "mastermind.h"


char* random_code(char* random_code) {
    const char numbers[] = "0123456789";

    for (int i = 0; i < 4; i++) {
        random_code[i] = numbers[rand() % 10];
    }

    random_code[4] = '\0';

    return random_code;
}

void evaluate_guess(char* guess, char* secret_code, int* correct_place, int* misplaced) {
    int guess_histogram[10] = {0};
    int secret_code_histogram[10] = {0};
    *correct_place = 0;
    *misplaced = 0;

    for (int i = 0; i < 4; i++) {
        if (guess[i] == secret_code[i]) {
            (*correct_place)++;
        } else {
            guess_histogram[guess[i] - '0']++;
            secret_code_histogram[secret_code[i] - '0']++;
        }
    }

    for (int i = 0; i < 10; i++) {
        *misplaced += (secret_code_histogram[i] < guess_histogram[i]) ? secret_code_histogram[i] : guess_histogram[i];
    }
}

int is_input_valid(char* input) {
    if (strlen(input) != 4) {
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0;
        }
    }

    return 1;
}
