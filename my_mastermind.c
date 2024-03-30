#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char *my_random();
int is_incorrect(char *input);
char *get_user_guess();
void evaluate_guess(char *code, char *guess);
void play_game(int attempts, char *code);
void print_wrong_input();
void print_congratulations();
void print_round(int round);
void print_well_place_pieces(int well);
void print_missed_place_pieces(int missed);
void print_sorry_message();
void handle_game_arguments(int argc, char **argv);
void handle_code_generation(char **code);
void handle_gameplay(int attempts, char *code);

char *my_random() {
    srand(time(NULL));
    char *code = (char *)malloc(sizeof(char) * 5);
    int used = 0, count = 0;

    while (count < 4) {
        int num = rand() % 9;
        if (!(used & (1 << num))) {
            code[count++] = num + '0';
            used |= (1 << num);
        }
    }
    code[4] = '\0';
    return code;
}
int is_incorrect(char *input) {
    if (input[0] == '\0' || input[4] != '\0') {
        print_wrong_input();
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            print_wrong_input();
            return 1;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                print_wrong_input();
                return 1;
            }
        }
    }

    return 0;
}

char *my_strdup(const char *input) {
    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    char *new_str = (char *)malloc(len + 1);
    if (new_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i <= len; i++) {
        new_str[i] = input[i];
    }

    return new_str;
}

char *get_user_guess() {
    char input[6] = {0}; // Increase size to accommodate null terminator
    char c = 0;
    int j = 0, flag = 1;

    do {
        write(1, ">", 1);
        j = 0;
        while ((flag = read(0, &c, 1)) > 0) {
            if (c == '\n') {
                input[j] = '\0';
                break;
            }
            input[j++] = c;
        }

        if (flag == 0)
            exit(0);

    } while (is_incorrect(input));

    return my_strdup(input);
}

void evaluate_guess(char *code, char *guess) {
    int well = 0, missed = 0;
    int code_used = 0, input_used = 0;

    for (int i = 0; i < 4; i++) {
        if (code[i] == guess[i])
            well++;
        code_used |= (1 << (code[i] - '0'));
        input_used |= (1 << (guess[i] - '0'));
    }

    int common = code_used & input_used;
    for (int i = 0; i < 9; i++) {
        if (common & (1 << i))
            missed++;
    }
    missed -= well;

    if (well == 4) {
        print_congratulations();
        exit(0);
    } else {
        print_well_place_pieces(well);
        print_missed_place_pieces(missed);
    }
}

void play_game(int attempts, char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");

    for (int i = 0; i < attempts; i++) {
        print_round(i);
        char *guess = get_user_guess();
        evaluate_guess(code, guess);
        free(guess);
    }

    print_sorry_message();
}

void print_wrong_input() {
    printf("Wrong input!\n");
}

void print_congratulations() {
    printf("Congratz! You did it!\n");
}

void print_round(int round) {
    printf("---\nRound %d\n", round);
}

void print_well_place_pieces(int well) {
    printf("Well place pieces: %d\n", well);
}

void print_missed_place_pieces(int missed) {
    printf("Missed place pieces: %d\n", missed);
}

void print_sorry_message() {
    printf("Sorry, you couldn't find the secret code!\n");
}
int strcmp_custom(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

void handle_game_arguments(int argc, char **argv) {
    int attempts = 10;
    char *code = NULL;
    if (argc >= 3) {
        for (int i = 1; i < argc; i++) {
            if (strcmp_custom(argv[i], "-t") == 0) {
                attempts = atoi(argv[i + 1]);
                i++;
            } else if (strcmp_custom(argv[i], "-c") == 0) {
                code = argv[i + 1];
                i++;
            }
        }
    }

    if (code == NULL)
        handle_code_generation(&code);

    handle_gameplay(attempts, code);
}

void handle_code_generation(char **code) {
    *code = my_random();
}

void handle_gameplay(int attempts, char *code) {
    play_game(attempts, code);
}

int main(int argc, char **argv) {
    handle_game_arguments(argc, argv);
    return 0;
}