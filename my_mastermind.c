#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *my_random() {
    static int ineger = 0;
    if (!ineger) {
        srand(time(NULL));
        ineger = 1;
    }

    char *code = (char *)malloc(sizeof(char) * 5);
    int user = 0;

    for (int cnt = 0; cnt < 4; cnt++)
    {
        int num = rand() % 9;
        if (!(user & (1 << num))) {
            code[cnt] = num + '0';
            user |= (1 << num);
            cnt++;
        }
    }
    


    code[4] = '\0';
    return code;
}

int is_dontcorrect(char *input) {
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

char *secret_code() {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }

    char *code = (char *)malloc(sizeof(char) * 5);
    int used = 0;

    for (int count = 0; count < 4; count++)
    {
        int num = rand() % 9;
        if (!(used & (1 << num))) {
            code[count] = num + '0';
            used |= (1 << num);
            count++;
        }
    }
    code[4] = '\0';
    return code;
}

void evguess(char *input, char *code) {
    int wells = 0;
    int missed = 0;
    int codes_used = 0, input_used = 0;
    for (int i = 0; i < 4; i++) {
        if (code[i] == input[i]) wells++;
        codes_used |= (1 << (code[i] - '0'));
        input_used |= (1 << (input[i] - '0'));
    }
    int common = codes_used & input_used;
    for (int i = 0; i < 9; i++) {
        if (common & (1 << i))
            missed++;
    }
    missed -= wells;

    if (wells == 4) {
        printf("Congratz! You did it!\n");
        exit(0);
    } else {
        printf("Well place pieces: %d\n", wells);
        printf("Missed place pieces: %d\n", missed);
    }
}

void playing_game(int attempts, char *code) {
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15] = {0};
    char c = 0;
    int j = 0;
    int flag = 1;
    for (int i = 0; i < attempts; i++) {
        printf("---\nRound %d\n", i);
        do {
            write(1, ">", 1);
            j = 0;
            while ((flag = read(0, &c, 1)) > 0) {
                if (c == '\n') {
                    input[j] = '\0';
                    break;
                }
                input[j] = c;
                j++;
            }
            if (flag == 0)
                exit(0);
        } while (is_dontcorrect(input));
        evguess(input, code);
    }
}

int main(int argc, char **argv) {
    int attempts;
    char *code;
    parse_arguments(argc, argv, &attempts, &code);
    if (code == NULL)
        code = secret_code();
    playing_game(attempts, code);
    return 0;
}