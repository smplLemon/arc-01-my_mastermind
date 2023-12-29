#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SECRET_CODE_LENGTH 4
#define MAX_ATTEMPTS 10
#define NUM_DIGITS 10

void generate_secret_code(char* secret_code) {
    const char numbers[] = "0123456789";
    for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
        secret_code[i] = numbers[rand() % NUM_DIGITS];
    }
    secret_code[SECRET_CODE_LENGTH] = '\0';
}

void evaluate_guess(const char* user_guess, const char* secret_code, int* well_placed, int* misplaced) {
    int guess_hist[NUM_DIGITS] = {0};
    int secret_hist[NUM_DIGITS] = {0};
    *well_placed = 0;
    *misplaced = 0;

    for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
        if (user_guess[i] == secret_code[i]) {
            (*well_placed)++;
        } else {
            guess_hist[user_guess[i] - '0']++;
            secret_hist[secret_code[i] - '0']++;
        }
    }
    
    for (int i = 0; i < NUM_DIGITS; i++) {
        *misplaced += (guess_hist[i] < secret_hist[i]) ? guess_hist[i] : secret_hist[i];
    }
}

int is_valid_input(const char* input) {
    if (strlen(input) != SECRET_CODE_LENGTH || strspn(input, "0123456789") != SECRET_CODE_LENGTH) {
        return 0;
    }

    for (int i = 0; i < SECRET_CODE_LENGTH - 1; i++) {
        for (int j = i + 1; j < SECRET_CODE_LENGTH; j++) {
            if (input[i] == input[j]) {
                return 0;
            }
        }
    }
    
    return 1;
}

void play_game(const char* secret_code, int attempts) {
    char user_guess[SECRET_CODE_LENGTH + 1];
    int well_placed, misplaced;
    int rounds = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (rounds < attempts) {
        printf("---\nRound %d\n>", rounds);

        if (read(0, user_guess, SECRET_CODE_LENGTH + 1) == -1) {
            printf("Error reading input.\n");
            return;
        }

        user_guess[strcspn(user_guess, "\n")] = '\0';

        if (!is_valid_input(user_guess)) {
            printf("Wrong input!\n");
            continue;
        }

        evaluate_guess(user_guess, secret_code, &well_placed, &misplaced);

        if (well_placed == SECRET_CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            return;
        }

        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
        rounds++;

        if (attempts > 0 && rounds == attempts) {
            printf("---\nGame over. You didn't find the secret code.\n");
            break;
        }
    }
}

int main(int argc, char** argv) {
    char secret_code[SECRET_CODE_LENGTH + 1] = {'\0'};
    int attempts = MAX_ATTEMPTS;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            strncpy(secret_code, argv[i + 1], SECRET_CODE_LENGTH);
            secret_code[SECRET_CODE_LENGTH] = '\0';
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            attempts = atoi(argv[i + 1]);
        }
    }
    
    if (strlen(secret_code) == 0) {
        srand(time(NULL));
        generate_secret_code(secret_code);
    }

    play_game(secret_code, attempts);
    
    return 0;
}
