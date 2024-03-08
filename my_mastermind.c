#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

bool step(int argc, char *argv[], int *code, int *round);
int generate(int *code);
int play(int code[], int *round);
int inputCheck(int guess);
int check(int code[], int guess);
void congrats();
int playRound(int code[], int guess);

int main(int argc, char *argv[]) {
    int code[4];
    int round;
    if (!step(argc, argv, code, &round)) return 1;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    return play(code, &round);
}

bool step(int argc, char *argv[], int *code, int *round) {
    if (argc == 1) {
        generate(code);
        return true;
    }
    bool found_t = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            found_t = true;
            *round = (i + 1 < argc) ? atoi(argv[i + 1]) : 10;
            generate(code);
            return true;
        }
    }
    if (!found_t) {
        printf("Invalid option\n");
        return false;
    }
    return true;
}

int generate(int *code) {
    srand(time(NULL));
    bool unique = false;
    while (!unique) {
        unique = true;
        for (int i = 0; i < 4; i++) code[i] = rand() % 8;
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++)
                if (code[i] == code[j]) {
                    unique = false;
                    break;
                }
    }
    return 0;
}

int play(int code[], int *roundI) {
    int round = 0;
    while (round <= *roundI || round <= 10) {
        int guess;
        printf("---\nRound %d \n>", round);
        int result = scanf("%d", &guess);
        if (result == EOF) return 1;
        else if (result != 1) {
            printf("Wrong input!\n");
            while (getchar() != '\n');
            continue;
        }
        int temp = playRound(code, guess);
        if (temp == 1) {
            congrats();
            return 1;
        } else if (temp == 0) round++;
        if (*roundI == round) break;
    }
    printf("You didn't find the code :(\n");
    return 0;
}

int inputCheck(int guess) {
    int numDigits = 0;
    int temp = guess;
    int digits[10] = {0};
    while (temp != 0) {
        int digit = temp % 10;
        temp /= 10;
        numDigits++;
        digits[digit]++;
    }
    if (numDigits != 4 || digits[9] > 0) {
        printf("Wrong input!\n");
        return -1;
    }
    for (int i = 0; i < 10; i++)
        if (digits[i] > 1 || digits[i] == 3 || digits[i] == 4) {
            printf("Wrong input!\n");
            return -1;
        }
    return 0;
}

int check(int code[], int guess) {
    int mp = 0;
    int wp = 0;
    int guess_digits[4];
    guess_digits[0] = guess / 1000;
    guess_digits[1] = (guess / 100) % 10;
    guess_digits[2] = (guess / 10) % 10;
    guess_digits[3] = guess % 10;
    for (int i = 0; i < 4; i++) {
        if (code[i] == guess_digits[i]) mp++;
        else
            for (int j = 0; j < 4; j++)
                if (j != i && code[j] == guess_digits[i]) {
                    wp++;
                    break;
                }
    }
    if (mp == 4) return 1;
    printf("Well placed pieces: %d\n", mp);
    printf("Misplaced pieces: %d\n", wp);
    return 0;
}

int playRound(int code[], int guess) {
    if (inputCheck(guess) == -1) return -1;
    else if (check(code, guess) == 1) return 1;
    else return 0;
}

void congrats() {
    printf("Congratz! You did it!\n");
}
