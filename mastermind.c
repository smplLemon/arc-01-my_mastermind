#include "mastermind.h"

int is_input_valid(char *inp);
void count_well_placed(char *inp, char *code);
void count_misplaced(char *inp, char *code);


void mastermind(char *code, int attempts) {
    printf("Will you find the secret code?\n---\n");
    char input[5000];

    for (int i = 0; i < attempts; i++) {
        printf("Round %i\n>",i);
        scanf("%s", input);
        if (is_input_valid(input)) {
            if (strcmp(input, code) == 0) {
                printf("Congratz! You did it!\n");
                break;
            }

            count_well_placed(input, code);
            count_misplaced(input, code);
            printf("---\n");

            if (i == attempts - 1) {
                printf("Failure!!!\n");
                printf("The secret code was %s\n", code);
            }
        } else {
            printf("Wrong input!\n");
            i -= 1;
        }
    }
}

int is_input_valid(char *inp) {
    for (int i = 0, len = strlen(inp); i < len; ++i) {
        if (!isdigit(inp[i]) || len != 4) {
            return 0;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (inp[i] == inp[j]) {
                return 0;
            }
        }
    }

    return 1;
}

void count_well_placed(char *inp, char *code) {
    int count_misplaced = 0;
    for (int i = 0, len = strlen(code); i < len; i++) {
        if (inp[i] == code[i]) {
            count_misplaced++;
        }
    }
    printf("Well placed pieces: %i\n", count_misplaced);
}

void count_misplaced(char *inp, char *code) {
    int wellplaced = 0;
    for (int i = 0, len = strlen(code); i < len; i++) {
        if (inp[i] == code[i]) {
            wellplaced++;
        }
    }

    int occurrence_count = 0;
    for (int i = 0, len_code = strlen(code); i < len_code; i++) {
        for (int j = 0, len_inp = strlen(inp); j < len_inp; j++) {
            if (code[i] == inp[j]) {
                occurrence_count++;
                break;
            }
        }
    }

    printf("Count misplaced pieces: %i\n", occurrence_count-wellplaced);
}
