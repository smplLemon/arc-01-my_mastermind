#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

void generateSecretCode(char* secretCode) {
    const char pieces[] = "012345678";
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        secretCode[i] = pieces[rand() % 9];
    }
    secretCode[CODE_LENGTH] = '\0';
}


int my_strlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}


void evaluateGuess(const char* secretCode, const char* guess, int* wellPlaced, int* misplaced) {
    *wellPlaced = 0;
    *misplaced = 0;

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] == secretCode[i]) {
            (*wellPlaced)++;
        }
    }
    for (int i = 0; i < CODE_LENGTH; i++) {
        for (int j = 0; j < CODE_LENGTH; j++) {
            if (i != j && guess[i] == secretCode[j]) {
                (*misplaced)++;
                break;
            }
        }
    }
}

int isValidGuess(const char* guess) {
    if (my_strlen(guess) != CODE_LENGTH) {
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

void playGame() {
    char secretCode[CODE_LENGTH + 1];
    char guess[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;
    int round = 0;
    generateSecretCode(secretCode);
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    while (attempts > 0) {
        printf("---\nRound %d\n", round);
        scanf("%s", guess);
        if (!isValidGuess(guess)) {
            printf("Wrong input!\n");
            continue;
        }
        int wellPlaced, misplaced;
        evaluateGuess(secretCode, guess, &wellPlaced, &misplaced);
        printf("Well-placed pieces: %d\n", wellPlaced);
        printf("Misplaced pieces: %d\n", misplaced);
        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz you did it!");
            return;
        }
        attempts--;
        round++;
    }
    printf("Game over! ");
}
void parseCommandLineArgs(char* secretCode, int argc, char* argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "c:t:")) != -1) {
        switch (opt) {
            case 'c':
                strncpy(secretCode, optarg, CODE_LENGTH);
                secretCode[CODE_LENGTH] = '\0';
                break;
            default:
                fprintf(stderr, "Usage: %s [-c CODE]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (secretCode[0] == '\0') {
        generateSecretCode(secretCode);
    }
}

int main(int argc, char* argv[]) {
    char secretCode[CODE_LENGTH + 1] = "";
    parseCommandLineArgs(secretCode, argc, argv);
    playGame();
    return 0;
}

