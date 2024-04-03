#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *generate_random_code();
int is_input_invalid(char *input);
void parse_command_line(int argc, char **argv, int *attempts, char **code);
char *generate_secret_code();
void evaluate_guess(char *input, char *code);
void play_game(int attempts, char *code);
void print_congratulations();
void print_invalid_input();
void print_feedback(int well, int missed);
void read_user_input(char *input);
void initialize_random();
void generate_unique_code(char *code);
int count_correct_placements(char *code, char *input);
int count_misplaced_pieces(char *code, char *input);
int is_game_won(int well);
int validate_input_format(char *input);
void initialize_game_state(int argc, char **argv, int *attempts, char **code);
void print_round_info(int round);
void display_prompt();
void finalize_execution();
void print_game_over_message();
void handle_input_reading(char *input, int *flag, char c, int *j);
void handle_no_input_received();
void handle_correct_attempt();
void handle_incorrect_attempt(char *input, char *code);
void print_secret_code_revealed(char *code);
void print_secret_code(char *code);

int main(int argc, char **argv) {
    int attempts;
    char *code;
    initialize_game_state(argc, argv, &attempts, &code);
    play_game(attempts, code);
    finalize_execution();
    return 0;
}

char *generate_random_code() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
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

int is_input_invalid(char *input) {
    if (strlen(input) != 4) {
        printf("Wrong input!\n");
        return 1;
    }
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
    return 0;
}

void parse_command_line(int argc, char **argv, int *attempts, char **code) {
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

char *generate_secret_code() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
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


void evaluate_guess(char *input, char *code) {
    int well = count_correct_placements(code, input);
    int missed = count_misplaced_pieces(code, input);
    if(well < 4)print_feedback(well, missed);
    if (is_game_won(well)) {
        print_congratulations();
    }
}
void play_game(int attempts, char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15] = {0};
    char c = 0;
    int j = 0, flag = 1;
    int game_won = 0; 
    for (int i = 0; i < attempts && !game_won; i++) { 
        printf("---\nRound %d\n", i);
        do {
            display_prompt();
            j = 0;
            while ((flag = read(0, &c, 1)) > 0) {
                if (c == '\n') {
                    input[j] = '\0';
                    break;
                }
                input[j++] = c;
            }
            if (flag == 0) return;
        } while (!validate_input_format(input));
        evaluate_guess(input, code);
        game_won = is_game_won(count_correct_placements(code, input)); 
    }
    if (!game_won) 
        print_game_over_message();
}


void print_congratulations() {
    printf("Congratz! You did it!\n");
}

void print_invalid_input() {
    printf("Wrong input!\n");
}

void print_feedback(int well, int missed) {
    printf("Well place pieces: %d\n", well);
    printf("Missed place pieces: %d\n", missed);
}

void read_user_input(char *input) {
    char c = 0;
    int j = 0, flag = 1;
    while ((flag = read(0, &c, 1)) > 0) {
        if (c == '\n') {
            input[j] = '\0';
            break;
        }
        input[j++] = c;
    }
}

void initialize_random() {
    srand(time(NULL));
}

void generate_unique_code(char *code) {
    int used = 0, count = 0;
    while (count < 4) {
        int num = rand() % 9;
        if (!(used & (1 << num))) {
            code[count++] = num + '0';
            used |= (1 << num);
        }
    }
    code[4] = '\0';
}

int count_correct_placements(char *code, char *input) {
    int well = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == input[i]) well++;
    }
    return well;
}

int count_misplaced_pieces(char *code, char *input) {
    int misplaced = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j && code[i] == input[j]) {
                misplaced++;
                break;
            }
        }
    }
    return misplaced;
}

int is_game_won(int well) {
    return (well == 4);
}

int validate_input_format(char *input) {
    if (strlen(input) != 4) {
        printf("Wrong input!\n");
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input!\n");
                return 0;
            }
        }
    }
    return 1;
}

void initialize_game_state(int argc, char **argv, int *attempts, char **code) {
    *attempts = 10;
    *code = NULL;
    parse_command_line(argc, argv, attempts, code);
    if (*code == NULL)
        *code = generate_secret_code();
}

void print_round_info(int round) {
    printf("---\nRound %d\n", round);
}

void display_prompt() {
    write(1, ">", 1);
}

void finalize_execution() {
}

void print_game_over_message() {
    printf("Game over!\n");
}

void handle_input_reading(char *input, int *flag, char c, int *j) {
    *j = 0;
    while ((*flag = read(0, &c, 1)) > 0) {
        if (c == '\n') {
            input[*j] = '\0';
            break;
        }
        input[(*j)++] = c;
    }
}

void handle_no_input_received() {
    return;
}

void handle_correct_attempt() {
    printf("Congratz! You did it!\n");
}

void handle_incorrect_attempt(char *input, char *code) {
    evaluate_guess(input, code);
}

void print_secret_code_revealed(char *code) {
    printf("The secret code was: %s\n", code);
}


void print_secret_code(char *code) {
    printf("The secret code was: %s\n", code);
}
