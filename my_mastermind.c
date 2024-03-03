#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define CODE_LENGTH 4

void GenerateSecretCode(char *code){
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++){
        code[i] = '0' + rand() % 9;
    }
    code[CODE_LENGTH] = '\0';
}

int CheckValidGuessts(char *guess){
    if (strlen(guess) != CODE_LENGTH){
        return 0;
    }
    for (int i = 0; i < CODE_LENGTH; i++){
        if (guess[i] < '0' || guess[i] > '8'){
            return 0;
        }
        for (int j = i + 1; j < CODE_LENGTH; j++){
            if (guess[i] == guess[j]){
                return 0;
            }
        }
    }
    return 1;
}

void ReadGuessts(char *guess){
    char c;
    int i = 0;
    while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n'){
        guess[i++] = c;
    }
    guess[i] = '\0';
    while (c != '\n' && read(STDIN_FILENO, &c, 1) > 0);
}

int CounterPlaces(char *secretCode, char *guessCode){
   int well_placed = 0, misplaced = 0;
    for (int i = 0; i < CODE_LENGTH; i++){
        if (secretCode[i] == guessCode[i]){
            well_placed++;
        }
        else if (strchr(secretCode, guessCode[i])){
            misplaced++;
        }
    }

    if (well_placed == CODE_LENGTH){
        return 1;
    }

    printf("Well placed pieces: %d\n", well_placed); 
    printf("Misplaced pieces: %d\n", misplaced);
    return 0;
}

void UserAttempts(char *secretCode,char *guessCode, int maxRound){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (int round = 0; round < maxRound; round++){
        printf("---\nRound: %d\n>", round);
        ReadGuessts(guessCode);
        if (!CheckValidGuessts(guessCode)){
            round--;
            printf("Wrong input!\n");
            continue;
        }else if ( CounterPlaces(secretCode, guessCode) == 1){
            printf("Congratz! You did it!\n");
            break;
        }
    }
}

int main(int argc, char *argv[]){
    char secretCode[CODE_LENGTH + 1] = {0};
    char guessCOde[CODE_LENGTH + 1];
    int maxRounds = 10;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            strncpy(secretCode, argv[i + 1], CODE_LENGTH);
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            maxRounds = atoi(argv[i + 1]);
        }
    }

    if (!secretCode[0]){
        GenerateSecretCode(secretCode);
    }

    UserAttempts(secretCode,guessCOde, maxRounds);
    return 0;
}
