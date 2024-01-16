#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char *my_strdup(char *str){
    int len = strlen(str);
    char *res = calloc((len + 1), sizeof(char));
    for (int i = 0; i < len; i++){
        res[i] = str[i];
    }
    return res;
}

char *my_cut(char *str){
    char *res = calloc(5, strlen(str));
    int c = 0;
    int len  = (strlen(str));
    for (int i = len - 4; i < len ; i++){
        res[c] = str[i];
        c++;
    }
    return res;
}

char *my_rand(){
    char *arr = calloc(5, sizeof(char));
    time_t t;
    int randedNum = 0;
    srand(time(&t));
    int i = 0;
    while (i < 4){
        randedNum = rand() % 9 + 48;
        if (strchr(arr, randedNum) != 0){
            continue;
        }
        arr[i++] = (char)randedNum;
    }
    return arr;
}

int Erorrs(char *mfu){
    int len = strlen(mfu);
    for (int i = 0; i < len; i++){
        if (!(mfu[i] > 47 && mfu[i] < 57) || (len < 4 || len > 4) || ( mfu[i] == mfu[i + 1])){
            printf("Wrong input!\n");
            return 1;
        }
    }
    return 0;
}

void my_itoa(int value, char* str) {
    sprintf(str, "%d", value);
}

int my_ict(char *str){
    char *result = calloc(3, sizeof(char));
    int len = (strlen(str) - 4);
    if (len < 1) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        result[i] = str[i];
    }
    return atoi(result);
}

char *my_read(){
    char *str = calloc(6, sizeof(char));
    char c;
    write(1, ">", 1);
    int i = 0;
    while (read(0, &c, 1)){
        if (i > 4 || c == '\n') {
            return str;
        }
        str[i++] = c;
    }
    return "EOT";
}

char *bg_main_func(int argc, char **argv){
    char *temp;
    char *res = malloc(sizeof(char) * 8);
    int attempt = 10, flag = 0;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0){
            temp = my_strdup(argv[i + 1]);
            flag = 1;
        }
        else if (strcmp(argv[i], "-t") == 0){
            attempt = atoi(argv[i + 1]);
        }
    }
    if (flag == 0) temp = my_rand();
    my_itoa(attempt, res);
    strcat(res, temp);
    return res;
}

void place(char *p1, char *p2){
    int c = 0;
    for (int i = 0; i < 4; i++){
        if (p1[i] == p2[i]){
            c++;
        }
    }
    printf("Well placed pieces: %d\n", c);
    c = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (!(p1[i] == p2[i]) && (p1[i] == p2[j])){
                c++;
            }
        }
    }
    printf("Misplaced pieces: %d\n", c);
}

int brain(int argc, char **argv){
    char *DATA = bg_main_func(argc, argv), *code = my_cut(DATA);
    int at = my_ict(DATA), i = 0;
    char *mfu = calloc(6, sizeof(char)); 
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (i < at) {
        printf("---\n");
        printf("Round %d\n", i);
        mfu = my_read();
        if (strcmp(mfu, "EOT") == 0)return 0;
        else if (Erorrs(mfu) == 1) continue;
        else if (strcmp(mfu, code) == 0){
            printf("Congratz! You did it!\n");
            return 0;
        }
        place(mfu, code);
        i++;
    }
    return 0;
}

int main(int argc, char **argv){
    brain(argc, argv);
    return 0;
}
