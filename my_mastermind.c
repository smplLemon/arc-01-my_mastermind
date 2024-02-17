#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define len_num 4

int my_strlen(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int my_scanf(char *str) {
    int index = 0;
    char letter;
    write(1, ">", 1);
    while (read(STDIN_FILENO, &letter, 1) > 0) {
        if (letter == '\n' || index == len_num + 1) {
            str[index] = '\0';
            return 1;
        }
        str[index++] = letter;
    }
    if (index == 0) {
        printf("\nCtrl+D pressed. Exiting...\n");
        exit(0);
    }
    return 0;
}

void generator_secret_numbers(char secret_numbers[]) {
    int used[9] = {0}; // Adjusted to cover numbers from 0 to 8
    srand(time(NULL));
    for (int i = 0; i < len_num; i++) {
        int num;
        num = rand() % 9; // Generating numbers from 0 to 8
        while (used[num]) {
            num = rand() % 9;
        }
        used[num] = 1;
        secret_numbers[i] = num + '0';
    }
}

void checker(char guess_numbers[]) {
    if (my_strlen(guess_numbers) != len_num) {
        printf("Wrong input\n");
        my_scanf(guess_numbers);
        checker(guess_numbers); // Recursive
    }
    int visited[10] = {0};
    for (int i = 0; i < len_num; i++) {
        if ((guess_numbers[i] >= 'a' && guess_numbers[i] <= 'z') || (guess_numbers[i] >= 'A' && guess_numbers[i] <= 'Z')) {
            printf("Wrong input\n");
            my_scanf(guess_numbers);
            checker(guess_numbers); // Recursive
        }
        int num = guess_numbers[i] - '0';
        if (visited[num]) {
            printf("Wrong input\n");
            my_scanf(guess_numbers);
            checker(guess_numbers); // Recursive
            break;
        }
        visited[num] = 1;
    }
}

void get_guess_nums(char guess_numbers[]) {
    my_scanf(guess_numbers);
    checker(guess_numbers);
}

void conmpare(char secret_numbers[], char guess_numbers[], int *wellPlaced, int *misplaced) {
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

int main() {
    char secret_numbers[len_num];
    generator_secret_numbers(secret_numbers);

    int attempts = 10;
    int wellPlaced, misplaced;
    char guess_numbers[len_num + 1];
    int round = 0;

    printf("Will you find the secret code? \nPlease enter a valid numbers\n");

    while (attempts > 0) {
        printf("---\n");
        printf("Round %d\n", round++);
        get_guess_nums(guess_numbers);
        conmpare(secret_numbers, guess_numbers, &wellPlaced, &misplaced);
        printf("Well-placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
        if (wellPlaced == len_num) {
            printf("Congratz! You did it!\n");
            break;
        }
        attempts--;
    }
////
    if (attempts == 0) {
        printf("Sorry, you couldn't find the secret code.\n");
    }

    return 0;
}