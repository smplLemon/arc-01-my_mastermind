#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define lenth_of_num 4

void cheker(char* guess, char* s_code, int* r, int* wrong, int* guess_num, int* index) {
    int i = 0;
    *r = 0;
    *wrong = 0;
    for (i = 0; i < lenth_of_num; i++){
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
    while(i < 10){
        if (index[i] < guess_num[i]){
            *wrong += index[i];
        } else {
            *wrong += guess_num[i];
        }
        i++;
    }
}

void cheker_f(char* guess, char* s_code, int* r, int* wrong) {
    int guess_num[10] = {0};
    int index[10] = {0};
    cheker(guess, s_code, r, wrong, guess_num, index);
    c_w(wrong, guess_num, index);
}

char* randomcode(char* random_code) {
    const char numbers[] = "0123456789";

    for (int i = 0; i < lenth_of_num; i++){
        int random_i = rand() % 10;
        random_code[i] = numbers[random_i];
    }
    random_code[lenth_of_num] = '\0';
    return random_code;
}

int check_length(char* input_code) {
    if (strlen(input_code) != lenth_of_num){
        return 0;
    }
    return 1;
}

int check_digits(char* input_code) {
    for (int i = 0; i < lenth_of_num; i++){
        if (input_code[i] < '0' || input_code[i] > '9'){
            return 0;
        }
    }
    return 1;
}

int input_cheker_f(char* input_code) {
    if (!check_length(input_code)) {
        return 0;
    }

    if (!check_digits(input_code)) {
        return 0;
    }

    return 1;
}

int main(int argc, char** argv)
{
    char* s_code = calloc(sizeof(char), lenth_of_num + 1);
    int max_chanse = 10;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            strncpy(s_code, argv[i + 1], lenth_of_num);
            s_code[lenth_of_num] = '\0';
        }else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            max_chanse = atoi(argv[i + 1]);
        }
    }
    if (strlen(s_code) == 0){
        srand(time(NULL));
        randomcode(s_code);
    }
    char guess[lenth_of_num + 1];
    int r, wrong;
    int rounds = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (rounds < max_chanse){
        printf("---\nRound %d\n>", rounds);
        if (read(0, guess, lenth_of_num + 1) == -1){
            printf("Error reading input.\n");
            return 1;
        }
        guess[lenth_of_num] = '\0';
        if (!input_cheker_f(guess)){
            printf("Wrong input!\n");
            continue;
        }
        cheker_f(guess, s_code, &r, &wrong);
        if (r == lenth_of_num){
            printf("Congratz! You did it!\n");
            return 0;
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", r, wrong);
        rounds++;
    }
    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}
