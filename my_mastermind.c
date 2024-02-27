#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

void generateSecretCode(char* secretCode) {
    // Generate a random secret code
    char pieces[] = "012345678";
    int i;
    srand(time(NULL));
    for (i = 0; i < CODE_LENGTH; i++) {
        int index = rand() % strlen(pieces);
        secretCode[i] = pieces[index];
    }
    secretCode[CODE_LENGTH] = '\0';
}

void evaluateGuess(char* secretCode, char* guess, int* wellPlaced, int* misplaced) {
    int i, j;
    int codeCount[10] = {0};
    int guessCount[10] = {0};
    *wellPlaced = 0;
    *misplaced = 0;

    // Count the occurrences of each piece in the secret code and the guess
    for (i = 0; i < CODE_LENGTH; i++) {
        codeCount[secretCode[i] - '0']++;
        guessCount[guess[i] - '0']++;
    }

    // Calculate the number of well-placed pieces
    for (i = 0; i < CODE_LENGTH; i++) {
        if (secretCode[i] == guess[i]) {
            (*wellPlaced)++;
            codeCount[secretCode[i] - '0']--;
            guessCount[guess[i] - '0']--;
        }
    }

    // Calculate the number of misplaced pieces
    for (i = 0; i < 10; i++) {
        int minCount = codeCount[i] < guessCount[i] ? codeCount[i] : guessCount[i];
        *misplaced += minCount;
    }
}

int main(int argc, char* argv[]) {
    char secretCode[CODE_LENGTH + 1];
    char guess[CODE_LENGTH + 1];
    int wellPlaced, misplaced;
    int attempts = MAX_ATTEMPTS;

    // Parse command line arguments
    if (argc > 1) {
        if (strcmp(argv[1], "-c") == 0 && argc > 2) {
            strncpy(secretCode, argv[2], CODE_LENGTH);
            secretCode[CODE_LENGTH] = '\0';
        }
        if (strcmp(argv[3], "-t") == 0 && argc > 4) {
            attempts = atoi(argv[4]);
        }
    } else {
        generateSecretCode(secretCode);
    }

    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    while (attempts > 0) {
        printf("---\n");
        printf("Round %d\n", MAX_ATTEMPTS - attempts);

        if (fgets(guess, sizeof(guess), stdin) == NULL) {
            break;
        }

        guess[strcspn(guess, "\n")] = '\0';

        if (strlen(guess) != CODE_LENGTH) {
            printf("Wrong input!\n");
            continue;
        }

        evaluateGuess(secretCode, guess, &wellPlaced, &misplaced);

        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            break;
        } else {
            printf("Well placed pieces: %d\n", wellPlaced);
            printf("Misplaced pieces: %d\n", misplaced);
        }

        attempts--;
    }

    return 0;
}
