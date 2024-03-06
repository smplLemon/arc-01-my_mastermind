#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#define Secret_Code_Length 4

int My_Str_Len(char* string){
    int length = 0;
    for (int i = 0; string[i] != '\0'; ++i) length++;
    return length;
}

int Checking_Function(char* users_guess){
    for (int i = 0; i < Secret_Code_Length; ++i){
        if (users_guess[i] < '0' || users_guess[i] > '8') return 1;
        for (int j = 0; j < i; ++j){
            if (users_guess[i] == users_guess[j]){
                return 1;
            }
        }
    }
    return 0;
}

void Generate_Secret_Code(char* string){
    srand(time(NULL));
    for (int i = 0; i < Secret_Code_Length; ++i){
        string[i] = rand() % 9 + '0';
    }
}

void The_Checker(char* the_secret_code, char* the_user_input){
    int well_placed = 0, miss_placed = 0;
    for (int i = 0; i < Secret_Code_Length; ++i){
        for (int j = 0; j < Secret_Code_Length; ++j){
            if (the_secret_code[j] == the_user_input[i] && the_secret_code[i] != the_user_input[i]){
                miss_placed++;
            }
        }
    }
    for (int i = 0; i < Secret_Code_Length; ++i){
        if (the_secret_code[i] == the_user_input[i]){
            well_placed++;
        }
    }
    if (well_placed == 4)
    {
        printf("Congratz! You did it!\n");
        exit(EXIT_SUCCESS);
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, miss_placed);
}

int The_Second_Main_Function(char* the_secret_code, int attempts){
    printf("\nWelcome to game mastermind\nWill you find the secret code?\nPlease enter a valid guess\n");
    for (int i = 1; i <= attempts; ++i){
        printf("---\nRound %i\n> ", i);
        while(1){
            char users_guess[Secret_Code_Length] = {0};
            scanf("%s", users_guess);
            if (Checking_Function(users_guess) == 1 || My_Str_Len(users_guess) != 4){
                printf("wrong input\n> ");
            }else {
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
  if (argc > 1){
      for (int i = 0; i < argc; ++i) {
          if ((argc == 3 && strcmp(argv[i],"-c") == 0) || (argc == 5 && strcmp(argv[i],"-c") == 0)) {
              strncpy(secret_code, argv[i+1], Secret_Code_Length);
              secret_c = 0;
          }
          if ((argc == 3 && strcmp(argv[i],"-t") == 0) || (argc == 5 && strcmp(argv[i],"-t") == 0)) {
              rounds = atoi(argv[i+1]);
          }
      }
  }
  if (argc == 2) exit(EXIT_FAILURE);
  if(secret_c == 1) Generate_Secret_Code(secret_code);   
  if(rounds != 0) The_Second_Main_Function(secret_code, rounds);
}