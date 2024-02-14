#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10
#define PIECES "012345678"

void generateSecretCode(char* secretCode) {
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        secretCode[i] = PIECES[rand() % (int)(sizeof(PIECES) - 1)];
    }
    secretCode[CODE_LENGTH] = '\0';
}

void evaluateGuess(const char* secretCode, const char* guess, int* wellPlaced, int* misplaced) {
    *wellPlaced = 0;
    *misplaced = 0;

    int secretCount[10] = {0};
    int guessCount[10] = {0};

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (secretCode[i] == guess[i]) {
            (*wellPlaced)++;
        } else {
            for (int j = 0; j < (int)(sizeof(PIECES) - 1); j++) {
                if (secretCode[i] == PIECES[j]) {
                    secretCount[j]++;
                    break;
                }
            }
            for (int j = 0; j < (int)(sizeof(PIECES) - 1); j++) {
                if (guess[i] == PIECES[j]) {
                    guessCount[j]++;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < (int)(sizeof(PIECES) - 1); i++) {
        *misplaced += (secretCount[i] < guessCount[i]) ? secretCount[i] : guessCount[i];
    }

    *misplaced -= *wellPlaced;
}

int isValidGuess(const char* guess) {
    if (strlen(guess) != CODE_LENGTH) {
        return 0;
    }
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] < '0' || guess[i] > '8') {
            return 0;
        }
        for (int j = i + 1; j < CODE_LENGTH; j++) {
            if (guess[i] == guess[j]) {
                return 0;
            }
        }
    }
    return 1;
}

int isStopCommand(const char* guess) {
    char command[5];
    strncpy(command, guess, 4);
    command[4] = '\0';
    for (int i = 0; i < 4; i++) {
        command[i] = tolower(command[i]);
    }
    return (strcmp(command, "stop") == 0);
}

int main(int argc, char* argv[]) {
    char secretCode[CODE_LENGTH + 1];
    char guess[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;
    int opt;
    while ((opt = getopt(argc, argv, "c:t:")) != -1) {
        switch (opt) {
            case 'c':
                strncpy(secretCode, optarg, CODE_LENGTH);
                secretCode[CODE_LENGTH] = '\0';
                break;
            case 't':
                attempts = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-c CODE] [-t ATTEMPTS]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (secretCode[0] == '\0') {
        generateSecretCode(secretCode);
    }

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    int wellPlaced, misplaced;

    for (int round = 0; round < attempts; round++) {
        printf("---\nRound %d\n>", round);

        if (scanf("%4s", guess) == EOF) {
            break;
        }

        if (!isValidGuess(guess)) {
            printf("Wrong input!\n");
            round--;
            continue;
        }

        evaluateGuess(secretCode, guess, &wellPlaced, &misplaced);
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);

        if (wellPlaced == CODE_LENGTH) {
            printf("Congrats! You did it!\n");
            break;
        }
    }

    return 0;
}
