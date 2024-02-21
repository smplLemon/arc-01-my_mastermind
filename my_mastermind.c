#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  
#include <unistd.h>
  
int strlen_mine(char* str) {  
    int len = 0;  
    while (str[len]) {  
        len++;  
    }  
    return len;  
}  
  
int strcmp_mine(char* str1, char* str2) {  
    int len1 = strlen_mine(str1);  
    int len2 = strlen_mine(str2);  
  
    if (len1 != len2) {  
        return 1;  
    }  
    for (int i = 0; i < len1; i++) {  
        if (str1[i] != str2[i]) {  
            return 1;  
        }  
    }  
    return 0;  
}  
  
char* strcpy_mine(char* buffer, char* str) {  
    return strcpy(buffer, str);  
}  
  
int my_atoi(char* str) {  
    if (*str == '\0') {  
        return 0;  
    }  
  
    int result = 0, i = 0;  
    char temp;  
    while (str[i]) {  
        temp = str[i];  
        if (temp < '0' || temp > '9') {  
            return result;  
        }  
        result *= 10;  
        result += temp - '0';  
        i++;  
    }  
    return result;  
}  
  
void play_game(char* secret_code, int attempts) {  
    printf("Will you find the secret code?\n");  
    printf("Please enter a valid guess\n");  
  
    char guess[5]; 
    for (int round = 0; round < attempts; round++) {  
        printf("---\nRound %d\n>", round);  
        if (read(0, guess, 5) == -1) {  
            printf("Error reading input\n");  
            exit(EXIT_FAILURE);  
        }  
        guess[strcspn(guess, "\n")] = '\0';  
        if (strlen_mine(guess) != 4) {  
            printf("Wrong input!\n");  
            continue;  
        }  
        if (strcmp_mine(guess, secret_code) == 0) {  
            printf("Congratulations! You did it!\n");  
            return;  
        }  
        int well_placed = 0, misplaced = 0;  
        for (int i = 0; i < 4; i++) {  
            if (guess[i] == secret_code[i]) {  
                well_placed++;  
            } else if (strchr(secret_code, guess[i]) != NULL) {  
                misplaced++;  
            }  
        }  
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);  
    }  
    printf("Your attempts are over. The secret code was %s\n", secret_code);  
}  
  
void main_work(int argc, char** argv) {  
    char secret_code[5] = "";  
    int attempts = 10;  
    for (int i = 0; i < argc; i++) {  
        if (strcmp_mine(argv[i], "-c") == 0) {  
            if (i + 1 < argc) {  
                strcpy_mine(secret_code, argv[i + 1]);  
            } else {  
                printf("No secret code provided after -c option\n");  
                return;  
            }  
        } else if (strcmp_mine(argv[i], "-t") == 0) {  
            if (i + 1 < argc) {  
                attempts = my_atoi(argv[i + 1]);  
            } else {  
                printf("No number of attempts provided after -t option\n");  
                return;  
            }  
        }  
    }  
    if (strlen_mine(secret_code) != 4) {  
        srand(time(NULL));  
        for (int i = 0; i < 4; i++) {  
            secret_code[i] = '0' + rand() % 9;  
        }  
        secret_code[4] = '\0';  
    }  
    play_game(secret_code, attempts);  
}  
  
int main(int argc, char** argv) {  
    main_work(argc, argv);  
    return 0;  
}