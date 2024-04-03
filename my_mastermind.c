#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int strln(char* str){
    int i = 0;
    while(*str){
        i++;
        str++;
    }
    return i;
}
int str_i(char* str, char n){
    for(int i = 0; str[i]; i++){
        if (str[i] == n) {
            return 1;
        }
    }
    return 0;
}

char* scan_f(){
    write(1, ">", 1);
    char c;
    char* str = malloc(sizeof(char)* 15);
    int i = 0;
    fflush(stdout);
    while(read(0, &c, 1)){
        if(c == EOF){
            return NULL;
        }
        if(c == '\n'){
            str[i] = '\0';
            return str;
        }
        str[i++] = c;
    }
    return NULL;
}

void rounds(int fl, int n){
    if(fl==0){
        printf("---\nRound %d\n", n);
    }
}

char* randm(){
    char* str = malloc(5);
    srand((unsigned) time(NULL));

    for(int i = 0; i < 4;){
        char s = (char)(rand() % 9 + 48);
        if(str_i(str, s) == 0){
            str[i++] = s;
        }
    }
    str[4] = '\0';
    return str;
}
int wlpp(char* str, char* str_t){
    int b = 0;
    for(int i = 0; str_t[i]; i++){
        if(str_t[i] == str[i]){
            b++;
        }
    }
    return b;
}

int mspp(char* str, char* str_t){
    int b = 0;
    for(int i = 0; str_t[i]; i++){
        for(int j = 0; str[j]; j++){
            if(str_t[i] == str[j] && i != j){
                b++;
            }
        }
    }
    return b;
}

int checking(char* cd, char* ip){
    int wpp = wlpp(cd, ip);
    if(wpp == 4){
        printf("Congratz! You did it!\n");
        return 1;
    }
    printf("Well placed pieces: %d\n", wpp);
    printf("Misplaced pieces: %d\n", mspp(cd, ip));
    return 0;
}

int wrong(char* str){
    int slen = strln(str);
    if(slen != 4){
        return 1;
    }
    for(int i = 0; str[i]; i++){
        if(!(str[i] < '9' && str[i] >= '0')){
            return 1;
        }
    }
    for(int i = 0; str[i]; i++){
        for(int j = 0; str[j]; j++){
            if(str[i] == str[j] && i != j){
                return 1;
            }
        }
    }
    return 0;
}

void s_game(char* code, char* input, int fl, int round){
    for(int i = 0; i < round; i++){
        rounds(fl, i);
        input = scan_f();
        if(input == NULL){
            return;
        }
        if(wrong(input) == 1){
            printf("Wrong input!\n");
            i--;
            fl = 1;
        } else{
            fl = 0;
            if(checking(code, input) == 1){
                return;
            }
        }
    }
}

int main(int argc, char** argv){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    char* code = randm();
    char* input = NULL;
    int ptr = 10;
    int flag = 0;
    for(int i = 1;  i < argc; i += 2){
        if(strcmp(argv[i], "-c") == 0){
            free(code);
            code = argv[i + 1];
        }else if(strcmp(argv[i], "-t") == 0){
            ptr = atoi(argv[i + 1]);
        }
    }
    s_game(code, input, flag, ptr);

}