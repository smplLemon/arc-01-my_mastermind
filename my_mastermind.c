#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LENGTH(str) strlen(str)

void copy(char* dest, const char* source) {
    for (int i = 0; i < LENGTH(source); i++) dest[i] = source[i];
}

int string(const char* str, char c) {
    for (int i = 0; i < LENGTH(str); i++) if (str[i] == c) return 1;
    return 0;
}

char* skan() {
    printf(">");
    fflush(stdout);
    char* input = calloc(5, sizeof(char));
    char temp;
    int i = 0;
    while (read(0, &temp, 1)) {
        if (temp == '\n') return input;
        input[i++] = temp;
    }
    return NULL;
}

char* randomayzer() {
    char* random = calloc(5, sizeof(char));
    int i = 0;
    srand(time(0));
    while (i < 4) {
        char temp = rand() % 9 + 48;
        if (!string(random, temp)) random[i++] = temp;
    }
    return random;
}

int checking_alpha(const char* input) {
    for (int i = 0; i < LENGTH(input); i++) if (!(input[i] >= 48 && input[i] <= 56)) return 0;
    return 1;
}

int checkingdup(const char* input) {
    for (int i = 0; i < LENGTH(input); i++) for (int j = i + 1; j < LENGTH(input); j++) if (input[i] == input[j]) return 0;
    return 1;
}

int welplaced(const char* sc_code, const char* users_vvod) {
    int count = 0;
    for (int i = 0; i < LENGTH(sc_code); i++) if (sc_code[i] == users_vvod[i]) count++;
    return count;
}

int misplaced(const char* sc_code, const char* users_vvod) {
    int count = 0;
    for (int i = 0; i < LENGTH(sc_code); i++) for (int j = 0; j < LENGTH(users_vvod); j++) if (sc_code[i] == users_vvod[j] && i != j) count++;
    return count;
}

int gen_checkning(const char* input) {
    if (LENGTH(input) != 4 || !checking_alpha(input) || !checkingdup(input)) return 0;
    return 1;
}

void main_func(int attempts, const char* sc_code) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    char* input;
    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i);
        input = skan();
        if (input == NULL) return;
        while (!gen_checkning(input)) {
            free(input);
            printf("Wrong input!\n");
            input = skan();
        }
        int well = welplaced(sc_code, input);
        int miss = misplaced(sc_code, input);
        if (well == 4) {
            printf("Congrats! You did it!\n");
            return;
        } else {
            printf("Well placed pieces: %d\n", well);
            printf("Misplaced pieces: %d\n", miss);
        }
    }
}

int main(int argc, char** argv) {
    int index = 0, attempts = 10;
    char* secret_code = NULL;
    while (index < argc) {
        if (strcmp(argv[index], "-c") == 0) {
            index++;
            secret_code = malloc(sizeof(char) * 5);
            copy(secret_code, argv[index]);
        } else if (strcmp(argv[index], "-t") == 0) {
            index++;
            attempts = atoi(argv[index]);
        }
        index++;
    }
    if (secret_code == NULL) secret_code = randomayzer();
    main_func(attempts, secret_code);
    return 0;
}
