#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

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


int main(int argc, char *argv[]) {
    srand(time(NULL));

    char secretCode[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    if (argc > 1) {
        for (int i = 1; i < argc; i += 2) {
            if (argv[i][0] == '-' && (i + 1) < argc) {
                switch (argv[i][1]) {
                    case 'c':
                        strncpy(secretCode, argv[i + 1], CODE_LENGTH);
                        secretCode[CODE_LENGTH] = '\0';
                        break;
                    case 't':
                        attempts = atoi(argv[i + 1]);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (secretCode[0] == '\0') {
        generateSecretCode(secretCode);
    }

    printWelcomeMessage();

    for (int round = 0; round < attempts; ++round) {
        char guess[CODE_LENGTH + 1];
        printRound(round);

        printf(">");

        int bytesRead = read(0, guess, CODE_LENGTH + 1);
        if (bytesRead <= 0) {
            printf("\n");
            break;
        }

        guess[CODE_LENGTH] = '\0';

        if (!isValidInput(guess)) {
            round--;
            continue;
        }

        int wellPlaced, misplaced;
        checkGuess(secretCode, guess, &wellPlaced, &misplaced);
        printResult(wellPlaced, misplaced);

        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            break;
        }
    }

    return 0;
}