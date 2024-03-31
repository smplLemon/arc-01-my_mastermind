#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *generate_random_code();
int string_length(char *str);
int check_input_validity(char *input);
void evaluate_guess(char *code, char *guess, int *good, int *unitized);

char *generate_random_code() {
    srand(time(NULL));
    char* code = (char *)malloc(sizeof(char)*5);
    for(int i = 0; i < 4; i++) {
        code[i] = rand() % 9 + '0';
        for(int j = 0; j < i; j++) {    
            if(code[i] == code[j]) {
                i--;
                break;
            }
        }
    }
    code[4] = '\0';
    return code;
}

int string_length(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int check_input_validity(char *input) {
    int length = string_length(input);
    if(length != 4) {
        printf("Wrong input!\n");
        return 0;
    } 

    for(int i = 0; i < 4; i++) {
        if(input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 0;
        }
    }

    for(int i = 0; i < 4; i++) {
        for(int j = i+1; j < 4; j++) {
            if(input[i] == input[j]) {
                printf("Wrong input!\n");
                return 0;
            }
        }
    }

    return 1;
}

void evaluate_guess(char *code, char *guess, int *good, int *unitized) {
    *good = 0;
    *unitized = 0;
    for(int i = 0; i < 4; i++) {
        if(code[i] == guess[i]) {
            (*good)++;
        }
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(guess[i] == code[j] && i != j) {
                (*unitized)++;
            }
        }
    }
}

int main(int argc, char **argv) {
    int attempts = 10;
    char *code = NULL;
    char guess[15] = {0};
    char c = 0;
    int j = 0;
    int good;
    int unitized;
    good = 0;
    unitized = 0;

    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "-t") == 0) {
            attempts = atoi(argv[i+1]);
        }
        if(strcmp(argv[i], "-c") == 0) {
            code = argv[i+1];
        }
    }

    if(code == NULL) {
        code = generate_random_code();
    }

    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    for(int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i);
        do {
            write(1, ">", 1);
            j = 0;
            while((read(0, &c, 1)) > 0) {
                if(c == '\n') {
                    guess[j] = '\0';
                    break;
                }
                guess[j] = c;
                j++;
            }
            if(c == 0 || c == -1) {
                return 0;
            }
        } while(!check_input_validity(guess));  

        evaluate_guess(code, guess, &good, &unitized);

        if(good == 4) {
            printf("Congratulations! You did it!\n");
            return 0;
        } else {
            printf("Well placed pieces: %d\n", good);
            printf("Misplaced pieces: %d\n", unitized);
        }
    }

    return 0;
}
