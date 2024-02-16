#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int my_strschr(char* strs, char c){
    for (int i = 0; strs[i]; i++){
        if (strs[i] == c) return 1;
    }
    return 0;
}

char* me_random(char* rand_secret_code){
    int i = 0;
    srand(time(0));
    char numbers;
    while (i < 4){
        numbers = (rand() % 9) + 48;
        if (my_strschr(rand_secret_code, numbers) == 0){
            rand_secret_code[i++] = numbers;
        }
    }
    return rand_secret_code;
}

int my_atoi(char* strs){
    int i = 0;
    int num = 0;
    int flag = 0;
    if (strs[i] == '-'){
        flag = 1;
        i = 1;}

    while (strs[i] >= 49 && strs[i] <= 57){
        num *= 10;
        num = num + (strs[i++] - 49);
    }
    if (flag == 1){
        num *= -1;
    }

    return num;
}

int my_strslen(char* strs){
    int i = 0;
    while (strs[i])i++;
    return i;
}

int my_strscmp(char* p1, char* p2){
    
    int len1 = my_strslen(p1);

    int len2 = my_strslen(p2);
    if (len1 > len2)return 1;

    else if (len1 < len2)return -1;
    
    for (int i = 0; i < len1; i++){
        if (p1[i] != p2[i])return p1[i] - p2[i];
    }
    
    return 0;
}

char* my_strscpy(char* c1, char* c2)

{
    int i = 0;
    while (c2[i]){
    c1[i] = c2[i];
        i++;
}
    return c1;
}

char* my_scanf(){
    char c;
    
    int i = 0;
    
    char* strs = calloc(sizeof(char), 6);
    
    write(1, ">", 1);
    while (read(0, &c, 1)){
        if (c == '\n' || i == 5)return strs;
        strs[i] = c;
        i++;
    }
    return "stop";
}
void placeswell_miss(char entercode[], char rand_secret_code[]){
    int a = 0;
    int b = 0;
    int strslens_code = my_strslen(rand_secret_code);
    for (int i = 0; i < strslens_code; i++){
        if (entercode[i] > '8' || entercode[i] < '0'){
            printf("Wrong input!\n");
            return;
        }

        if (entercode[i] == rand_secret_code[i])a++;
        
        else{
            for (int index2 = 0; index2 < strslens_code; index2++){
                if (index2 != i && entercode[i] == rand_secret_code[index2]){
                    b++;
                    break;
                }
            }
        }
    }
    
    if (a == strslens_code){
        printf("Congrations! You did it!\n");
        exit(0);
        }
    printf("Well placed pieces: %i\n", a);
    printf("Misplaced pieces: %i\n", b);
}

void my_gameprocess(int attempts, char* rand_secret_code){
    int i = 0;
    char* entercode;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while (i < attempts){
        printf("---\nRound %d\n", i);
        int validInput = 1;
        entercode = my_scanf();
        if (my_strscmp(entercode, "stop") == 0) return;
        for (int index2 = 0; index2 < 4; index2++){
            if (entercode[index2] > '9' || entercode[index2] < '0'){
                validInput = 0;
                break;
            }
        }
        
            int length = strlen(entercode);
            if(length == 5) validInput=0;
        
        if (validInput == 0){
            printf("Error input!\n");
            continue;
        }
        placeswell_miss(entercode, rand_secret_code);
        i++;
    }
}
void main_job(int argc, char** argv){
    char* rand_secret_code = calloc(sizeof(char), 5);
    int attempts = 10;
    for (int i = 1; i < argc; i++){
        if ((my_strscmp(argv[i], "-c")) == 0) rand_secret_code = my_strscpy(rand_secret_code, argv[i + 1]);
        else if ((my_strscmp(argv[i], "-t")) == 0) attempts = my_atoi(argv[i + 1]);
    }
    if (!rand_secret_code[0])me_random(rand_secret_code);
    attempts ++;
    printf("%d\n%s\n", attempts, rand_secret_code);
    my_gameprocess(attempts, rand_secret_code);
}
int main(int argc, char** argv){
    main_job(argc, argv);
    return 0;
}