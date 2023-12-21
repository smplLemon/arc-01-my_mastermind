#include "my_mastermind.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

int check_guess(const char *guess, const char *secret_code) {
    int well_placed = 0, misplaced = 0;

    for (int i = 0; i < 4; i++) {
        if (guess[i] == secret_code[i]) {
            well_placed++;
        } else if (strchr(secret_code, guess[i]) != NULL) {
            misplaced++;
        }
    }

    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
    return well_placed == 4;
}

int read_input(char *buffer) {
    char c;
    int i = 0;
    while (read(0, &c, 1) > 0 && c != '\n') {
        if (i < 4) {
            buffer[i++] = c;
        }
    }
    buffer[i] = '\0';

    if (i != 4) {
        return 0;
    }

    for (int j = 0; j < 4; j++) {
        if (!isdigit(buffer[j])) {
            return 0;
        }
    }

    return 1;
}