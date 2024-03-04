#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char *generate_random_code();
int check_input_validity(char *input);
void evaluate_guess(char *code, char *guess);


int good, unitized;


char *generate_random_code() {
    srand(time(NULL));
    char *code = (char *)malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; i++) {
        code[i] = rand() % 9 + '0';
        for (int j = 0; j < i; j++) {
            if (code[i] == code[j]) {
                i--;
                break;
            }
        }
    }
    code[4] = '\0';
    return code;
}


int check_input_validity(char *input) {
    if (strlen(input) != 4) {
        printf("Wrong input!\n");
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Wrong input!\n");
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input!\n");
                return 0;
            }
        }
    }

    return 1;
}


void evaluate_guess(char *code, char *guess) {
    good = 0;
    unitized = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == guess[i]) {
            good++;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (guess[i] == code[j] && i != j) {
                unitized++;
            }
        }
    }
}


void play_my_mastermind(int attempts, char *code) {
    char guess[15] = {0};
    char c = 0;
    int j = 0;

    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i + 1);
        do {
            printf("Enter your guess (4 digits): ");
            scanf("%s", guess);
        } while (!check_input_validity(guess));

        evaluate_guess(code, guess);

        if (good == 4) {
            printf("Congratulations! You cracked the code!\n");
            return;
        } else {
            printf("Correctly placed digits: %d\n", good);
            printf("Misplaced digits: %d\n", unitized);
        }
    }

    printf("Game over! The secret code was: %s\n", code);
}

int main() {
    int attempts = 10;
    char *code = generate_random_code();

    printf("Welcome to My Mastermind!\n");
    printf("Try to guess the 4-digit secret code.\n");

    play_my_mastermind(attempts, code);

    return 0;
}