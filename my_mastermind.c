#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define THE_LENGTH_OF_SECRET_CODE 4

void checkingFunction(char *usersGuess, char *secretCode, int *right, int *wrong) {
    int i = 0;
    *right = 0, *wrong = 0;
    int usersGuessCount[10] = {0};
    int c1[10] = {0};

    for (int i = 0; i < THE_LENGTH_OF_SECRET_CODE; i++) {
        if (usersGuess[i] == secretCode[i]) {
            (*right)++;
        } else {
            usersGuessCount[usersGuess[i] - '0']++;
            c1[secretCode[i] - '0']++;
        }
    }

    while (i < 10) {
        if (c1[i] < usersGuessCount[i]) {
            *wrong += c1[i];
        } else {
            *wrong += usersGuessCount[i];
        }
        i++;
    }
}

char *randomizer(char *randomCode) {
    const char numbers[] = "0123456789";
    int a1 = 0;

    while (a1 < THE_LENGTH_OF_SECRET_CODE) {
        randomCode[a1] = numbers[rand() % 10];
        a1++;
    }

    randomCode[THE_LENGTH_OF_SECRET_CODE] = '\0';
    return randomCode;
}

int inputCodeCheckFunction(char *inputCode) {
    int i = 0;

    if (strlen(inputCode) != THE_LENGTH_OF_SECRET_CODE) {
        return 0;
    }

    while (i < THE_LENGTH_OF_SECRET_CODE) {
        if (inputCode[i] < '0' || inputCode[i] > '9') {
            return 0;
        }
        i++;
    }

    return 1;
}

int main(int argc, char **argv) {
    char *theSecretCode = calloc(sizeof(char), THE_LENGTH_OF_SECRET_CODE + 1);
    int maksimalUrinshlar = 10;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            strncpy(theSecretCode, argv[i + 1], THE_LENGTH_OF_SECRET_CODE);
            theSecretCode[THE_LENGTH_OF_SECRET_CODE] = '\0';
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            maksimalUrinshlar = atoi(argv[i + 1]);
        }
    }

    if (strlen(theSecretCode) == 0) {
        srand(time(NULL));
        randomizer(theSecretCode);
    }

    char usersGuess[THE_LENGTH_OF_SECRET_CODE + 1];
    int right, wrong;
    int rounds = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (rounds < maksimalUrinshlar) {
        printf("---\nRound %d\n>", rounds);

        if (read(0, usersGuess, THE_LENGTH_OF_SECRET_CODE + 1) == -1) {
            printf("Error reading input.\n");
            return 1;
        }

        usersGuess[THE_LENGTH_OF_SECRET_CODE] = '\0';

        if (!inputCodeCheckFunction(usersGuess)) {
            printf("Wrong input!\n");
            char c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        checkingFunction(usersGuess, theSecretCode, &right, &wrong);

        if (right == THE_LENGTH_OF_SECRET_CODE) {
            printf("Congratz! You did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", right, wrong);
        rounds++;

        if (maksimalUrinshlar > 0 && rounds == maksimalUrinshlar) {
            printf("---\nGame over. You didn't find the secret code.\n");
            break;

        }
    }

    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}
