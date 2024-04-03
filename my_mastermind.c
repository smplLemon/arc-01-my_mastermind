#include <stdio.h>
#include "./h/my_string.h"
#include <unistd.h>
#include <stdlib.h>

int uniq_check(char* str, char c) {
    for(int i = 0; str[i]; i++) {
        if(str[i] == c) {
            return 1;
        }
    }
    return 0;
}

int uniq(char* str) {
    int i, j;
    for(i=0; str[i]; i++) {
        for(j = 0; str[j]; j++) {
            if(i != j && str[i] == str[j]) {
                return 1;
            }
        }
    }
    return 0;
}

char* code_creat() {
    char* str = (char*)malloc(sizeof(char)*5);
    str[0] = '\0';
    str[1] = '\0';
    str[2] = '\0';
    str[3] = '\0';
    str[4] = '\0';
    char c;
    for(int i = 0; i < 4;) {
        c  = rand()%9+48;
        if(uniq_check(str, c) == 0) {
            str[i++] = c;
        }
    }
    return str;
}

char* input_code() {
    char* str = malloc(sizeof(char)*5);
    str[0] = '\0';
    str[1] = '\0';
    str[2] = '\0';
    str[3] = '\0';
    str[4] = '\0';
    int i = 0;
    char c; 
    while(read(0, &c, 1)) {
        if(c == '\n') {
            return str;
        }
        if(i < 5) {
            str[i++] = c;
        }
    }
    return "exit";
}

int well_miss(char* str1, char* str2) {
    int w = 0, m = 0;
    int i, j;
    for(i = 0; str1[i]; i++) {
        for(j = 0; str2[j]; j++) {
            if(str1[i] == str2[j] && i == j) {
                w++;
            }
            if(str1[i] == str2[j] && i != j) {
                m++;
            }
        }
    }
    if(w == 4)  {
        return 1;
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", w, m);
    return 0;
}   

int wrong_check(char* s_code, char* code) {
    while(1) {
        printf("Wrong input!\n");
        write(1, ">", 1);
        code = input_code();
        if(my_strcmp(code, "exit") == 0) {
            return 1;
        }
        if(my_strlen(code) == 4 && uniq(code) == 0 && my_isdigit(code) == 0) {
            if(well_miss(s_code, code) == 1) {
                printf("Congratz! You did it!\n");
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}

void start(char* s_code, int round) {
    printf("Will you find the secret code\nPlease enter a valid guess\n");
    char* code;
    for(int i = 0; i < round; i++) {
        printf("---\nRound %d\n", i);
        write(1, ">", 1);
        code = input_code();
        if(my_strcmp(code, "exit") == 0) return;
        if(my_strlen(code) == 4 && uniq(code) == 0 && my_isdigit(code) == 0) {
            if(well_miss(s_code, code) == 1) {
                printf("Congratz! You did it!\n");
                return;
            }
        }
        else {
            if(wrong_check(s_code, code) == 1) return;
        }
    }
    printf("secret_code: %s\nGame Over\n", s_code);
}

int main(int ac, char** av) {
    int round = 10;
    char* s_code = NULL;
    for(int i = 1; i < ac; i++) {
        if(my_strcmp(av[i], "-c") == 0) {
            s_code = (char*)malloc(sizeof(char)*(my_strlen(av[i+1])+1));
            s_code = my_strcpy(s_code, av[i+1]);
            s_code[my_strlen(av[i+1])] = '\0';
        }
        if(i >= ac) break;
        if(my_strcmp(av[i], "-t") == 0)  round = atoi(av[i+1]);
    }
    if(s_code == NULL) s_code = code_creat();
    start(s_code, round);
    return 0;
}
