#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define SECRET_CODE_LENGTH 4

int my_strlen(char* str){
    int length;
    while(str[length] != '\0'){
        length++;
    }
    return length;
}

char* scaning_function(){
    int size = 10;
    char *user_input = calloc(sizeof(char), size);
    char temp;
    for (int index = 0;read(0, &temp, 1);)
    {
        if (temp == '\n')
        {
            user_input[index] = '\0';
            return user_input;
        }
        user_input[index++] = temp;
    }
    return NULL;
}

void function_c(char* param_1, char* param_2, int* val, int* res) {
    int i = 0;
    *val = 0, *res = 0;
    int param_1_param_1[10] = { 0 };
    int c1[10] = { 0 };
    for (int i = 0; i < SECRET_CODE_LENGTH; i++) {
        if (param_1[i] == param_2[i]) {
            (*val)++;
        } else {
            param_1_param_1[param_1[i] - '0']++;
            c1[param_2[i] - '0']++;
        }
    }
    while (i < 10) {
        if (c1[i] < param_1_param_1[i]) {
            *res += c1[i];
        } else {
            *res += param_1_param_1[i];
        }
        i++;
    }
}

int is_number_repeating(int num, char* secret_code){
    int len = strlen(secret_code);
    for (int i = 0; i < len; ++i) {
        if (num == secret_code[i]) {
            return 1;
        }
    }
    return 0;
}

char* function_in_c(char* ptr) {
    srand(time(NULL));
    const char numbers[] = "012345678";
    int temp, i = 0;
    while (i < SECRET_CODE_LENGTH) {
        temp = numbers[rand() % 7];
        if (is_number_repeating(temp, ptr) == 0) {
            ptr[i] = temp;
            i++;
        }
    }
    ptr[SECRET_CODE_LENGTH] = '\0';
    return ptr;
}

int input_checking_function(char* input_code) {
    int len = strlen(input_code);
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

int The_Second_Main_Function(char secret_code[], int rounds){
    if (input_checking_function(secret_code))exit(1);
    int well = 0, miss = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for(int r = 1; r <= rounds; r++){
        printf("---\nRound %d\n",r);
        while(1){
            printf(">");
            char* Users_Input = scaning_function();
            if(input_checking_function(Users_Input) == 1){
                printf("Wrong Input!\n");
            }else{
                function_c(secret_code,Users_Input, &well, &miss);
                if(well == 4){
                    printf("Congratz! You did it!\n");
                    return 0;
                }
                printf("Well placed pieces: %d\nMisplaced pieces: %d\n",well,miss);
                well-=well,miss-=miss;
                break;
            }
        }
    }
    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}

int main(int argc, char** argv) {
    char secret_code[SECRET_CODE_LENGTH];
    function_in_c(secret_code);
    if (argc < 2){
      The_Second_Main_Function(secret_code, 10);
    }else if (argc == 3 && (strcmp(argv[1], "-c") == 0)){
      The_Second_Main_Function(argv[2], 10);
    }else if (argc == 3 && (strcmp(argv[1], "-t") == 0)){
      The_Second_Main_Function(secret_code, atoi(argv[2]));
    }else if (argc == 5 && (strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-c") == 0)){
      The_Second_Main_Function(argv[4], atoi(argv[2]));
    }else if (argc == 5 && (strcmp(argv[1], "-c") == 0) && (strcmp(argv[3], "-t") == 0)){
      The_Second_Main_Function(argv[2], atoi(argv[4]));
    }
    return 0;
}
