#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void initialize_random() {
    srand(time(NULL));
}

char *generate_random_code() {
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

int is_invalid_input(char *input) {
    if (input[4] != '\0') {
        printf("Wrong input!\n");
        return 1;
    } else {
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
    }
    return 0;
}

char *read_user_input() {
    char input[15] = {0};
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
            return NULL; // Return NULL on end of input
    } while (is_invalid_input(input));
    return strdup(input);
}

void evaluate_guess(char *code, char *guess, int *game_won) {
    int well = 0, missed = 0;
    int code_used = 0, input_used = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == guess[i]) {
            well++;
        }
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
        printf("Congratz! You did it!\n");
        *game_won = 1; // Set game_won to 1 if the game is won
    } else {
        printf("Well placed pieces: %d\n", well);
        printf("Misplaced pieces: %d\n", missed);
    }
}

void print_game_start_message() {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
}

void print_game_result_message() {
    printf("Sorry, you couldn't find the secret code!\n");
}

void play_game(int attempts, char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");

    int game_won = 0; // Flag to indicate if the game is won
    for (int i = 0; i < attempts && !game_won; i++) { // Check game_won flag in loop condition
        printf("---\nRound %d\n", i);
        char *guess = read_user_input();
        if (guess == NULL)
            break; // Break the loop if no more input is available
        evaluate_guess(code, guess, &game_won);
        free(guess);
    }

    if (!game_won)
        print_game_result_message();
}

int get_game_attempts(int argc, char **argv) {
    int attempts = 10;

    if (argc >= 3) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-t") == 0) {
                attempts = atoi(argv[i + 1]);
                i++;
            }
        }
    }

    return attempts;
}

char *get_game_code(int argc, char **argv) {
    char *code = NULL;

    if (argc >= 3) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-c") == 0) {
                code = argv[i + 1];
                i++;
            }
        }
    }

    return code;
}

int main(int argc, char **argv) {
    initialize_random();
    int attempts = get_game_attempts(argc, argv);
    char *code = get_game_code(argc, argv);
    if (code == NULL)
        code = generate_random_code();
    play_game(attempts, code);
    return 0;
}
