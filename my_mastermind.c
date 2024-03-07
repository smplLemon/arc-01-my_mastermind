#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int my_strlen(char* string);
char* my_strchr(const char* str, int c);
int well_placed(char* secret_code, char* users_input);
int misplaced(char* secret_code, char* users_input);
int checker(char* secret_code, char* users_input);
char* my_scanf();
int is_number_valid(char* string);
void second_main(char* code, int rounds);
char* generate_code();
void print_congratulations();
void print_feedback(int well_placed_count, int misplaced_count);
void print_guess_prompt();
void print_round_header(int round_number);
void print_game_over();
int get_rounds(int argc, char** argv);
char* get_secret_code(int argc, char** argv);
int process_user_input(char* code, int rounds);
int validate_input(char* string);
void initialize_random_seed();
char generate_random_digit();
char* generate_unique_code();


int my_strlen(char* string) {
    return strlen(string);
}

char* my_strchr(const char* str, int c) {
    return strchr(str, c);
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
        print_congratulations();
        return 1;
    }
    int well_placed_count = well_placed(secret_code, users_input);
    int misplaced_count = misplaced(secret_code, users_input);
    print_feedback(well_placed_count, misplaced_count);
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
    print_guess_prompt();
    for (int i = 0; i < rounds; ++i) {
        print_round_header(i);
        while (1) {
            printf(">");
            char* users_input = my_scanf();
            if (is_number_valid(users_input)) {
                printf("Wrong input!\n");
            } else {
                if (checker(code, users_input) == 1) return;
                break;
            }
        }
    }
    print_game_over();
}

char* generate_code() {
    initialize_random_seed();
    return generate_unique_code();
}

void print_congratulations() {
    printf("Congratz! You did it!\n");
}

void print_feedback(int well_placed_count, int misplaced_count) {
    printf("Well placed pieces: %d\n", well_placed_count);
    printf("Misplaced pieces: %d\n", misplaced_count);
}

void print_guess_prompt() {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
}

void print_round_header(int round_number) {
    printf("---\nRound %d\n", round_number);
}

void print_game_over() {
    printf("Game over! You didn't find the secret code.\n");
}

int get_rounds(int argc, char** argv) {
    int rounds = 10;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (argv[i+1] == NULL || i + 1 > argc) {
                exit(1);
            }
            rounds = atoi(argv[i + 1]);
        }
    }
    return rounds;
}



char* get_secret_code(int argc, char** argv) {
    char* Secret_Code = generate_code();
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (argv[i+1] == NULL || i + 1 > argc) {
                exit(1);
            }
            Secret_Code = argv[i + 1];
        }
    }
    return Secret_Code;
}

int process_user_input(char* code, int rounds) {
    second_main(code, rounds);
    return 0;
}

int validate_input(char* string) {
    return is_number_valid(string);
}

void initialize_random_seed() {
    srand((unsigned)time(NULL));
}

char generate_random_digit() {
    return rand() % 9 + '0';
}

char* generate_unique_code() {
    char* code = malloc(5 * sizeof(char));
    if (code == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < 4) {
        char digit = generate_random_digit();
        if (my_strchr(code, digit) == NULL) {
            code[i] = digit;
            i++;
        }
    }
    code[4] = '\0';
    return code;
}

int main(int argc, char** argv) {
    char* Secret_Code = get_secret_code(argc, argv);
    int rounds = get_rounds(argc, argv);
    return process_user_input(Secret_Code, rounds);
}
