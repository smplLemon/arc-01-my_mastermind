#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define CODE_LENGTH 4

void generateSecretCode(char *secret) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < CODE_LENGTH; ++i) {
        secret[i] = rand() % 10 +  '0';
    }
    secret[CODE_LENGTH] = '\0';
}

bool isValidGuess(char *guess) {
    if (strlen(guess) != CODE_LENGTH) {
        return false;
    }

    for (int i = 0; i < CODE_LENGTH; ++i) {
        if (guess[i] < '0' || guess[i] > '9') {
            return false;
        }
    }

    for (int i = 0; i < CODE_LENGTH - 1; ++i) {
        for (int j = i + 1; j < CODE_LENGTH; ++j) {
            if (guess[i] == guess[j]) {
                return false;
            }
        }
    }

    return true;
}

char *getUserGuess() {
    printf(">");
    fflush(stdout);
    char *guess = malloc(sizeof(char) * (CODE_LENGTH + 1));
    scanf("%4s", guess);
    return guess;
}

void evaluateGuess(char *secret, char *guess) {
    int wellPlaced = 0;
    int misplaced = 0;

    for (int i = 0; i < CODE_LENGTH; ++i) {
        if (guess[i] == secret[i]) {
            wellPlaced++;
        } else if (strchr(secret, guess[i]) != NULL) {
            misplaced++;
        }
    }

    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
}

int main() {
    char secret[CODE_LENGTH + 1];
    generateSecretCode(secret);

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (int round = 0; round < 10; round++) {
        printf("---\n");
        printf("Round %d\n", round + 0);

        char *guess = getUserGuess();

        if (!isValidGuess(guess)) {
            printf("Wrong input!\n");
            free(guess);
            round--;
            continue;
        }

        if (strcmp(secret, guess) == 0) {
            printf("Congrats! You did it!\n");
            free(guess);
            return 0;
        } else {
            evaluateGuess(secret, guess);
        }

        free(guess);
    }

    printf("Game over! You couldn't find the secret code.\n");
    printf("The secret code was: %s\n", secret);

    return 0;
}
