#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define CODE_LENGTH 4

void guess(char* str, char* secretCode, int* well, int* mis){
*well = 0;
*mis = 0;
int arr[10] = {0};
int secret[10] = {0};
int i = 0;
while(i<CODE_LENGTH){
    i++;
    if(str[i] == secret[i]){
        (*well)++;
    }
    else {
        arr[str[i] - '0']++;
        secret[secretCode[i] - '0']++;
    }
}

for(int i=0; i<10; i++){
    if(secret[i] < arr[i]){
        *mis += secret[i];
    }
    else {
        *mis += arr[i];
    }
  }
}

char* randGenerated(char* random){
    const char num[] = "0123456789";
    int i = 0;
    while(i < CODE_LENGTH){
        i++;
        random[i] = num[rand() % 10];
    }
    random[CODE_LENGTH] = '\0';
    return random;
}

int inputcheck(char* a){
    if(strlen(a) != CODE_LENGTH){
        return 0;
    }
    int i = 0;
    while(i<CODE_LENGTH){
        i++;
        if(a[i] < '0' || a[i] > '9'){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv){
    char* secretCode = calloc(sizeof(char), CODE_LENGTH + 1);
    int attempts = 10;
    
    for(int i=0; i<10; i++){
        if(strcmp(argv[i], "-c") == 0 && i+1 < argc){
            strncpy(secretCode, argv[i+1], CODE_LENGTH);
            secretCode[CODE_LENGTH] = '\0';
        }
        else if(strcmp(argv[i], "-t") == 0 && i+1 < argc){
            attempts = atoi(argv[i+1]);
        }
    }
    if(strlen(secretCode) == 0){
        srand(time(NULL));
        randGenerated(secretCode);
    }
    char user[CODE_LENGTH + 1];
    int well, mis;
    int round = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while(round < attempts){
        printf("---\nRound %d\n>", round);
        if(read(0, user, CODE_LENGTH + 1) == -1){
            printf("Error reading input.\n");
            return 1;
        }
        user[CODE_LENGTH] = '\0';
        if(!inputcheck(user)){
            printf("Wrong input!\n");
            continue;
        }
        guess(user, secretCode, &well, &mis);
        if(well == CODE_LENGTH){
            printf("Congratz! You did it!\n");
            return 0;
        }
        printf("Well placed pieces: %d\nMis placed pieces: %d\n", well, mis);
        round++;
    }
    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}