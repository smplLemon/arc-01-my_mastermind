#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "my_mastermind.h"

int main(int argc, char* argv[]) {
    char* secret_code;
    int flag = 0;
    int rounds = 10;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            rounds = atoi(argv[i + 1]);
        }
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            secret_code = argv[i + 1];
            flag = 1;
        }
    }

    if (flag == 0) {
        secret_code = my_rand_num();
    }

    int wp = 0, mp = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (int r = 0; r < rounds; r++) {
        printf("---\nRound %d\n", r);
        while (1) {
            write(0, ">", 1);
            char* g_code = my_scanf();
            if (strcmp(g_code, secret_code) == 0) {
                printf("Congrats! You did it!\n");
                return 0;
            }
            if (is_tr(g_code) == 1) {
                printf("Wrong Input!\n");
            } else {
                for (int kl = 0; kl < 4; kl++) {
                    if (g_code[kl] == secret_code[kl]) {
                        wp += 1;
                    }
                    if (check_yn(g_code, secret_code[kl]) && g_code[kl] != secret_code[kl]) {
                        mp += 1;
                    }
                }
                printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wp, mp);
                wp -= wp, mp -= mp;
                break;
            }
        }
    }
    return 0;
}
