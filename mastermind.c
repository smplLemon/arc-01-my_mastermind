#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

int isCorrect(char* str);
int duplicate(char* p1);
char* generateRandomCode();
char* getUserInput();
int countWellPlaced(char* code, char* guess);
int countMisplaced(char* code, char* guess);
void playGame(char* code, int attempts);

int main(int argc, char** argv) {
    int attempts = MAX_ATTEMPTS;
    char* code = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (isCorrect(argv[i + 1]) && duplicate(argv[i + 1])) {
                code = strdup(argv[i + 1]);
            } else {
                code = generateRandomCode();
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            attempts = atoi(argv[++i]);
        }
    }
    if (code == NULL) {
        code = generateRandomCode();
    }
    playGame(code, attempts);
    free(code);
    return 0;
}

int isCorrect(char* str) {
    if (strlen(str) != CODE_LENGTH)
        return 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (!(str[i] >= '0' && str[i] <= '8'))
            return 0;
    }
    return 1;
}

int duplicate(char* str) {
    for (int i = 0; i < CODE_LENGTH - 1; i++) {
        for (int j = i + 1; j < CODE_LENGTH; j++) {
            if (str[i] == str[j])
                return 0;
        }
    }
    return 1;
}

char* generateRandomCode() {
    srand((unsigned)time(NULL));
    char* code = malloc(CODE_LENGTH + 1);
    for (int i = 0; i < CODE_LENGTH; i++) {
        char digit;
        do {
            digit = (char)(rand() % 10 + '0');
        } while (strchr(code, digit));
        code[i] = digit;
    }
    code[CODE_LENGTH] = '\0';
    return code;
}

char* getUserInput() {
    printf("> ");
    fflush(stdout);
    char* input = malloc(CODE_LENGTH + 1);
    fgets(input, CODE_LENGTH + 1, stdin);
    input[strcspn(input, "\n")] = '\0';
    return input;
}

int countWellPlaced(char* code, char* guess) {
    int count = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (code[i] == guess[i]) {
            count++;
        }
    }
    return count;
}

int countMisplaced(char* code, char* guess) {
    int count = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        for (int j = 0; j < CODE_LENGTH; j++) {
            if (i != j && code[i] == guess[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

void playGame(char* code, int attempts) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int attempt = 1; attempt <= attempts; attempt++) {
        printf("---\nRound %d\n", attempt);
        char* guess = getUserInput();
        if (!isCorrect(guess) || !duplicate(guess)) {
            printf("Wrong input!\n");
            free(guess);
            attempt--;
            continue;
        }
        int wellPlaced = countWellPlaced(code, guess);
        int misplaced = countMisplaced(code, guess);
        if (wellPlaced == CODE_LENGTH) {
            printf("Congrats! You did it!\n");
            free(guess);
            return;
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
        free(guess);
    }
    printf("Out of attempts. The correct code was: %s\n", code);
}
