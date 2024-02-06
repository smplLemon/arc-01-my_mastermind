#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define the_length_of_secret_code 4
void checking_function(char* users_guess, char* secret_code, int* right, int* wrong)
{
    int i = 0; *right=0,*wrong=0;
    int users_check[10] = {0};
    int c1[10] = {0};
    for (int i = 0; i < the_length_of_secret_code; i++){
        if (users_guess[i] == secret_code[i]){
            (*right)++;
        } else {
            users_check[users_guess[i] - '0']++;
            c1[secret_code[i] - '0']++;
        }
    }
    while(i<10){
        if (c1[i] < users_check[i]){
            *wrong += c1[i];
        } else {
            *wrong += users_check[i];
        }
        i++;
    }
}

char* Randomiser(char* random_code)
{
    const char numbers[] = "0123456789";
    int a1 = 0;
    while(a1<the_length_of_secret_code){
        random_code[a1] = numbers[rand() % 10];
        a1++;
    }
    random_code[the_length_of_secret_code] = '\0';
    return random_code;
}

int code_check_function(char* input_code)
{
    int i = 0;
    if (strlen(input_code) != the_length_of_secret_code){
        return 0;
    }

    while(i<the_length_of_secret_code){
        if (input_code[i] < '0' || input_code[i] > '9'){
            return 0;
        }
        i++;
    }
    return 1;
}

int main(int argc, char** argv)
{
    char* the_secret_code = calloc(sizeof(char), the_length_of_secret_code + 1);
    int maksimal_urinishlar = 10;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            strncpy(the_secret_code, argv[i + 1], the_length_of_secret_code);
            the_secret_code[the_length_of_secret_code] = '\0';
        }else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            maksimal_urinishlar = atoi(argv[i + 1]);
        }
    }
    if (strlen(the_secret_code) == 0){
        srand(time(NULL));
        Randomiser(the_secret_code);
    }
    char users_guess[the_length_of_secret_code + 1];
    int right, wrong;
    int rounds = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (rounds < maksimal_urinishlar){
        printf("---\nRound %d\n>", rounds);
        if (read(0, users_guess, the_length_of_secret_code + 1) == -1){
            printf("Error reading input.\n");
            return 1;
        }
        users_guess[the_length_of_secret_code] = '\0';
        if (!code_check_function(users_guess)){
            printf("Wrong input!\n");
            continue;
        }
        checking_function(users_guess, the_secret_code, &right, &wrong);
        if (right == the_length_of_secret_code){
            printf("Congratz! You did it!\n");
            return 0;
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", right, wrong);
        rounds++;
    }
    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}