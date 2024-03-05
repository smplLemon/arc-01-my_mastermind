
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *generateRandomCode() {
    srand(time(NULL));
    char* code = (char *)malloc(sizeof(char) * 5);
    
    for (int i = 0; i < 4; i++) {
        code[i] = rand() % 9 + '0';
        
        for (int j = 0; j < i; j++) {    
            if (code[i] == code[j]) {
                i--;
                break;
            }
        }
    }
    
    code[4] = '\0';
    return code;
}

int isIncorrectInput(char *input) {
    if (strlen(input) != 4) {
        printf("Wrong input!\n");
        return 1;
    } 
    
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 1;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input!\n");
                return 1;
            }
        }
    }
    
    return 0;
}

void playGame(int attempts, char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15] = {0};
    char c = 0;
    int j = 0;
    int flag = 1;
    int correctPlacements, incorrectPlacements;
    
    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i);
        
        do {
            write(1, ">", 1);
            j = 0;
            
            while ((flag = read(0, &c, 1)) > 0) {
                if (c == '\n') {
                    input[j] = '\0';
                    break;
                }
                input[j] = c;
                j++;
            }
            
            if (flag == 0) {
                return;
            }
        } while (isIncorrectInput(input));
        
        correctPlacements = 0;
        incorrectPlacements = 0;
        
        for (int i = 0; i < 4; i++) {
            if (code[i] == input[i]) {
                correctPlacements++;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (input[i] == code[j] && i != j) {
                    incorrectPlacements++;
                }
            }
        }
        
        if (correctPlacements == 4) {
            printf("Congratulations! You did it!\n");
            return;
        } else {
            printf("Correct placements: %d\n", correctPlacements);
            printf("Incorrect placements: %d\n", incorrectPlacements);
        }
    }
}

int main(int argc, char **argv) {
    int attempts = 10;
    char *code = NULL;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            attempts = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-c") == 0) {
            code = argv[i + 1];
        }
    }
    if (code == NULL) {
        code = generateRandomCode();
    }
    playGame(attempts, code);
    return 0;
}
