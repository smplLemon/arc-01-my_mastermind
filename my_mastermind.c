#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

int isDuplicate(char* str, int index);
int validateInput(char* input);
int countWellPlaced(char* guess, char* secretCode);
int countMisplaced(char* guess, char* secretCode);
char* generateRandomCode();
void showGameInstructions();
void displayRound(int round);
void showError();
char* readGuess();
void playGame(char* secretCode, int attempts);

#define MAX_ROUNDS 10

void playGame(char* secretCode, int max_rounds);

int main(int argc, char** argv) {
    char* secretCode = NULL;
    int max_rounds = MAX_ROUNDS;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            secretCode = argv[i + 1];
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            max_rounds = atoi(argv[i + 1]);
            if (max_rounds < 1 || max_rounds > MAX_ROUNDS) {
                printf("Invalid maximum rounds. Using default value (%d).\n", MAX_ROUNDS);
                max_rounds = MAX_ROUNDS;
            }
        }
    }

    if (secretCode == NULL) {
        secretCode = generateRandomCode();
    }

    playGame(secretCode, max_rounds);

    return 0;
}


int isDuplicate(char* str, int index) {
    for (int i = 0; i < index; i++) {
        if (str[i] == str[index]) {
            return 1;
        }
    }
    return 0;
}

int validateInput(char* input) {
    int len = strlen(input);
    return len == CODE_LENGTH && sscanf(input, "%4[0-9]", input) == 1;
}

int countWellPlaced(char* guess, char* secretCode) {
    int count = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        count += (guess[i] == secretCode[i]);
    }
    return count;
}

int countMisplaced(char* guess, char* secretCode) {
    int count = 0;
    int guessCount[10] = {0};
    int secretCount[10] = {0};
    for (int i = 0; i < CODE_LENGTH; i++) {
        guessCount[guess[i] - '0']++;
        secretCount[secretCode[i] - '0']++;
    }
    for (int i = 0; i < 10; i++) {
        count += (guessCount[i] < secretCount[i] ? guessCount[i] : secretCount[i]);
    }
    count -= countWellPlaced(guess, secretCode);
    return count;
}

char* generateRandomCode() {
    char* code = malloc(CODE_LENGTH + 1);
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH;) {
        char digit = rand() % 10 + '0';
        if (!isDuplicate(code, i)) {
            code[i++] = digit;
        }
    }
    code[CODE_LENGTH] = '\0';
    return code;
}

void showGameInstructions() {
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
}

void displayRound(int round) {
    printf("---\nRound %d\n", round);
    write(1, ">", 1);
}

void showError() {
    printf("Wrong input!\n");
    write(1, ">", 1);
    fflush(stdout);
}

char* readGuess() {
    char* guess = malloc(CODE_LENGTH + 1);
    char ch;
    int i;
    int seen[10] = {0};

    for (i = 0; read(0, &ch, 1); i++) {
        if (ch == '\n') {
            guess[i] = '\0';
            
            int valid = 1;
            for (int j = 0; guess[j] != '\0'; j++) {
                if (guess[j] < '0' || guess[j] > '9') {
                    valid = 0;
                    break;
                }
                int digit = guess[j] - '0';
                if (seen[digit]) {
                    valid = 0;
                    break;
                }
                seen[digit] = 1;
            }
            
            if (valid && i == CODE_LENGTH) {
                return guess;
            } else {
                showError();
                free(guess);
                return readGuess();
            }
        }
        
        guess[i] = ch;
    }

    free(guess);
    return "abc";
}

void playGame(char* secretCode, int max_rounds) {
    showGameInstructions();
    char* guess;
    for (int i = 0; i < max_rounds; i++) { 
        displayRound(i);
        guess = readGuess();
        if (strcmp(guess, "abc") == 0) {
            return;
        }
        int wellPlaced = countWellPlaced(guess, secretCode);
        if (wellPlaced == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            return;
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, countMisplaced(guess, secretCode));
        }
    }
}
