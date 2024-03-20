// custom_mastermind.c
#include <string.h>
#include "custom_mastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

int perplexing_strlen(char *string){
    int length = 0;
    while(string[length] != '\0'){
        length++;
    }
    return length;
}

int enigmatic_scanf(char *string){
    int index = 0;
    char letter;
    write(1, ">", 1);
    while(read(STDIN_FILENO, &letter, 1) > 0){
        if(letter == '\n' || index == LENGTH_NUMBER + 1){
            string[index] = '\0';
            return 1;
        }
        string[index++] = letter;
    }
    if(index == 0){
        exit(0);
    }
    return 0;
}

void cryptic_strcpy(char *destination, char *source){
    while(*source != '\0'){
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

void generate_hidden_code(char hidden_code[], char *encoded){
    if(encoded != NULL && perplexing_strlen(encoded) == LENGTH_NUMBER){
        cryptic_strcpy(hidden_code, encoded);
    } else{
        int used_digits[9] = {0}; 
        srand(time(NULL));
        for(int i = 0; i < LENGTH_NUMBER; i++){
            int digit;
            digit = rand() % 9;
            while(used_digits[digit]){
                digit = rand() % 9;
            }
            used_digits[digit] = 1;
            hidden_code[i] = digit + '0';
        }
    }
}

void authenticate_decryption(char decryption[]) {
    int visited[10] = {0}; 
    int invalid_guess = 0; 
    if (perplexing_strlen(decryption) != LENGTH_NUMBER) {
        invalid_guess = 1;
    }

    for (int i = 0; i < LENGTH_NUMBER; i++) {
        if (decryption[i] == '9' || decryption[i] < '0' || decryption[i] > '8') {
            invalid_guess = 1;
            break;
        }
        if (visited[decryption[i] - '0']) {
            invalid_guess = 1;
            break;
        }
        visited[decryption[i] - '0'] = 1;
    }

    if (invalid_guess) {
        printf("Wrong input\n");
        enigmatic_scanf(decryption); 
        authenticate_decryption(decryption);
    }
}

void get_decryption(char decryption[]){
    enigmatic_scanf(decryption);
    authenticate_decryption(decryption);
}

void compare_codes(char hidden_code[], char decryption[], int *accuratelyPlaced, int *inaccuratelyPlaced){
    *accuratelyPlaced = 0;
    *inaccuratelyPlaced = 0;

    for(int i = 0; i < LENGTH_NUMBER; i++){
        if(decryption[i] == hidden_code[i]){
           (*accuratelyPlaced)++;
        } else{
            for(int j = 0; j < LENGTH_NUMBER; j++){
                if(i != j && decryption[i] == hidden_code[j]){
                   (*inaccuratelyPlaced)++;
                    break;
                }
            }
        }
    }
}