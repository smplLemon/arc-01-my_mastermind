#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define the_length_of_param   4


void compare_guess(char* guess, char* secret, int* correct, int* misplaced)
{
     
    int secret_count[10] = {0};
    *misplaced =  0; 
    int guess_count[10] = {0};
    int i =  0;  
    *correct =  0;
     for (i =  0; i < the_length_of_param; i++) {
        if (guess[i] == secret[i]) {(*correct)++;} 
        else {secret_count[secret[i] - '0']++;
            guess_count[guess[i] - '0']++;}
}for (i =  0; i <  10; i++) {
        if (guess_count[i] < secret_count[i]) {(*misplaced) += guess_count[i];} 
        else {
            (*misplaced) += secret_count[i];
}}}


char* generate_secret_code(char* code)
{
    const char numbers[] = "0123456789";
    int index =  0;
    
    while (index < the_length_of_param) {
        code[index] = numbers[rand() %  10];
        index++;
    }
    
    code[the_length_of_param] = '\0';
    return code;
}


int validate_input(char* input_code)
{
    int i =  0;
    
    if (strlen(input_code) != the_length_of_param) {
        return  0;
    }

    for (i =  0; i < the_length_of_param; i++) {
        if (input_code[i] < '0' || input_code[i] > '9') {
            return  0;
        }
    }
    return  1;
}


int main(int argc, char** argv)
{
    char* secret_code = calloc(sizeof(char), the_length_of_param +  1);
    int max_attempts =  10;
    
    for (int i =  1; i < argc; i++) {
        if (strcmp(argv[i], "-c") ==  0 && i +  1 < argc) {
            strncpy(secret_code, argv[i +  1], the_length_of_param);
            secret_code[the_length_of_param] = '\0';
        } else if (strcmp(argv[i], "-t") ==  0 && i +  1 < argc) {
            max_attempts = atoi(argv[i +  1]);
        }
    }
    
    if (strlen(secret_code) ==  0) {
        srand(time(NULL));
        generate_secret_code(secret_code);
    }
    
    char guess[the_length_of_param +  1];
    int correct, misplaced;
    int rounds =  0;
    
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    
    while (rounds < max_attempts) {
        printf("---\nRound %d:\n>", rounds);
        
        if (read(0, guess, the_length_of_param +  1) == -1) {
            printf("Error reading input.\n");
            return  1;
        }
        guess[the_length_of_param] = '\0';
        
        if (!validate_input(guess)) {
            printf("Invalid input!\n");
            continue;
        }
        compare_guess(guess, secret_code, &correct, &misplaced);
        if (correct == the_length_of_param) {
            printf("Congrats! You did it!\n");
            return  0;
        }
        printf("Well placed pieces: %d\n Misplaced pieces: %d ", correct, misplaced);
        rounds++;
    }
    printf("---\nGame over. You didn't find the secret code.\n");
    return  0;
}
