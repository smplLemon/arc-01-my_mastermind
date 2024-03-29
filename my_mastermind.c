#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

volatile sig_atomic_t ctrl_c_pressed = 0;

void sigint_handler(int signum) {
    (void)signum;
    ctrl_c_pressed = 1;
}

char *generate_code() {
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

int is_incorrect_input(char *input) {
    if (input[0] == '\0' || input[4] != '\0') {
        printf("Wrong input!\n");
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 1;
        }
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input!\n");
                return 1;
            }
        }
    }

    return 0;
}

void display_round(int round_num) {
    printf("---\nRound %d\n", round_num);
}

void get_user_input(char *input) {
    char c;
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

        if (flag == 0 || ctrl_c_pressed) {
            printf("\nExiting game...\n");
            break;
        }

    } while (is_incorrect_input(input));
}

int evaluate_guess(char *code, char *input, int *well, int *missed) {
    *well = 0;
    *missed = 0;
    int code_used = 0, input_used = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == input[i]) (*well)++;
        code_used |= (1 << (code[i] - '0'));
        input_used |= (1 << (input[i] - '0'));
    }
    int common = code_used & input_used;
    for (int i = 0; i < 9; i++) {
        if (common & (1 << i))
            (*missed)++;
    }
    *missed -= *well;

    if (*well == 4) {
        printf("Congratz! You did it!\n");
        return 1; 
    }
    return 0;
}

void display_result(int well, int missed) {
    printf("Well place pieces: %d\n", well);
    printf("Missed place pieces: %d\n", missed);
}

int parse_arguments(int argc, char **argv, char **code, int *attempts) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 't') {
            *attempts = atoi(argv[i + 1]);
            i++;
        } else if (argv[i][0] == '-' && argv[i][1] == 'c') {
            *code = argv[i + 1];
            i++;
        }
    }
    return 0;
}

void start_game(int argc, char **argv) {
    int attempts = 10;
    char *code = NULL;

    parse_arguments(argc, argv, &code, &attempts);

    if (code == NULL)
        code = generate_code();

    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15] = {0};

    int game_over = 0;
    for (int i = 0; i < attempts && !game_over; i++) {
        display_round(i);
        get_user_input(input);
        if (input[0] == '\0') {
            break;
        }
        int well, missed;
        game_over = evaluate_guess(code, input, &well, &missed);
        if (!game_over)
            display_result(well, missed);
        if (ctrl_c_pressed) {
            printf("\nExiting game...\n");
            break;
        }
    }

    if (!game_over && !ctrl_c_pressed)
        printf("Game over! The secret code was: %s\n", code);

    free(code);
}

int main(int argc, char **argv) {
    signal(SIGINT, sigint_handler);

    start_game(argc, argv);
    return 0;
}
