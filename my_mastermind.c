#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int strleng(char* str){
    int i = 0;
    while(str[i++]);

    return i - 1;
}

void recpy(char* argc, char* argv){
    for(int i = 0; i < strleng(argv); i++){
        argc[i] = argv[i];
    }
}

int strchar(char* strb, char number){
    for(int i = 0; i < strleng(strb); i++){
        if(strb[i] == number) return 1;
    }
    return 0;
}


char* rgenerated(){
    char* rcode = calloc(5, sizeof(char));
    int i = 0;
    char temp;
    srand(time(0));


    while(i < 4){
        temp = rand() %9 +48;

        if(strchar(rcode, temp) == 0){
            rcode[i] = temp;
            i++;
        }
    }
    return rcode;
}

char* mainscanf(){
    char n = '>';
    write(1, &n, 1);
    fflush(stdout);
    char* input_u = calloc(100, sizeof(char));
    int i = 0;
    char temp;

    while(read(0, &temp, 1)){
        if(temp == '\n'){
            return input_u;
        }
        input_u[i] = temp;
        i++;
    }
    return NULL;
}

int gen_for_alp(char* input_u2){
    for(int i = 0; i < strleng(input_u2); i++){
        if(!(input_u2[i] >= 48 && input_u2[i] <= 56)) return 0;
    }

    return 1;
}

int gen_for_dupp(char* input_u){
    for(int i = 0; i < strleng(input_u); i++){
        for(int j = i+1; j <= strleng(input_u); j++){
            if(input_u[i] == input_u[j]) return 0;
        }
    }
    return 1;
}

int  b_placeded(char* sccs_code, char* user_code){
    int matter = 0;
    for(int i = 0; i < strleng(sccs_code); i++){
        if(sccs_code[i] == user_code[i]) matter++;
    }
    return matter;

}

int lost_placeded(char* sccs_code, char* user_code){
    int matter = 0;
    for(int i = 0; i <strleng(sccs_code); i++){
        for(int j = 0; j < strleng(user_code); j++){
            if(sccs_code[i] == user_code[j] && i != j) matter++;
        }
    }
    return matter;
}

int check_for_fun(char* input_u){
    if(strleng(input_u) != 4) return 0;
    if(gen_for_alp(input_u) == 0) return 0;
    if(gen_for_dupp(input_u) == 0) return 0;

    return 1;
}

void game_for_fun(int attemm, char* sccs_code){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    char* input_u;
    for(int i = 0; i < attemm; i++){
        printf("---\nRound %d\n", i);
        input_u = mainscanf();
    if(input_u == NULL) return;
    while (check_for_fun(input_u) == 0){
            free(input_u);
            printf("Wrong input!\n");
            input_u = mainscanf();}
int well = b_placeded(sccs_code, input_u);
        if(well == 4){
            free(input_u);
            printf("Congratz! You did it!\n");
            return;}
        else {
            printf("Well placed pieces: %d\n", well);
            printf("Misplaced pieces: %d\n", lost_placeded(sccs_code, input_u));}}}

int main(int argc, char** argv){
    int i = 0;
    char* sec_code = NULL;
    int attemm = 10;
    while(i < argc){
        if(strcmp(argv[i], "-c") == 0){
            i++;
            sec_code = malloc(sizeof(char) * 5);
            recpy(sec_code, argv[i]);}
        else if (strcmp(argv[i], "-t") == 0){
            i++;
            attemm = atoi(argv[i]);}
            i++;}
    if(sec_code == NULL){
        sec_code = rgenerated();}
    game_for_fun(attemm, sec_code);
    free(sec_code);
return 0;
}
