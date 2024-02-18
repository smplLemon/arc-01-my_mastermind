#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

int my_strlen(char* string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}

char* my_strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == c)
            return (char*)str;
        str++;
    }
    return NULL;
}

int well_placed(char* secret_code, char* users_input) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (users_input[i] == secret_code[i]) {
            count++;
        }
    }
    return count;
}

int misplaced(char* secret_code, char* users_input) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (users_input[i] == secret_code[j] && i != j) {
                count++;
            }
        }
    }
    return count;
}

int checker(char* secret_code, char* users_input) {
    if (strcmp(secret_code, users_input) == 0) {
        printf("Congratz! You did it!\n");
        return 1;
    }
    printf("Well placed pieces: %d\n", well_placed(secret_code, users_input));
    printf("Misplaced pieces: %d\n", misplaced(secret_code, users_input));
    return 0;
}

char* my_scanf() {
    char* string = (char*) malloc(1);
    int size = 0; 
    char c;
    while (read(0, &c, 1) == 1) {
        if (c == '\n') break;
        string[size] = c;
        size++;
    }
    string[size] = '\0';
    return string;
}

int is_number_valid(char* string) {
    if (my_strlen(string) != 4) return 1;

    int count[10] = {0};
    for (int i = 0; i < 4; i++) {
        if (!(string[i] >= '0' && string[i] <= '8')) {
            return 1;
        }
        int digit = string[i] - '0';
        if (count[digit] > 0) {
            return 1;
        }
        count[digit]++;
    }
    return 0;
}

void second_main(char* code, int rounds) {
    if (is_number_valid(code) || rounds < 1) exit(1);
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int i = 1; i <= rounds; ++i) {
        printf("---\nRound %d\n", i);
        while (1) {
            printf(">");
            char* users_input = my_scanf();
            if (is_number_valid(users_input)) {
                printf("Wrong input!\n");
            }
            else {
                if (checker(code, users_input) == 1) return;
                break;
            }
        }
    }
    printf("Game over! You didn't find the secret code.\n");
}

char* generate_code() {
    char* code = malloc(5 * sizeof(char));
    if (code == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    srand((unsigned)time(NULL));
    int i = 0;
    while (i < 4) {
        char str = rand() % 9 + '0';
        if (my_strchr(code, str) == NULL) {
            code[i] = str;
            i++;
        }
    }
    code[4] = '\0';
    return code;
}

int main(int argc, char** argv) {
    char* Secret_Code = generate_code();
    int rounds = 10;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (argv[i+1] == NULL || i + 1 > argc) 
                exit(1);
            rounds = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-c") == 0) {
            if (argv[i+1] == NULL || i + 1 > argc) 
                exit(1);
            Secret_Code = argv[i + 1];
        }
    }
    second_main(Secret_Code, rounds);
    return 0;
}