#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h>
#include <stdbool.h> 
#include <string.h> 

#define CODE_LENGTH 4 

int my_strlen(char* p1){
    int i = 0;
    while(p1[i]){
        i++;
    }
    return i;
}

char* my_scanf() {
    char c;
    int i = 0;
    char* str = calloc(sizeof(char), 6);
    write(1,">", 1);
    while(read(0, &c, 1)) {
        if(c == '\n' || i == 5) {
            return str;
        }
        str[i] = c;
        i++;
    }
    return "stop";
}

char* my_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int getStrLength(char string[]) { 
    int length = 0; 
    for (int i = 0; string[i] != '\0'; ++i) { 
        length++; 
    } 
    return length; 
} 

int findChar(char *str, char letter) { 
    for (int i = 0; str[i] != '\0'; i++) { 
        if (str[i] == letter) { 
            return true; 
        } 
    } 
    return false; 
} 

void calculate_clues(char *secret_code, char *user_guess) { 
    int well_placed = 0; 
    int misplaced = 0; 
    for (int i = 0; i < CODE_LENGTH; ++i) { 
        if (secret_code[i] == user_guess[i]) { 
            well_placed++; 
        } else if (findChar(secret_code, user_guess[i]) == true) { 
            misplaced++; 
        } 
    } 
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced); 
} 

bool isNumRepeat(int number, char *array, int size) { 
    for (int i = 0; i < size; ++i) { 
        if (array[i] == number) { 
            return true; 
        } 
    } 
    return false; 
} 

bool isValidGuess(char *user_guess) { 
    if (getStrLength(user_guess) != CODE_LENGTH) { 
        return false;
    } else {
        for (int i = 0; i < CODE_LENGTH; ++i) {
            if (!(user_guess[i] >= '0' && user_guess[i] <= '8') || isNumRepeat(user_guess[i], user_guess, i)) {
                return false;
            }
        }
        return true;
    }
}

char* get_user_guess() {
    char prompt[] = "> ";
    char user_guess[100];

    write(1, prompt, my_strlen(prompt));

    int num_bytes = read(0, user_guess, sizeof(user_guess));
    if (num_bytes <= 0) {
        return NULL;
    }

    if (num_bytes > 0 && user_guess[num_bytes - 1] == '\n') {
        user_guess[num_bytes - 1] = '\0';
    }

    return strdup(user_guess);
}

void playGame(char *secret_code, int turns) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int round = 0; round < turns; ++round) {
        printf("---\nRound %d\n", round);
        char *user_guess = get_user_guess();
        if (user_guess == NULL) {
            return;
        }
        if (!isValidGuess(user_guess)) {
            printf("Wrong input\n");
            free(user_guess);
            round--;
            continue;
        }
        if (strcmp(secret_code, user_guess) == 0) {
            printf("Congratz! You did it!\n");
            free(user_guess);
            return;
        } else {
            calculate_clues(secret_code, user_guess);
        }
        free(user_guess);
    }
    printf("Game Over!!!\n");
}

char *generateSecretCode(char *rand_code) {
    srand(time(NULL));
    char temp;
    int i = 0;
    while (i < CODE_LENGTH) {
        temp = rand() % 9 + '0';
        if (findChar(rand_code, temp) == 0) {
            rand_code[i] = temp;
            i++;
        }
    }
    rand_code[CODE_LENGTH] = '\0';
    return rand_code;
}

int main(int argc, char* argv[]) {
    int turns = 10;
    char secret_code[CODE_LENGTH + 1];

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            turns = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            my_strcpy(secret_code, argv[i + 1]);
        }
    }

    if (getStrLength(secret_code) != CODE_LENGTH || !isValidGuess(secret_code)) {
        generateSecretCode(secret_code);
    }

    playGame(secret_code, turns);
    return 0;
