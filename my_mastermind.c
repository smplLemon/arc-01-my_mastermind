#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *generate_random_code() {
    srand(time(NULL));
    char *code = (char *)malloc(sizeof(char) * 5);
    for (int i = 0; i < 4; i++) {
        code[i] = rand() % 10 + '0';
        for (int j = 0; j < i; j++) {
            if (code[i] == code[j]) {
                i--;
                break;
            }
        }
    }
    code[4] = '\0';
    return code;
}

void printMessage() {
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
}

int confirm_input(char *input) {
    int length = strlen(input);
    if (length != 4) {
        printf("Wrong input!\n");
        return 1;
    }
    for (int i = 0; i < length; i++) {
        if (input[i] < '0' || input[i] > '8') {
            printf("Wrong input!\n");
            return 1;
        }
    }
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input!\n");
                return 1;
            }
        }
    }
    return 0;
}

int get_max_attempts(int argc, char **argv) {
    int max_attempts = 10;
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            max_attempts = atoi(argv[i + 1]);
            break;
        }
    }
    return max_attempts;
}

char *get_code(int argc, char **argv) {
    char *code = NULL;
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            code = argv[i + 1];
            break;
        }
    }
    return code;
}

int check_well_placed(char *code, char *input) {
    int well_placed = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == input[i]) {
            well_placed++;
        }
    }
    return well_placed;
}

int check_miss_placed(char *code, char *input) {
    int miss_placed = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (input[i] == code[j] && i != j) {
                miss_placed++;
                break;
            }
        }
    }
    return miss_placed;
}

void get_input(char input[]) {
    char c = 0;
    int j = 0;
    int flag = 1;

    do {
        write(1, ">", 1);
        j = 0;
        while ((flag = read(0, &c, 1)) > 0) {
            if (c == '\n' || c == EOF) {
                input[j] = '\0';
                break;
            }
            input[j] = c;
            j++;
        }
        if (flag == 0) return 1; 
    } while (confirm_input(input));
}

int get_user_input(int max_attempts, char *code) {
    char input[10] = {0};
    int well_placed, miss_placed;

    for (int i = 0; i < max_attempts; i++) {
        printf("---\nRound %d\n", i);
        get_input(input);
        well_placed = check_well_placed(code, input);
        miss_placed = check_miss_placed(code, input);
        if (well_placed == 4) {
            printf("Congratz! You did it\n");
            return 1;
        } else {
            printf("Well placed pieces: %d\n", well_placed);
            printf("Miss placed pieces: %d\n", miss_placed);
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    printMessage();
    char *code = get_code(argc, argv);
    if (code == NULL) code = generate_random_code();
    int max_attempts = get_max_attempts(argc, argv);
    int result = get_user_input(max_attempts, code);
    if (result == 0) return 1;
    if (code != NULL) free(code);
    return 0;
}
