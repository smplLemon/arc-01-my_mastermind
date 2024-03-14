#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define CODE_LENGTH 4

char* generate_secret_code() {
    srand(time(NULL));
    char *secret_code = (char *)malloc(sizeof(char) * (CODE_LENGTH + 1));
    
    for(int i = 0; i < CODE_LENGTH; i++) {
        secret_code[i] = rand() % 9 + '0';
        for(int j = 0; j < i; j++) {    
            if(secret_code[i] == secret_code[j]) {
                i--;
                break;
            }
        }
    }
    secret_code[CODE_LENGTH] = '\0';
    
    return secret_code;
}

void print_welcome_message() {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
}

void print_round(int round) {
    printf("---\nRound %d\n", round);
}

int is_valid_input(const char *input) {
    if(strlen(input) != CODE_LENGTH) {
        printf("Wrong input!\n");
        return 0;
    } 
    
    for(int i = 0; i < CODE_LENGTH; i++) {
        if(input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 0;
        }
    }
    
    for(int i = 0; i < CODE_LENGTH; i++) {
        for(int j = i + 1; j < CODE_LENGTH; j++) {
            if(input[i] == input[j]) {
                printf("Wrong input!\n");
                return 0;
            }
        }
    }
    
    return 1;
}

int check_guess(char *secret_code, char *guess) {
    int well_placed = 0;
    int miss_placed = 0;
    
    for(int i = 0; i < CODE_LENGTH; i++) {
        if(secret_code[i] == guess[i]) {
            well_placed++;
        }
    }
    
    for(int i = 0; i < CODE_LENGTH; i++) {
        for(int j = 0; j < CODE_LENGTH; j++) {
            if(i != j && guess[i] == secret_code[j]) {
                miss_placed++;
            }
        }
    }
    
    if(well_placed == CODE_LENGTH) {
        printf("Congratz! You did it!\n");
        return 1;
    } else {
        printf("Well place pieces: %d\nMissed place pieces: %d\n", well_placed, miss_placed);
    } 
    return 0;
}

int main(int argc, char **argv) {
    char *secret_code = NULL;
    int max_attempts = 10;
   
    for(int i = 0; i < argc; i++) {
        switch (argv[i][1]) {
            case 't':
                max_attempts = atoi(argv[i+1]);
                break;
            case 'c':
                secret_code = argv[i+1];
                break;
            default:
                break;
        }
    }
    
    if(secret_code == NULL) secret_code = generate_secret_code();
    
    print_welcome_message();
    
    char input[20] = {0};
    char input_index = 0;
    int input_complete = 0;
    int read_status = 1;
    
    for(int i = 0; i < max_attempts; i++) {
        print_round(i);
        while(1) {
            write(1, ">", 1);
            input_complete = 0;
            while((read_status = read(0, &input_index, 1)) > 0) {
                if(input_index == '\n') {
                    input[input_complete] = '\0';
                    break;
                }
                input[input_complete] = input_index;
                input_complete++;
            }
           
            if(read_status == 0) {
                return 0;
            }
            if(is_valid_input(input)) {
                break;
            }
        }
            if(check_guess(secret_code, input)) {
                break;
            }
    }
    
    return 0;
}
