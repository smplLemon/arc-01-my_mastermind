#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10
void generateSecretCode(char* code) {
    srand(time(NULL));

    for (int i = 0; i < CODE_LENGTH; i++) {
        code[i] = '0' + rand() % 9;
    }

    code[CODE_LENGTH] = '\0';
}

void evaluateGuess(const char* secretCode, const char* guess, int* wellPlaced, int* misplaced) {
    int secretCount[10] = {0};
    int guessCount[10] = {0};

    *wellPlaced = 0;
    *misplaced = 0;

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (secretCode[i] == guess[i]) {
            (*wellPlaced)++;
        } else {
            secretCount[secretCode[i] - '0']++;
            guessCount[guess[i] - '0']++;
        }
    }

    for (int i = 0; i < 10; i++) {
        *misplaced += (secretCount[i] < guessCount[i]) ? secretCount[i] : guessCount[i];
    }
}

int main(int argc, char* argv[]) {
    char secretCode[CODE_LENGTH + 1];
    char guess[CODE_LENGTH + 1];
    int wellPlaced, misplaced;
    int attempts = MAX_ATTEMPTS;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-c") == 0) {
                if (i + 1 < argc) {
                    strncpy(secretCode, argv[i + 1], CODE_LENGTH);
                } else {
                    printf("Invalid secret code.\n");
                    return 1;
                }
            } else if (strcmp(argv[i], "-t") == 0) {
                if (i + 1 < argc) {
                    attempts = atoi(argv[i + 1]);
                } else {
                    printf("Invalid number of attempts.\n");
                    return 1;
                }
            }
        }
    } else {
        generateSecretCode(secretCode);
    }

    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    for (int round = 0; round < attempts; round++) {
        printf("---\nRound %d\n>", round);

        char c;
        int index = 0;

        while (read(STDIN_FILENO, &c, 1) > 0) {
            if (c == '\n') {
                guess[index] = '\0';
                break;
            }

            guess[index] = c;
            index++;

            if (index >= CODE_LENGTH) {
                break;
            }
        }

        if (index != CODE_LENGTH) {
            printf("Wrong input!\n");
            continue;
        }

        evaluateGuess(secretCode, guess, &wellPlaced, &misplaced);

        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            return 0;
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
        }
    }

    return 0;
}
