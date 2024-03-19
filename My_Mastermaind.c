#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_LENGTH 4

char *code_random_generate() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    char *code = (char *)malloc(sizeof(char) * 5);
    int used = 0, count = 0;
    while (count < 4) {
        int num = rand() % 8;
        if (!(used & (1 << num))) {
            code[count++] = num + '0';
            used |= (1 << num);
        }
    }
    code[4] = '\0';
    return code;
}

int argument_length_error(const char *input) {
    if (strlen(input) != 4) {
        printf("Wrong input!\n");
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        if (input[i] == '9') {
            printf("Wrong input!\n");
            return 1;
        }
    }
    return 0;
}

int incorrect_range(const char *input) {
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 1;
        }
    }
    return 0;
}

int incorrect_duplicates(const char *input) {
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

char *receive_information() {
    char *input = (char *)malloc(MAX_INPUT_LENGTH + 1); 
    if (input == NULL) {
        return NULL;
    }
    
    char c = 0;
    int j = 0, flag = 1;
    do {
        printf("> ");
        j = 0;
        while ((flag = read(0, &c, 1)) > 0) {
            if (c == '\n') {
                input[j] = '\0';
                break;
            }
            input[j++] = c;
        }
        if (flag == 0) {
            free(input);
            return NULL;
        }
    } while (argument_length_error(input) || incorrect_range(input) || incorrect_duplicates(input));
    
    return input;
}
int find_true_or_false_codes(const char *code, const char *guess) {
    int well = 0, missed = 0;
    int code_used = 0, input_used = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == guess[i]) well++;
        code_used |= (1 << (code[i] - '0'));
        input_used |= (1 << (guess[i] - '0'));
    }
    int common = code_used & input_used;
    for (int i = 0; i < 4; i++) {
        if (common & (1 << (code[i] - '0')))
            missed++;
    }
    missed -= well;
    return well * 10 + missed;
}

int result_game(const char *code, const char *guess) {
    int result = find_true_or_false_codes(code, guess);
    int well = result / 10;
    int missed = result % 10;
    if (well == 4) {
        printf("Congratz! You did it!\n");
        return 1;
    } else {
        printf("Well placed pieces: %d\n", well);
        printf("Misplaced pieces: %d\n", missed);
        return 0;
    }
}

void play_game(int attempts, const char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i + 1);
        char *guess = receive_information();
        if(guess == NULL) return;
        find_true_or_false_codes(code, guess);
        if(result_game(code, guess)) return;
        free(guess);
    }
}

void parse_arguments(int argc, char **argv, int *attempts, const char **code) {
    *attempts = 9;
    *code = NULL;
    if (argc >= 3) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-t") == 0) {
                *attempts = atoi(argv[i + 1]);
                i++;    
            } else if (strcmp(argv[i], "-c") == 0) {
                *code = argv[i + 1];
                i++;
            }
        }
    }
    if (*code == NULL)
        *code = code_random_generate();
}

int main(int argc, char **argv) {
    int attempts;
    const char *code;
    parse_arguments(argc, argv, &attempts, &code);
    play_game(attempts, code);
    return 0;
}
