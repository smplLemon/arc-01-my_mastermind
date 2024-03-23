#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define SECRET_CODE_LENGTH 4

int my_strlen(char* str){
    int length = 0;
    while(str[length] != '\0'){
        length++;
    }
    return length;
}

char* scaning_function() {
    int size = 10, index = 0;
    char *user_input = calloc(sizeof(char), size), temp;
    if (user_input == NULL) return NULL;
    ssize_t bytes_read;
    while ((bytes_read = read(0, &temp, 1)) > 0) {
        if (temp == '\n') {
            user_input[index] = '\0';
            return user_input;
        }
        user_input[index++] = temp;
        if (index >= size) {
            size *= 2;
            user_input = realloc(user_input, size * sizeof(char));
            if (user_input == NULL) return NULL;
        }
    }
    if (bytes_read == -1) return NULL;
    free(user_input);
    return NULL;
}

void function_c(char* param_1, char* param_2, int* val, int* res) {
    *val = 0, *res = 0;
    int param_1_count[10] = { 0 };
    int param_2_count[10] = { 0 };
    for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
        if (param_1[i] == param_2[i]) {
            (*val)++;
        } else {
            param_1_count[param_1[i] - '0']++;
            param_2_count[param_2[i] - '0']++;
        }
    }
    for (int i = 0; i < 10; ++i) {
        if (param_2_count[i] < param_1_count[i]) {
            *res += param_2_count[i];
        } else {
            *res += param_1_count[i];
        }
    }
}

int is_number_repeating(int num, char* secret_code){
    int len = my_strlen(secret_code);
    for (int i = 0; i < len; ++i) {
        if (num == secret_code[i]) {
            return 1;
        }
    }
    return 0;
}

char* function_in_c(char* ptr) {
    srand(time(NULL));
    int i = 0;
    char temp;
    while (i < SECRET_CODE_LENGTH) {
        temp = rand() % 9;
        if (is_number_repeating(temp, ptr) == 0) {
            ptr[i] = temp + '0';
            i++;
        }
    }
    ptr[SECRET_CODE_LENGTH] = '\0';
    return ptr;
}

int input_checking_function(char* input_code) {
    int len = my_strlen(input_code);
    if (len != SECRET_CODE_LENGTH) {
        return 1;
    }
    for (int i = 0; i < len; ++i) {
        for (int k = 0; k < i; ++k) {
            if (input_code[k] == input_code[i]) {
                return 1;
            }
        }
    }
    for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
        if (input_code[i] < '0' || input_code[i] > '8') {
            return 1;
        }
    }
    return 0;
}

void The_Second_Main_Function(char secret_code[], int rounds){
    if (input_checking_function(secret_code)) return;
    int well = 0, miss = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for(int r = 1; r <= rounds; r++){
        printf("---\nRound %d\n> ",r);
        while(1){
            char* Users_Input = scaning_function();
            if (Users_Input == NULL) return;
                if (input_checking_function(Users_Input) == 1) printf("Wrong Input!\n> "); 
                else {
                    function_c(secret_code, Users_Input, &well, &miss);
                if(well == 4){
                    printf("Congratz! You did it!\n");
                    return;
                }
                printf("Well placed pieces: %d\nMisplaced pieces: %d\n",well,miss);
                well = 0,miss = 0;
                break;
            }
        }
    }
}


int main(int argc, char** argv) {
    char secret_code[SECRET_CODE_LENGTH];
    function_in_c(secret_code);
    if (argc < 2) {
        The_Second_Main_Function(secret_code, 10);
    } else if (argc == 3 && (strcmp(argv[1], "-c") == 0)) {
        The_Second_Main_Function(argv[2], 10);
    } else if (argc == 3 && (strcmp(argv[1], "-t") == 0)) {
        The_Second_Main_Function(secret_code, atoi(argv[2]));
    } else if (argc == 5 && (strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-c") == 0)) {
        The_Second_Main_Function(argv[4], atoi(argv[2]));
    } else if (argc == 5 && (strcmp(argv[1], "-c") == 0) && (strcmp(argv[3], "-t") == 0)) {
        The_Second_Main_Function(argv[2], atoi(argv[4]));
    }
    return 0;
}