#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h> 
#define Secret_Code_Length  4
int Stoper = 0;

char *The_Scan_Function() {
    int the_size_array = 10, the_index = 0;
    char *the_user_input = calloc(sizeof(char), the_size_array), temp;
    for (; read(0, &temp, 1); the_user_input[the_index++] = temp) {
        if (temp == '\n') {
            the_user_input[the_index] = '\0';
            return the_user_input;
        }
        if (the_index >= the_size_array - 1) {
            the_size_array *= 2;
            the_user_input = realloc(the_user_input, the_size_array);
        }
    }
    return NULL;
}

int My_Str_Len(char* string){
    int length = 0;
    for (int i = 0; string[i] != '\0'; ++i) length++;
    return length;
}

int Checking_Function(char* users_guess){
    for (int i = 0; i < Secret_Code_Length; ++i){
        if (users_guess[i] < '0' || users_guess[i] > '8') return 1;
        for (int j = 0; j < i; ++j){
            if (users_guess[i] == users_guess[j]) return 1;
        }
    }
    return 0;
}

int Checking_Function_for_Generator(char* secret_code, char letter) {
    int length = My_Str_Len(secret_code);
    for (int i = 0; i < length; ++i) {
        if (secret_code[i] == letter) return 1;
    }
    return 0;
}

void Generate_Secret_Code(char* string) {
    srand(time(NULL));
    int i = 0;
    while (i < Secret_Code_Length) {
        char temp = rand() % 9 + '0';
        if (Checking_Function_for_Generator(string, temp) == 0) {
            string[i] = temp;
            i++;
        }
    }
}

int The_Checker(char* the_secret_code, char* the_user_input){
    int well_placed = 0, miss_placed = 0 ;
    for (int i = 0; i < Secret_Code_Length; ++i) {
        for (int j = 0; j < Secret_Code_Length; ++j){
            if (the_secret_code[j] == the_user_input[i] && the_secret_code[i] != the_user_input[i]) {
                miss_placed++;
            }
        }
    }
    for (int i = 0; i < Secret_Code_Length; ++i) {
        if (the_secret_code[i] == the_user_input[i])
            well_placed++;
    }
    if (well_placed == 4) {
        printf("Congratz! You did it!\n");
        Stoper += 1;
        return 0;
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, miss_placed);
    return 0;
}

int The_Second_Main_Function(char* the_secret_code, int attempts){
    if (Checking_Function(the_secret_code) == 1) Stoper += 1;
    else printf("\nWelcome to game mastermind\nWill you find the secret code?\nPlease enter a valid guess\n");
    for (int round = 1; round <= attempts; ++round){
        if (Stoper != 0) break;
        printf("---\nRound %i\n> ", round);
        while(1){
            char* users_guess = The_Scan_Function();
            if (users_guess == NULL) {
                Stoper += 1;
                return 0;
            }
            if (Checking_Function(users_guess) == 1 || My_Str_Len(users_guess) != 4) printf("wrong input\n> ");
            else {
                The_Checker(the_secret_code, users_guess);
                break;
            }        
        }
    }
    return 0;
}


int main(int argc, char** argv) {
    char secret_code[Secret_Code_Length] = {0};
    int rounds = 10, secret_c = 1;
    if (argc > 1) {
        for (int i = 0; i < argc; ++i) {
            if ((argc == 3 && strcmp(argv[i],"-c") == 0) || (argc == 5 && strcmp(argv[i],"-c") == 0)) {
                for (int j = 0; j < Secret_Code_Length && argv[i+1][j] != '\0'; ++j) {
                    secret_code[j] = argv[i+1][j];
                }
                secret_c = 0;
            }
            if ((argc == 3 && strcmp(argv[i],"-t") == 0) || (argc == 5 && strcmp(argv[i],"-t") == 0)){
                rounds = atoi(argv[i+1]);
            }
        }
    }
    if (argc == 2 || argc == 4 || argc > 5) Stoper += 1;
    if (secret_c == 1) Generate_Secret_Code(secret_code);
    if (rounds != 0 && Stoper == 0) The_Second_Main_Function(secret_code, rounds);
}
