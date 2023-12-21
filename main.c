#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my_mastermind.h"

int main(int argc, char *argv[]) {
    char secret_code[5] = "1123";
    int attempts = 10; 

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            strncpy(secret_code, argv[i + 1], 4);
            secret_code[4] = '\0';
        }
        if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            attempts = atoi(argv[i + 1]);
        }
    }

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (attempts > 0) {
        char guess[5];
        printf("---\nRound %d\n>", 10 - attempts);
        if (read_input(guess)) {
            if (check_guess(guess, secret_code)) {
                printf("Congratz! You did it!\n");
                return 0;
            }
        } else {
            printf("Wrong input! Please enter a valid guess\n");
            continue;
        }
        attempts--;
    }

    printf("Game over. Secret code was: %s\n", secret_code);
    return 0;
}
