#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int compare_strings(const char *str1, const char *str2) {
    return strcmp(str1, str2) == 0;
}
char *code_random_generate() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    char *code = (char *)malloc(sizeof(char) * 4);
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
    char input[4] = {0};
    char c = 0;
    int j = 0, flag = 1;
    do {
        printf(">");
        j = 0;
        while ((flag = read(0, &c, 1)) > 0) {
            if (c == '\n') {
                input[j] = '\0';
                break;
            }
            input[j++] = c;
        }
        if (flag == 0)
            break;
    } while (argument_length_error(input) || incorrect_range(input) || incorrect_duplicates(input));
    return strdup(input);
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
    for (int i = 0; i < 8; i++) {
        if (common & (1 << i))
            missed++;
    }
    missed -= well;
    return well * 10 + missed;
}
void result_game(const char *code, const char *guess) {
    int result = find_true_or_false_codes(code, guess);
    int well = result / 10;
    int missed = result % 10;
    if (well == 4) {
        printf("Congratz! You did it!   \n");
    } else {
        printf("Well placed pieces: %d\n", well);
        printf("Misplaced pieces: %d\n", missed);
    }
}
void play_game(int attempts, const char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i + 1);
        char *guess = receive_information();
        find_true_or_false_codes(code, guess);
        result_game(code, guess);
        free(guess);
    }
}
void parse_arguments(int argc, char **argv, int *attempts, const char **code) {
    *attempts = 9;
    *code = NULL;
    if (argc >= 3) {
        for (int i = 1; i < argc; i++) {
            if (compare_strings(argv[i], "-t")) {
                *attempts = atoi(argv[i + 1]);
                i++;    
            } else if (compare_strings(argv[i], "-c")) {
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
