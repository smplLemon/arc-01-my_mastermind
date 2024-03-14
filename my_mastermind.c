#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int my_strlen(char* p1){
    int num = 0;
    int i = 0;
    while(p1[i]){
        {num++;}
        i++;
    }
    return num;
}

int my_strchr(char* p1, char p2)
{
    int i = 0;
    while(p1[i])
    {
        if(p1[i] == p2)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

char* my_rand()
{
    int i = 0;
    char x;
    time_t t;
    char* str = (char*)malloc(sizeof(char)* 4);

    srand(time(&t));

    while(i < 4)
    {
        x = rand() % 9 + 48;
        if(!my_strchr(str, x))
        {
            str[i] = x;
            i++;
        }
    }
    return str;
}

char* my_read(){
    write(1,">",1);
    fflush(stdout);
    char c;
    int x = 0;
    char* num_r = (char*)malloc(sizeof(char)* 4);
    while(read(0, &c, 1)){
        if(c == '\n'){
            return num_r;
        }
        num_r[x++] = c;
    }

    return "end";
}

int buble_str(char* p1){
    for(int i = 0; i < my_strlen(p1) - 1; i++){
        for(int j = i + 1; j < my_strlen(p1); j++){
            if(p1[i] == p1[j]){
                return 1;
            }
        }
    }
    return 0;
}

int between(char* p1){
    int i = 0;
    while(p1[i]){
        if(!(p1[i] >= 48 && p1[i] <= 56)){
            return 0;
        }
        i++;
    }
    return 1;
}

void title(int p1)
{
    if(p1 == 1){
        printf("Will you find the secret code?\nPlease enter a valid guess\n");
    }
    else if(p1 == 2){
        printf("Congratz! You did it!\n");
    }
    else if(p1 == 3){
        printf("---\n");
    }
    else if(p1 == 4){
        printf("Wrong input!\n");
    }
}

int inorder(char* p1, char* p2){
    int duble = 0;
    int i = 0;
    while(p1[i]){
        if(p1[i] == p2[i]) {duble++;}
        i++;
    }
    return duble;
}

int out_of_order(char* p1, char* p2){
    int duble = 0;
    for(int i = 0; p2[i]; i++){
        for(int j = 0; p1[j]; j++){
            if(p2[i] == p1[j] && i != j) duble++;
        }
    }
    return duble;
}

int out_put_print(char* p1, char* p2){
    if(inorder(p1, p2) == 4){
        return 0;
    }
    printf("Well placed pieces: %d\n", inorder(p1, p2));
    printf("Misplaced pieces: %d\n", out_of_order(p1, p2));
    title(3);
    return 1;
}

int str_analise(char* p1, char* p2){
    if(my_strlen(p1) != 4 || buble_str(p1) == 1 || between(p1) == 0){
        title(4);
        return 0;
    }
    if(out_put_print(p1, p2) == 0){
        title(2);
        return 2;
    }
    return 1;
}

void brain(int t, char* c){
    title(1);
    title(3);
    int i = 0;
    int x = 1;
    char* pasword;
    while(i < t){
        if(x == 1) printf("Round %d\n", i);
        if ( strcmp((pasword = my_read()) , "end") == 0){
            break;
        }
        x = str_analise(pasword, c);
        if(x == 1) i++;
        if(x == 2) break;
    }
}

void def_option(int ac,char** av)
{
    int p = 0;
    int chanece = 10;
    char* str = (char*)malloc(sizeof(char)* 4);
    if(av[1]){
        int i = 0;
        while(i < ac){
            if((strcmp(av[i],"-c")) == 0){
                str = av[i + 1];
                p++;
            }
            if((strcmp(av[i],"-t")) == 0){
                chanece = atoi(av[i + 1]);
            }
            i++;
        }
    }
    if(p == 0) str = my_rand();
    brain(chanece, str);
}

int main(int ac, char** av)
{
    def_option(ac, av);
    return 0;
}