#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void my_strcpy(char* s1, const char* s2) {
    while ((*s1++ = *s2++))
        ;
}

int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int is_exist(const char* s, char c) {
    for (int i = 0; s[i]; i++) {
        if (s[i] == c) {
            return 1;
        }
    }
    return 0;
}

char* code_generator() {
    char* str = calloc(5, sizeof(char));
    srand((unsigned)time(NULL));
    char n;
    for (int i = 0; i < 4;) {
        if (!is_exist(str, n = (char)(rand() % 9 + '0'))) {
            str[i++] = n;
        }
    }
    return str;
}

char* my_readline(char* input) {
    printf("> ");
    return fgets(input, 10, stdin);
}

int is_uniq(const char* input) {
    for (int i = 0; input[i]; i++) {
        if (is_exist(input, input[i]) != 1 || input[i] < '0' || input[i] > '8') {
            return 0;
        }
    }
    return 1;
}

void print_err() {
    printf("Wrong input!\n");
}

int is_input_wrong(const char* input) {
    size_t input_length = strlen(input);
    if (input_length != 4 || !is_uniq(input)) {
        print_err();
        return 1;
    }
    return 0;
}

int win_check(const char* mistery_code, const char* input) {
    int well_placed_pieces = 0;
    int miss_placed_pieces = 0;
    for (int i = 0; input[i]; i++) {
        for (int j = 0; mistery_code[j]; j++) {
            if (input[i] == mistery_code[j]) {
                if (i != j) {
                    miss_placed_pieces++;
                } else {
                    well_placed_pieces++;
                }
            }
        }
    }
    if (well_placed_pieces == 4) {
        printf("Congratz! You did it!\n");
        return 1;
    }
    printf("Well placed pieces: %d\n", well_placed_pieces);
    printf("Misplaced pieces: %d\n", miss_placed_pieces);
    return 0;
}

void mastermind_game(const char* mistery_code, int round_counter) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");
    char input[10];
    for (int i = 0; i < round_counter;) {
        printf("Round %d\n", i);
        if (!my_readline(input)) {
            return;
        }
        if (!is_input_wrong(input)) {
            if (win_check(mistery_code, input) == 1) {
                return;
            }
            i++;
        }
    }
}

int main(int argc, char** argv) {
    char* mistery_code = NULL;
    int round_counter = 10;
    for (int i = 1; i < argc; i++) {
        if (my_strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            mistery_code = argv[++i];
        } else if (my_strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            round_counter = atoi(argv[++i]);
        }
    }
    if (!mistery_code) {
        mistery_code = code_generator();
    }
    mastermind_game(mistery_code, round_counter);
    free(mistery_code);
    return 0;
}