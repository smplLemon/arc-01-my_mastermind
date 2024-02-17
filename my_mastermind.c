#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "math.h" 
#include "stdlib.h"
#include "time.h"

int check_yn(char*str,char c){
    for(int i = 0; str[i] !='\0'; i++){
        if(str[i] == c){
            return 1;
        }
    }
    return 0;
}

char* my_rand_num(){
    srand(time(NULL));
    char c;
    char *ret_str = (char*)malloc(sizeof(char)*4);
    for(int i = 0; i < 4;){
        c = rand() % 9 +'0';
        if(check_yn(ret_str,c) == 0){
            ret_str[i++] = c;
        }
    }
    return ret_str;
}

char*my_scanf(){
    char* ret_str = (char*)malloc(sizeof(char) *25);
    char c;
    int i = 0,k;
    while((k =read(0,&c,1)) >= 0){
        if(k == 0) exit(0);
        if(c == '\n'){
            return ret_str;
        }else{
            ret_str[i] = c;
            i++;
        }
    }
    return ret_str;
}

int my_slen(char*str){
    int i = 0;
    for(; str[i] !='\0';){
        i++;
    }
    return i;
}

int is_tr(char*str){
    if(my_slen(str) != 4){
        return 1;
    }
    for(int i = 0 ; i < 4; i++){
        if(str[i] > '9' || str[i] < '0'){
            return 1;
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = i+1; j < 4; j++){
            if(str[i] == str[j]){
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char*argv[])
{
    char*secret_code;
    int flag = 0;
    int raundlar = 10;
    
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i],"-t") == 0){
          raundlar = atoi(argv[i+1]);   
        }
    }
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i],"-c") == 0){
            secret_code = argv[i+1];
            flag = 1;
        }
    }
    if(flag == 0){
        secret_code = my_rand_num();
    }
    
    int wp = 0, mp = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for(int r = 0; r < raundlar;r+=1){
        printf("---\nRound %d\n",r);
        while(1){
            write(0,">",1);
            char*g_code = my_scanf();
            if(strcmp(g_code,secret_code)==0){
                    printf("Congratz! You did it!");
                    return 0;
                }
                if(is_tr(g_code)==1){
                    printf("Wrong Input!\n");
                }else{
                    for(int kl = 0; kl < 4; kl++){
                        if(g_code[kl] == secret_code[kl]){
                            wp+=1;
                        }
                        if(check_yn(g_code,secret_code[kl]) && g_code[kl] != secret_code[kl]){
                            mp+=1;
                        }
                    }
                    printf("Well placed pieces: %d\nMisplaced pieces: %d\n",wp,mp);
                    wp-=wp,mp-=mp;
                    break;
            }
        }
    }
    return 0;
}
