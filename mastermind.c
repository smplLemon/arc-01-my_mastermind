#include <stdio.h> 
#include <assert.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
#include "mastermind.h"



 

void game_func(char* secret_code, int attempts) 
{ 
    printf("Will you find the secret code?\nPlease enter a valid guess\n"); 
    char* input; 
    int* arr; 
    for (int i = 0; i < attempts; i++) 
    { 
        printf("---\nRound %d\n", i); 
        input = my_scanf(); 
        if (input == NULL) return; 
        arr = check_for_wi(input, secret_code); 
        if (arr != 0 && arr[0] == 4) { 
            printf("Congratz! You did it!\n"); 
            return; 
        } 
        while (arr == 0) 
        { 
            free(input); 
            printf("Wrong input!\n"); 
            input = my_scanf(); 
            arr = check_for_wi(input, secret_code); 
            if (arr != 0 && arr[0] == 4) { 
                printf("Congratz! You did it!\n"); 
                return; 
            } 
        } 
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", arr[0], arr[1]); 
        free(arr); 
        free(input); 
    } 
    // free(secret_code); 
    // free(arr); 
} 
 
int main(int argc, char** argv) 
{    
    if (argc == 0) return 1; 
    char* secret_code ; 
    int attempts = 10; 
    int code_flag = 0; 
    for (int i = 0; i < argc; i++) 
    { 
        if (my_strcmp(argv[i], "-c") == 0) 
        { 
            secret_code = calloc(5, sizeof(char)); 
            my_str_cpy(secret_code, argv[++i]);  
            code_flag++;

}               else if (my_strcmp(argv[i], "-t") == 0) attempts = atoi(argv[++i]);
    }
    if (code_flag == 0) secret_code = random_code_generate();        game_func(secret_code, attempts);
    free(secret_code);    return 0;
}