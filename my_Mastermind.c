#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

bool is_unique(char* arr, char target) {
    for (int i = 0; arr[i]; i++)
        if (arr[i] == target)
            return false;
    return true;
}

int get_length(char* str) {
    return strlen(str);
}

int count_misplaced(char* code1, char* code2) {
    int count = 0;
    for (int i = 0; code1[i]; i++)
        if (!is_unique(code1, code2[i]) && code1[i] != code2[i])
            count++;
    return count;
}

int count_well_placed(char* code1, char* code2) {
    int count = 0;
    for (int i = 0; code1[i]; i++)
        if (code1[i] == code2[i])
            count++;
    return count;
}

int has_duplicates(char* str) {
    for (int i = 0; str[i]; i++)
        for (int j = i + 1; str[j]; j++)
            if (str[i] == str[j])
                return 1;
    return 0;
}

char* read_input() {
    char *input = malloc(100);
    int index = 0;
    char ch;
    while (read(0, &ch, 1) > 0) {
        if (ch != '\n')
            input[index++] = ch;
        else
            return input;
    }
    if (!feof(stdin)) exit(1);
    return input;
}

int check_input_validity(char* input) {
    if (get_length(input) != 4) return printf("Wrong input!\n");
    for (int i = 0; input[i]; i++)
        if ((input[i] > '8' || input[i] < '0') || has_duplicates(input))
            return printf("Wrong input!\n");
    return 0;
}

int get_rounds(int argc, char** argv) {
    int rounds = 10;
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-t") == 0)
            rounds = atoi(argv[++i]);
    return rounds;
}

char* get_secret_code(int argc, char** argv) {
    char* code = NULL;
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-c") == 0)
            return argv[++i];
    return code;
}

void generate_secret_code(char* code) {
    srand(time(NULL));
    for (int i = 0; i < 4; ) {
        char random_char = rand() % 8 + '0';
        if (is_unique(code, random_char))
            code[i++] = random_char;
    }
    code[4] = '\0';
}

void initialize_game(int argc, char** argv, int* rounds, char** secret_code) {
    *rounds = get_rounds(argc, argv);
    *secret_code = get_secret_code(argc, argv);
    if (!(*secret_code)) {
        *secret_code = malloc(5);
        generate_secret_code(*secret_code);
    }
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
}

void play_game(int rounds, char* secret_code) {
    int round_count = 0;
    char user_input[19];
    while (round_count < rounds) {
        printf("---\nRound %d\n", round_count);
        write(1, ">", 1);
        strcpy(user_input, read_input());
        
        if (check_input_validity(user_input)) {
            do {
                write(1, ">", 1);
                strcpy(user_input, read_input());
            } while (check_input_validity(user_input));
        }
        
        int well_placed = count_well_placed(secret_code, user_input);
        int misplaced = count_misplaced(secret_code, user_input);
        
        if (well_placed == 4) {
            printf("Congratz! You did it\n!");
            break;
        } else {
            printf("Well placed pieces: %d\n", well_placed);
            printf("Misplaced pieces: %d\n", misplaced);
        }
        
        round_count++;
    }
}

int main(int argc, char** argv) {
    int rounds;
    char* secret_code;
    initialize_game(argc, argv, &rounds, &secret_code);
    play_game(rounds, secret_code);
    return 0;
}