#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define max_attempts 10
#define code_length 4
#define colors "012345678"

void makeSecretCode(char *secret_code) {
    srand(time(0));
    for (int i = 0; i < code_length; i++) {
        secret_code[i] = colors[rand() % 9];
    }
    secret_code[code_length] = '\0';
}

int WrongInput(char *input) {
    if (strlen(input) != code_length) {
        return 0;
    }
    return 1;
}

void checkGuess(char *secret_code, char *guess, int *well_placed, int *misplaced) {
    *well_placed = 0;
    *misplaced = 0;
    for (int i = 0; i < code_length; i++) {
        if (secret_code[i] == guess[i]) {
            (*well_placed)++;
        }
            for (int j = 0; j < code_length; j++) {
                if (guess[i] == secret_code[j]) {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }

int main(int argc, char *argv[]) {
    char secret_code[code_length + 1];
    char guess[code_length + 1];
    int well_placed, misplaced, attempts = max_attempts;
    if (argc > 0) {
        for (int i = 1; i < argc; i += 1) {
            if (strcmp(argv[i], "-c") == 0) {
                secret_code[code_length] = '\0';
                //makeSecretCode(secret_code);
            } else if (strcmp(argv[i], "-t") == 0) {
                attempts = atoi(argv[i+1]);
            }
        }
    }

    if (strlen(secret_code) == 0) {
        printf("Will you find the secret code?\n");
        printf("Please enter a valid guess\n");
        //makeSecretCode(secret_code);
    }

    for (int attempt = 0; attempt <= attempts; attempt++) {
        printf("\n Round %d ", attempt);

        // Read player's input
        for (int i = 0; i < code_length; i++) {
            char c;
            if (read(STDIN_FILENO, &c, 1) <= 0) {
                printf("\n Wrong input!\n");
                return 1;  // Exit the program on error
            }
            if (c == '\n') {
                guess[i] = '\0';
                break;
            } else {
                guess[i] = c;
            }
        }

        // Evaluate the guess
        checkGuess(secret_code, guess, &well_placed, &misplaced);

        if (well_placed == code_length) {
            printf("Congratz! You did it!\n");
            break;
        } else {
            printf("Well placed pieces: %d\n", well_placed);
            printf("Misplaced pieces: %d\n", misplaced);
        }
    }
    return 0;
}
