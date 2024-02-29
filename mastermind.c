#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *randomCode() {
    srand(time(NULL));
    char *code = (char *)malloc(sizeof(char) * 5);
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

int enterInput(char *input) {
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

char *getInput() {
    char *input = (char *)malloc(sizeof(char) * 5);
    char c = 0;
    int index = 0;
    int read_status = 1;
    
    do {
        write(1, ">", 1);
        index = 0;
        while ((read_status = read(0, &c, 1)) > 0) {
            if (c == '\n') {
                input[index] = '\0';
                break;
            }
            input[index++] = c;
            printf("%c", c);
        }

        if (read_status == 0) return NULL;

    } while (enterInput(input));  

    return input;
}

void playGame(int rounds, char *secret_code) {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    
    for (int i = 0; i < rounds; i++) {
        printf("---\nRound %d\n", i);
        
        char *input = getInput();
        if (input == NULL) return;

        int correct_positions = 0;
        int misplaced_positions = 0;
        for (int i = 0; i < 4; i++) {
            if (secret_code[i] == input[i]) correct_positions++;
        }
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (input[i] == secret_code[j] && i != j) misplaced_positions++;
            }
        }
        
        if (correct_positions == 4) {
            printf("Congratulations! You made it!\n");
            return;
        } else {
            printf("Well placed pieces: %d\n", correct_positions);
            printf("Misplaced pieces: %d\n", misplaced_positions);
        }
    }
}

int main(int argc, char **argv) {
    int rounds = 10;
    char *secret_code = NULL;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            rounds = atoi(argv[i+1]);
        }
        if (strcmp(argv[i], "-c") == 0) {
            secret_code = argv[i+1];
        }
    }
    
    if (secret_code == NULL) secret_code = randomCode();
    
    playGame(rounds, secret_code);

    return 0;
}