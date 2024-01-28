#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10
void generateSecretCode(char* secretCode);
void evaluateGuess(const char* secretCode, const char* guess, int* wellPlaced, int* misplaced);
int isValidGuess(const char* guess);

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
    int round = 0;
    while (attempts > 0) {
        printf("---\nRound %d\n>", round);
        if (read(0, guess, CODE_LENGTH + 1) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        guess[strcspn(guess, "\n")] = '\0';
        if (guess[0] == '\0') {
            break;
        }
        if (!isValidGuess(guess)) {
            printf("Wrong input!\n");
            continue;
        }
        int wellPlaced, misplaced;
        evaluateGuess(secretCode, guess, &wellPlaced, &misplaced);
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            exit(EXIT_SUCCESS);
        }
        attempts--;
        round++;
    }
    printf("Game over! The secret code was %s\n", secretCode);
    exit(EXIT_SUCCESS);
}
void generateSecretCode(char* secretCode) {
    const char pieces[] = "012345678";
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        secretCode[i] = pieces[rand() % 9];
    }
    secretCode[CODE_LENGTH] = '\0';
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
    if (strlen(guess) != CODE_LENGTH) {
        return 0;
    }
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] < '0' || guess[i] > '8') {
            return 0;
        }
    }
    return 1;
}
