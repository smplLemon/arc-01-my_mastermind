#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int my_strlen(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
int my_strcmp(char *str1, char *str2) {
    for (int i = 0; str1[i] || str2[i]; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }
    return 0;
}

int my_strchr(char *str, char ch) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            return 1;
        }
    }
    return 0;
}
char *random_generator() {
    char number;
    time_t my_time;
    char *random_combination = malloc(sizeof(char) * 5); // O'zgaruvchini `random_combination` deb o'zgartirildi
    srand(time(&my_time));
    for (int i = 0; i < 4;) {
        number = rand() % 9 + '0'; // 48 o'rniga '0' qo'shildi
        if (!my_strchr(random_combination, number)) {
            random_combination[i++] = number;
        }
    }
    random_combination[4] = '\0'; // O'zgaruvchini nomi `random_combination` deb o'zgartirildi
    return random_combination;
}
char *my_scanf() {
    char ch;
    char *input_code = malloc(sizeof(char) * 6); // O'zgaruvchini nomi `input_code` deb o'zgartirildi, hajmi 6 ga o'zgartirildi
    int i = 0;
    write(1, ">", 1);
    while (read(0, &ch, 1)) {
        if (ch == '\n') {
            input_code[i] = '\0';
            return input_code;
        } else if (i < 4) {
            input_code[i++] = ch;
        }
    }
    return "stop";
}
int find_error(char *input) {
    if (my_strlen(input) != 4) {
        printf("Wrong input!\n");
        return 1;
    }
    for (int i = 0; input[i]; i++) {
        if ((input[i] < '0' || input[i] > '8')) { // 56 o'rniga '8' qo'shildi
            printf("Wrong input!\n");
            return 1;
        }
        for (int j = i + 1; input[j]; j++) {
            if (input[i] == input[j]) {
                printf("Wrong input!\n");
                return 1;
            }
        }
    }
    return 0;
}
int analysis_password(char *secret_code, char *input) { // Funksiya nomi o'zgartirildi
    int well_placed = 0;
    int misplaced = 0;
    for (int i = 0; i < 4; i++) {
        if (secret_code[i] == input[i]) {
            well_placed++;
        }
        for (int j = 0; j < 4; j++) {
            if (secret_code[i] == input[j] && i != j) {
                misplaced++;
            }
        }
    }
    if (well_placed == 4) {
        return 2;
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
    return 0;
}
void game_interface(char *secret_code, int attempts) { // Funksiya nomi o'zgartirildi
    int i = 0, j = 0;
    char *input;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (i < attempts) {
        if (j == 0)
            printf("---\nRound %d\n", i);
        if (my_strcmp(input = my_scanf(), "stop") == 0)
            return;
        j = find_error(input);
        if (j == 0) {
            j = analysis_password(secret_code, input); // Funksiya nomi o'zgartirildi
            if (j == 2) {
                printf("Congratz! You did it!\n");
                return;
            }
            i++;
        }
    }
}
void option(int argc, char **argv) {
    char *secret_code = random_generator(); 
    int attempts = 10;
    for (int i = 1; i < argc; i++) {
        if (my_strcmp(argv[i], "-c") == 0) {
            free(secret_code); 
            secret_code = argv[i + 1];
        } else if (my_strcmp(argv[i], "-t") == 0) {
            attempts = atoi(argv[i + 1]);
        }
    }
      game_interface(secret_code, attempts);
}
int main(int argc, char **argv) {
    option(argc, argv);
    return 0;
}