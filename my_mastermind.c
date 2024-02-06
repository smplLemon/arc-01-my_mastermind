#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#define CODE_SIZE 4

void generateSecretCode(char code[CODE_SIZE + 1]);
bool getUserGuess(char code[CODE_SIZE + 1]);
void evaluateGuess(const char code[CODE_SIZE + 1], const char secretCode[CODE_SIZE + 1], int *wellPlaced, int *misplaced);

int main(int argc, char **argv) {
    srand(time(NULL));


    short maxAttempt = 10;
    char secretCode[CODE_SIZE + 1];
    char userGuess[CODE_SIZE + 1];
    int wellPlaced, misplaced;

    generateSecretCode(secretCode);

    for (int i = 1; i < argc - 1; i++) {
        if (argv[i][0] != '-' argv[i][1] == '\0') {
            continue;
        }

        char flag = argv[i][1];
        i++;

        switch (flag) {
            case 'c':
                if (argv[i][0] != '\0') {
                    for (short j = 0; j < CODE_SIZE; j++) {
                        secretCode[j] = argv[i][j];
                    }
                }
                break;

            case 't':
                maxAttempt = atoi(argv[i]);
                break;

            default:
                break;
        }
    }

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (int attempts = 0; attempts < maxAttempt; attempts++) {
        printf("---\nRound %d\n", attempts);

        if (!getUserGuess(userGuess)) {
            printf("Wrong input!\n");
            continue;
        }

        evaluateGuess(userGuess, secretCode, &wellPlaced, &misplaced);

        if (wellPlaced == CODE_SIZE) {
            printf("Congratz! You did it!\n");
            return 0;
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
        }
    }

    printf("Sorry, you couldn't find the secret code. It was: %s\n", secretCode);

    return 0;
}

void generateSecretCode(char code[CODE_SIZE + 1]) {
    char possible[10] = "0123456789";

    for (short i = 0; i < CODE_SIZE; i++) {
        short j = rand() % (10 - i);
        code[i] = possible[j];
        possible[j] = possible[9 - i];
    }

    code[CODE_SIZE] = '\0';
}

bool getUserGuess(char code[CODE_SIZE + 1]) {
    short valid = 0;
    write(1, ">", 1);

    for (short i = 0; i < CODE_SIZE; i++) {
        if (read(0, &code[i], 1) == 0 code[i] == '\n') {
            break;
        }

        if (i == CODE_SIZE || (code[i] >= '0' && code[i] <= '9')) {
            valid++;
        }
    }

    code[CODE_SIZE] = '\0';
    return valid == CODE_SIZE;
}

void evaluateGuess(const char code[CODE_SIZE + 1], const char secretCode[CODE_SIZE + 1], int *wellPlaced, int *misplaced) {
    *wellPlaced = 0;
    *misplaced = 0;

    for (short i = 0; i < CODE_SIZE; i++) {
        for (short j = 0; j < CODE_SIZE; j++) {
            if (code[i] == secretCode[j]) {
                if (i == j) {
                    (*wellPlaced)++;
                } else {
                    (*misplaced)++;
                }
                break;
            }
        }
    }
}
