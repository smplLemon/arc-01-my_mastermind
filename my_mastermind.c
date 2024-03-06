#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SECRET_CODE_LENGTH 4

int str_len(char* arr) {
    int length = 0;
    for (int i = 0; arr[i] != '\0'; ++i) {
        length++;
    }
    return length;
}

int inspector(char* arr, char letter) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == letter) return 1;
    }
    return 0;
}

void generate_secret(char secret[]) {
    srand(time(NULL));
    int i = 0;
    char temp;
    while(i < SECRET_CODE_LENGTH) {
        temp = rand() % 10 + '0'; 
        if (inspector(secret, temp) == 0) {
            secret[i] = temp;
            i++;
        }
    }
    secret[SECRET_CODE_LENGTH] = '\0'; 
}

int checkDuplicateNumbers(char* guess) {
    if (str_len(guess) != SECRET_CODE_LENGTH) return 1; 
    for (int i = 0; i < SECRET_CODE_LENGTH; ++i) {
        if (guess[i] < '0' || guess[i] > '8') {
            return 1;
        }
    }
    for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
        for (int j = i + 1; j < SECRET_CODE_LENGTH; j++) {
            if (guess[i] == guess[j]) {
                return 1;
            }
        }
    }
    return 0;
}

char* get_user_guess() {
    int the_size_array = 10, the_index = 0;
    ssize_t reader;
    char* the_user_input = calloc(sizeof(char), the_size_array);
    if (the_user_input == NULL) {
        exit(EXIT_SUCCESS);
    }
    char temp;
    while ((reader = read(STDIN_FILENO, &temp, 1)) > 0 && temp != '\n') {
        if (the_index >= the_size_array - 1) {
            the_size_array *= 2;
            the_user_input = realloc(the_user_input, the_size_array);
            if (the_user_input == NULL) {
                exit(EXIT_SUCCESS);
            }
        }
        the_user_input[the_index++] = temp;
    }
    
    the_user_input[the_index] = '\0';
    return the_user_input;
}


void give_feedback(char secret_code[SECRET_CODE_LENGTH], char guess[SECRET_CODE_LENGTH]) {
    int black = 0, white = 0;
    for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
        if (secret_code[i] == guess[i]) {
            black++;
        } else {
            for (int j = 0; j < SECRET_CODE_LENGTH; j++) {
                if (secret_code[i] == guess[j]) {
                    white++;
                    break;
                }
            }
        }
    }
    if (black == SECRET_CODE_LENGTH) {
        printf("Congrats! You did it!\n");
        exit(EXIT_SUCCESS);
    }
    printf("\nWell placed: %d\n", black);
    printf("Misplaced: %d\n", white);
}

int the_main_function(char secret_code[SECRET_CODE_LENGTH], int attempts) {
    if (checkDuplicateNumbers(secret_code) == 1) exit(EXIT_FAILURE);
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int attempt = 1; attempt <= attempts; attempt++) {
        printf("---\nRound: %d\n>", attempt);
        while(1) {
            char* users_guess = get_user_guess();
            if (checkDuplicateNumbers(users_guess) == 1) {
                printf("Wrong input!\n>");
            } else {
                give_feedback(secret_code, users_guess);
                free(users_guess); 
                break;
            }
        }
    }
    printf("Out of attempts. The secret code was: %s\n", secret_code);
    return 0;
}

int main(int argc, char *argv[]) {
    char secret_code[SECRET_CODE_LENGTH + 1];
    generate_secret(secret_code);
    if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        the_main_function(argv[2], 10);
    } else if (argc == 3 && strcmp(argv[1], "-t") == 0) {
        the_main_function(secret_code, atoi(argv[2]));
    } else if (argc == 5 && strcmp(argv[1], "-c") == 0 && strcmp(argv[3], "-t") == 0) {
        the_main_function(argv[2], atoi(argv[4]));
    } else if (argc == 5 && strcmp(argv[1], "-t") == 0 && strcmp(argv[3], "-c") == 0) {
        the_main_function(argv[4], atoi(argv[2]));
    } else {
        the_main_function(secret_code, 10);
    }
    return 0;
}