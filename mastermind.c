#include "mastermind.h"

void generateSecretCode(char *secretCode) {
    for (int i = 0; i < CODE_LENGTH; ++i) {
        secretCode[i] = '0' + rand() % 9;
    }
    secretCode[CODE_LENGTH] = '\0';
}

void printWelcomeMessage() {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
}

void printRound(int round) {
    printf("---\nRound %d\n", round);
}

void printResult(int wellPlaced, int misplaced) {
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
}

int isValidInput(const char *input) {
    if (strlen(input) != CODE_LENGTH) {
        printf("Wrong input!\n");
        return 0;
    }

    for (int i = 0; i < CODE_LENGTH; ++i) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 0;
        }
    }

    return 1;
}

void checkGuess(const char *secretCode, const char *guess, int *wellPlaced, int *misplaced) {
    *wellPlaced = 0;
    *misplaced = 0;

    for (int i = 0; i < CODE_LENGTH; ++i) {
        if (guess[i] == secretCode[i]) {
            (*wellPlaced)++;
        } else {
            for (int j = 0; j < CODE_LENGTH; ++j) {
                if (j != i && guess[i] == secretCode[j]) {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
}