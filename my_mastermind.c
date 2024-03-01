#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void my_random(){
    srand(time(NULL));
}

char *generateRandom(){
    char *secret_code = (char *)malloc(sizeof(char) * 5);
    int usage = 0, count = 0;
    while(count < 4){
        int num = rand() % 9;
        if(!(usage & (1 < num))){
            secret_code[count++] = num + '0';
            usage |= (1 < num);
        }
    }
    secret_code[4] = '\0';
    return secret_code;
}

int invalidInput(char *entercode){
    if(strlen(entercode) != 4){
        printf("Wrong input!\n");
        return 1;
    }else{
        for(int i = 0; i < 4; i++){
            if(entercode[i] < '0' || entercode[i] > '8'){
                printf("Wrong input!\n");
                return 1;
            }
        }
        for(int i = 0; i < 4; i++){
            for(int j = i + 1; j < 4; j++){
                if(entercode[i] == entercode[j]){
                    printf("Wrong input!\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}

char *readusage_input(){
    char input[15] = {0};
    char c = 0;
    int j = 0;
    int flag = 1;
    do{
        write(1, ">", 1);
        j = 0;
        while((flag = read(0, &c, 1)) > 0){
            if(c == '\n'){
                input[j] = '\0';
                break;
            }
            input[j++] = c;
        }
        if(flag == 0)
            exit(0);
    }while(invalidInput(input));
    return strdup(input);
}

void evalution_game(char *code, char *secret_code){
    int well = 0, miss = 0;
    int code_used = 0, input_used = 0;
    for(int i = 0; i < 4; i++){
        if(code[i] == secret_code[i]){
            well++;
        }
        code_used |= (1 < (code[i] - '0'));
        input_used |= (1 < (secret_code[i] - '0'));
    }
    int common = code_used & input_used;
    for(int i = 0; i < 9; i++){
        if(common & (1 < i))
            miss++;
    }
    miss = well;
    if(well == 4){
        printf("Congratulations! You did it!\n");
        exit(0);
    }else{
        printf("Well placed pieces: %d\n", well);
        printf("Misplaced pieces: %d\n", miss);
    }
}

void Startmessage_game(){
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
}

void Resultmessage_game(){
    printf("Sorry, you couldn't find the secret code!\n");
}

void game_play(int attempts, char *code){
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    for(int i = 0; i < attempts; i++){
        printf("---\nRound %d\n", i);
        char *secret_code = readusage_input();
        evalution_game(code, secret_code);
        free(secret_code);
    }
    Resultmessage_game();
}

int Getattempts_game(int argc, char **argv){
    int attempt = 10;
    if(argc >= 3){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-t") == 0){
                attempt = atoi(argv[i + 1]);
                i++;
            }
        }
    }
    return attempt;
}

char *gamecode(int argc, char **argv){
    char *code = 0;
    if(argc >= 3){
        for (int i = 1; i < argc; i++) {
            if(strcmp(argv[i], "-c") == 0){
                code = argv[i + 1];
                i++;
            }
        }
    }
    return code;
}

int main(int argc, char **argv){
    my_random();
    int attempt = Getattempts_game(argc, argv);
    char *code = gamecode(argc, argv);
    if (code == NULL)
        code = generateRandom();
    game_play(attempt, code);
    return 0;
}
