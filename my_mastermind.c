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

void evaluateGuess(char* secretCode, char* guess, int* wellPlaced, int* misplaced) {
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

int isValidGuess(char* guess) {
    if (guess[CODE_LENGTH] != '\0') {
        return 0;
    }

    for (int i = 0; i < CODE_LENGTH; i++) {
        int valid = 0;
        for (int j = 0; j < (int)(sizeof(PIECES) - 1); j++) {
            if (guess[i] == PIECES[j]) {
                valid = 1;
                break;
            }
        }
        if (!valid) {
            return 0;
        }
    }

    return 1;
}

int isStopCommand(char* guess) {
    char command[5];
    strncpy(command, guess, 4);
    command[4] = '\0';
    for (int i = 0; i < 4; i++) {
        command[i] = tolower(command[i]);
    }
    return (strcmp(command, "stop") == 0);
}

int main() {
    char secretCode[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    generateSecretCode(secretCode);

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    char guess[CODE_LENGTH + 1];
    int wellPlaced, misplaced;

    for (int round = 0; round < attempts; round++) {
        printf("---\n");
        printf("Round %d\n>", round);

        int result = scanf("%s", guess);

        if (result == EOF) {
            printf("End of input. Exiting...\n");
            break;
        }

        if (isStopCommand(guess)) {
            printf("Game stopped by the player. Exiting...\n");
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
