#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define len_num 4

int validate_input(char *input) {
    int visited[10] = {0};
    
    if (strlen(input) != len_num) {
        return 0;
    }

    for (int i = 0; i < len_num; i++) {
        if (input[i] < '0'  input[i] > '9'  visited[input[i] - '0']) {
            return 0;
        }
        visited[input[i] - '0'] = 1;
    }
    return 1;
}

void generate_secret_numbers(char secret_numbers[]) {
    int numbers[10] = {0};
    for (int i = 0; i < len_num; i++) {
        int num = rand() % 10;
        while (numbers[num]) {
            num = rand() % 10;
        }
        numbers[num] = 1;
        secret_numbers[i] = num + '0';
    }
    secret_numbers[len_num] = '\0';
}

void compare(char secret_numbers[], char guess_numbers[], int *wellPlaced, int *misplaced) {
    *wellPlaced = 0;
    *misplaced = 0;

    for (int i = 0; i < len_num; i++) {
        if (guess_numbers[i] == secret_numbers[i]) {
            (*wellPlaced)++;
        } else {
            for (int j = 0; j < len_num; j++) {
                if (i != j && guess_numbers[i] == secret_numbers[j]) {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    time_t t;
    srand((unsigned)time(&t));

    char secret_numbers[len_num + 1];
    generate_secret_numbers(secret_numbers);

    printf("Will you find the secret code? Please enter %d unique digits.\n", len_num);

    int attempts = 10;
    int wellPlaced, misplaced;
    char guess_numbers[len_num + 1];

    while (attempts > 0) {
        printf("---\n");
        printf("Round %d\n", 10 - attempts + 1);
        printf("Enter your guess: ");
        scanf("%s", guess_numbers);

        if (!validate_input(guess_numbers)) {
            printf("Invalid input. Please enter %d unique digits.\n", len_num);
            attempts--;
            continue;
        }

        compare(secret_numbers, guess_numbers, &wellPlaced, &misplaced);
        printf("Well-placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);

        if (wellPlaced == len_num) {
            printf("Congratulations! You guessed the secret code.\n");
            break;
        }
        
        attempts--;
    }

    if (attempts == 0) {
        printf("Sorry, you couldn't find the secret code. The secret code was: %s\n", secret_numbers);
    }

    return 0;
}
