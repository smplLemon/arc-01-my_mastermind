#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define lenth_of_num 4

int my_strlen(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void my_strncpy(char *dest, const char *src, int n) {
    for (int i = 0; i < n && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    dest[n] = '\0';
}

char *the_scanf() {
    int the_size_array = 10, the_index = 0;
    char *the_user_input = calloc(sizeof(char), the_size_array), temp;
    for (; read(0, &temp, 1); the_user_input[the_index++] = temp) {
        if (temp == '\n') {
            the_user_input[the_index] = '\0';
            return the_user_input;
        }
    }
    return NULL;
}

void cheker(char* guess, char* s_code, int* r, int* wrong, int* guess_num, int* index) {
    int i = 0;
    *r = 0;
    *wrong = 0;
    for (i = 0; i < lenth_of_num; i++) {
        if (guess[i] == s_code[i]){
            (*r)++;
        } else {
            guess_num[guess[i] - '0']++;
            index[s_code[i] - '0']++;
        }
    }
}

void c_w(int* wrong, int* guess_num, int* index) {
    int i = 0;
    while(i < 10) {
        if (index[i] < guess_num[i]) {
            *wrong += index[i];
        } else {
            *wrong += guess_num[i];
        }
        i++;
    }
}

int cheker_f(char* guess, char* s_code) {
    int guess_num[10] = {0};
    int index[10] = {0};
    int r = 0;
    int wrong = 0;
    cheker(guess, s_code, &r, &wrong, guess_num, index);
    c_w(&wrong, guess_num, index);
    if (r == 4) {
        return 0;
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", r, wrong);
    return 1;
}

int check_random_code(char* input_code, char c) {
    for (int i = 0; input_code[i] != '\0'; ++i) {
        if (input_code[i] == c) return 1;
    }
    return 0;
}

int check_length(char* input_code) {
    if (my_strlen(input_code) != lenth_of_num) {
        return 0;
    }
    return 1;
}

int check_digits(char* input_code) {
    for (int i = 0; i < lenth_of_num; i++) {
        if (input_code[i] < '0' || input_code[i] > '8') {
            return 0;
        }
        for (int k = 0; k < i; ++k) {
            if (input_code[i] == input_code[k]) {
                return 0;
            }
        }
    }
    return 1;
}

int input_checker_f(char* input_code) {
    if (check_length(input_code)==0 || check_digits(input_code)==0){
        return 1;
    }
    else {
        return 0;
    }
}

int the_main_func(char* s_code, int max_chance) {
    for (int i = 1; i <= max_chance; ++i) {
        printf("---\nRound %d\n>", i);
        while (1) {
            char* guess = the_scanf();
            if (guess == NULL) return 0;
            if (input_checker_f(guess)) {
                printf("Wrong input!\n> ");
            } else {
                int result = cheker_f(guess, s_code);
                if (result == 0) {
                    printf("Congratz! You did it!\n");
                    return 0;
                }
                break;
            }
        }
    }
    return 0;
}

char* randomcode(char* random_code) {
    srand(time(NULL));
    char numbers[] = "012345678";
    for (int i = 0; i < lenth_of_num; i++) {
        int random_i = rand() % 9;
        while (check_random_code(random_code, numbers[random_i])) {
            random_i = rand() % 9;
        }
        random_code[i] = numbers[random_i];
    }
    random_code[lenth_of_num] = '\0';
    return random_code;
}

int Sorter(int argc, char** argv, char* s_code, int* max_chance) {
    *max_chance = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            if(!input_checker_f(argv[i+1])) {
                my_strncpy(s_code, argv[i + 1], lenth_of_num);
                s_code[lenth_of_num] = '\0';
            } else {
                return 1;
            }
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            *max_chance += atoi(argv[i + 1]);
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    char* s_code = calloc(sizeof(char), lenth_of_num + 1);
    int max_chance = 0, result = Sorter(argc, argv, s_code, &max_chance);
    if (my_strlen(s_code) == 0) s_code = randomcode(s_code);
    if (max_chance == 0) max_chance = 10;
    if(input_checker_f(s_code) || result != 0) return 1;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    the_main_func(s_code, max_chance);
    return 0;
}