#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

char *my_scanf() {
    char *data = calloc(32, sizeof(char));
    int i = 0;
    char c;
    write(1, ">", 1);
    while (read(0, &c, 1)) {
        if (c == '\n' || i > 4) {
            return data;
        }
        data[i++] = c;
    }
    return "EOT";
}

bool isDigit(char *c) {
    for (int i = 0; i < 4; i++) {
        if (c[i] < '0' || c[i] > '8')
            return false;
    }
    return true;
}

bool isFour(char *four) {
    return strlen(four) == 4;
}

int valid_code(char *string) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (string[i] == string[j])
                return 0;
        }
    }
    return 1;
}

char *generatesecretCode() {
    char *secret_code = malloc((4 + 1) * sizeof(char));
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        char num;
        do {
            num = '0' + rand() % 9;
        } while (strchr(secret_code, num) != NULL);
        secret_code[i] = num;
    }
    secret_code[4] = '\0';
    return secret_code;
}

void places(char *secret, char *guess) {
    int wellPlaced = 0;
    int missPlaced = 0;

    for (int i = 0; i < 4; i++) {
        if (secret[i] == guess[i])
            wellPlaced++;
        else {
            for (int j = 0; j < 4; j++) {
                if (i != j && secret[i] == guess[j]) {
                    missPlaced++;
                    break;
                }
            }
        }
    }
    printf("Well placed pieces: %d\nmissPlaced pieces: %d\n", wellPlaced, missPlaced);
}

void check(int rounds, char *secret_num) {
    int r = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\nRound %d\n", r++);
    for (int round = 1; round <= rounds; round++) {
        char *player_guessed = my_scanf();
        if (strcmp(player_guessed, "EOT") == 0) {
            break;
        } else if (valid_code(player_guessed) && isDigit(player_guessed) && isFour(player_guessed)) {
            bool check_bool = strcmp(secret_num, player_guessed) == 0;
            if (!check_bool) {
                places(secret_num, player_guessed);
                if (r != rounds) {
                    printf("---\nRound %d\n", r++);
                }
            } else {
                printf("Congratz! You did it!\n");
                break;
            }
        } else {
            printf("Wrong input!\n");
            round--;
        }
        free(player_guessed);
    }
}

int all_function(int argc, char **argv) {
    int rounds = 10;
    char *secret_num = generatesecretCode();
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-t")) {
            if (!isDigit(argv[i + 1])) {
                rounds = atoi(argv[i + 1]); 
            } else {
                printf("Invalid code!\n");
                return 1;
            }
        } else if (!strcmp(argv[i], "-c")) {
            if (isDigit(argv[i + 1]) && isFour(argv[i + 1])) {
                free(secret_num);
                secret_num = malloc(5 * sizeof(char));
                strcpy(secret_num, argv[i + 1]);
            } else {
                printf("Invalid secret code!\n");
                return 1;
            }
        }
    }
    check(rounds, secret_num);
    free(secret_num);
    return 0;
}

int main(int argc, char **argv) {
    all_function(argc, argv);
    return 0;
}