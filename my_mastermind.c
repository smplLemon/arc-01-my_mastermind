#include "my_mastermind.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "time.h"

char* my_rand_num() {
    srand(time(NULL));
    char c;
    char *ret_str = (char*)malloc(sizeof(char) * 5);
    for (int i = 0; i < 4;) {
        c = rand() % 9 + '0';
        if (check_yn(ret_str, c) == 0) {
            ret_str[i++] = c;
        }
    }
    return ret_str;
}

char* my_scanf() {
    char* ret_str = (char*)malloc(sizeof(char) * 25);
    char c;
    int i = 0, k;
    while ((k = read(0, &c, 1)) >= 0) {
        if (k == 0)
            exit(0);
        if (c == '\n') {
            return ret_str;
        } else {
            ret_str[i] = c;
            i++;
        }
    }
    return ret_str;
}

int my_slen(char* str) {
    int i = 0;
    for (; str[i] != '\0';) {
        i++;
    }
    return i;
}

int is_tr(char* str) {
    if (my_slen(str) != 4) {
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        if (str[i] > '9' || str[i] < '0') {
            return 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (str[i] == str[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int check_yn(char* str, char c) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            return 1;
        }
    }
    return 0;
}
