

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define CODE_LENGTH 4

char *generate_random_code();
int is_input_incorrect(char *input);
void parse_arguments(int argc, char **argv, int *attempts, char **code);
void evaluate_guess(char *input, char *code);
void play_game(int attempts, char *code);
void print_welcome_message();
void print_round_header(int round);
char *read_input();
void print_congratulations_message();
void print_feedback(int well, int missed);
int count_well_placed(char *input, char *code);
int count_missed_placed(char *input, char *code);
int is_guess_correct(char *input, char *code);
void handle_game_over(char *code);


int main(int argc, char **argv) {
    int attempts;
    char *code;
    parse_arguments(argc, argv, &attempts, &code);
    if (code == NULL)
        code = generate_random_code();
    play_game(attempts, code);
    return 0;
}

char *generate_random_code() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }

    char *code = (char *)malloc(sizeof(char) * (CODE_LENGTH + 1));
    int used = 0;
    int count = 0;

    while (count < CODE_LENGTH) {
        int num = rand() % 9;
        if (!(used & (1 << num))) {
            code[count] = num + '0';
            used |= (1 << num);
            count++;
        }
    }
    code[CODE_LENGTH] = '\0';
    return code;
}


int is_input_incorrect(char *input) {
    if (strlen(input) != CODE_LENGTH) {
        printf("Wrong input!\n");
        return 1;
    }

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 1;
        }
    }

    for (int i = 0; i < CODE_LENGTH; i++) {
        for (int j = i + 1; j < CODE_LENGTH; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input!\n");
                return 1;
            }
        }
    }

    return 0;
}


void parse_arguments(int argc, char **argv, int *attempts, char **code) {
    *attempts = 10;
    *code = NULL;

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


void evaluate_guess(char *input, char *code) {
    int well = count_well_placed(input, code);
    int missed = count_missed_placed(input, code) - well;

    if (well == CODE_LENGTH) {
        print_congratulations_message();
        handle_game_over(code);
    } else {
        print_feedback(well, missed);
    }
}


void play_game(int attempts, char *code) {
    print_welcome_message();
    for (int i = 0; i < attempts; i++) {
        print_round_header(i);
        char *input;
        do {
            input = read_input();
        } while (is_input_incorrect(input));
        evaluate_guess(input, code);
        free(input);
    }
    handle_game_over(code);
}


void print_welcome_message() {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
}


void print_round_header(int round) {
    printf("---\nRound %d\n", round);
}

char *read_input() {
    printf(">");
    char *input = (char *)malloc(sizeof(char) * (CODE_LENGTH + 1));
    scanf("%s", input);
    return input;
}


void print_congratulations_message() {
    printf("Congratz! You did it!\n");
}


void print_feedback(int well, int missed) {
    printf("Well place pieces: %d\n", well);
    printf("Missed place pieces: %d\n", missed);
}


int count_well_placed(char *input, char *code) {
    int well = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (code[i] == input[i]) well++;
    }
    return well;
}


int count_missed_placed(char *input, char *code) {
    int code_used = 0, input_used = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        code_used |= (1 << (code[i] - '0'));
        input_used |= (1 << (input[i] - '0'));
    }
    int common = code_used & input_used;
    int missed = 0;
    for (int i = 0; i < 9; i++) {
        if (common & (1 << i))
            missed++;
    }
    return missed;
}


int is_guess_correct(char *input, char *code) {
    return strcmp(input, code) == 0;
}


void handle_game_over(char *code) {
    printf("The secret code was: %s\n", code);
    exit(0);
}