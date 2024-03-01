#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define len_num 4
#define MAX_ATTEMPTS 10

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
        exit(0);
    }
    return 0;
}

void my_strcpy(char *param_1, char *param_2) {
    while (*param_2 != '\0') {
        *param_1 = *param_2;
        param_1++;
        param_2++;
    }
    *param_1 = '\0';
}


void generate_secret_numbers(char secret_numbers[]) {
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    srand(time(NULL));

    for (int i = 0; i < len_num; i++) {
        int j = rand() % (10 - i); 
        secret_numbers[i] = digits[j];
        digits[j] = digits[9 - i]; 
    }

    secret_numbers[len_num] = '\0'; 
}

void checker(char guess_numbers[]) {
    if (strlen(guess_numbers) != len_num) {
        printf("Wrong input\n");
        my_scanf(guess_numbers);
        checker(guess_numbers);
    }

    int visited[10] = {0};

    for (int i = 0; i < len_num; i++) {
        if (!isdigit(guess_numbers[i])) {
            printf("Wrong input\n");
            my_scanf(guess_numbers);
            checker(guess_numbers);
        }

        int num = guess_numbers[i] - '0';

        if (visited[num]) {
            printf("Wrong input\n");
             my_scanf(guess_numbers);
             checker(guess_numbers);
        }

        visited[num] = 1;
    }
}
void get_guess_nums(char guess_numbers[]) {
    my_scanf(guess_numbers);
    checker(guess_numbers);
}

void compare(char secret_numbers[], char guess_numbers[], int *wellPlaced, int *misplaced) {
    *wellPlaced = 0;
    *misplaced = 0;
    int freqSecret[10] = {0};
    int freqGuess[10] = {0};

    for (int i = 0; i < len_num; i++) {
        if (guess_numbers[i] == secret_numbers[i]) {
            (*wellPlaced)++;
        } else {
            freqSecret[secret_numbers[i] - '0']++;
            freqGuess[guess_numbers[i] - '0']++;
        }
    }

    for (int i = 0; i < 10; i++) {
        *misplaced += (freqSecret[i] < freqGuess[i]) ? freqSecret[i] : freqGuess[i];
    }

    *misplaced -= *wellPlaced;
}


int main(int argc, char *argv[]) {
    char secret_numbers[len_num];
    char *code = NULL;
    int attempts = MAX_ATTEMPTS;
    int wellPlaced, misplaced;
    char guess_numbers[len_num + 1] = "";
    int round = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            code = argv[i + 1];
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            attempts = atoi(argv[i + 1]);
        }
    }

    generate_secret_numbers(secret_numbers);

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (attempts > 0) {
        printf("---\n");
        printf("Round %d\n", round++);
        get_guess_nums(guess_numbers);
        compare(secret_numbers, guess_numbers, &wellPlaced, &misplaced);
        printf("Well-placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
        if (wellPlaced == len_num) {
            printf("Congratulations! You guessed the secret code!\n");
            break;
        }
        attempts--;
    }

   
    return 0;
}