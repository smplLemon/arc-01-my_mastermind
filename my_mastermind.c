#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int attempt_check(int att){
    if(att <= 0)
        return 0;
    return 1;
}

int my_strlen(char* p1){
    int i = 0;
    while(p1[i] != '\0')
        i++;
    return i;
}

int code_check(char* str){
    if(my_strlen(str) == 4 && (str[0] >= '0' && str[0] <= '8') && (str[1] >= '0' && str[1] <= '8') && (str[2] >= '0' && str[2] <= '8') && (str[3] >= '0' && str[3] <= '8') && (str[0] != str[1] && str[0] != str[2] && str[0] != str[3] && str[2] != str[1] && str[2] != str[3] && str[3] != str[1] && str[3] != str[2]))
        return 1;
    return 0;
}

int read_input(char* input){
    for(int i = 0; read(0, &input[i], 1); i++)
        if(input[i] == '\n'){
            input[i] = '\0';
            return 1;
        }
    return 0;
}

int wellmisplace(char* code, char* secret){
    int x = 0;
    int y = 0;
    for(int i = 0; i < 4; i++){
        if(code[i] == secret[i])
            x++;
        for(int j = 0; j < 4; j++)
            if(i != j && code[i] == secret[j])
                y++;
    }
    if(x != 4){
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", x, y);
        return 0;
    }
    printf("Congratz! You did it!\n");
    return 1;
}

char* random_code(char* code){
    srand(time(NULL));
    int num_arr[4];
    for(int i = 0; i < 4; i++)
        num_arr[i] = rand() % 9;
    while(num_arr[1] == num_arr[0] || num_arr[2] == num_arr[0] || num_arr[2] == num_arr[1] || num_arr[3] == num_arr[0] || num_arr[3] == num_arr[1] || num_arr[3] == num_arr[2])
        for(int i = 0; i < 4; i++)
            num_arr[i] = rand() % 9;
    for(int i = 0; i < 4; i++)
        code[i] = '0' + num_arr[i];
    code[4] = '\0';
    return code;
}

int err_param(){
    printf("Error! Parameters are incorrect.\n");
    return 1;
}

int param_check(int argc, char* argv[], int* attempts, char* secret){
    if(argc > 2){
        if(strcmp(argv[1], "-c") == 0){
            for(int i = 0; i < 4; i++)
                secret[i] = argv[2][i];
            if(argc >= 4 && strcmp((argv[3]), "-t") == 0)
                *attempts = atoi(argv[4]);
        }
        else if(strcmp((argv[1]), "-t") == 0){
            *attempts = atoi(argv[2]);
            if(argc >= 4 && strcmp(argv[3], "-c") == 0)
                for(int i = 0; i < 4; i++)
                   secret[i] = argv[4][i];
        }
        secret[4] = '\0';
    }
    if((argc != 1 && argc != 3 && argc != 5) || !code_check(secret) || !attempt_check(*attempts))
        return err_param();
    return 0;
}

void game(char* secret, int attempts, char* input){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for(int round = 0; round < attempts; round++){
        printf("---\nRound %d\n", round);
        write(1, ">", 1);
        if(!read_input(input))
            break;
        while(!code_check(input)){
            printf("Wrong input!\n");
            write(1, ">", 1);
            if(!read_input(input)){
                attempts = 0;
                break;
            }
        }
        if(round < attempts)
            if(wellmisplace(input, secret))
                break;
    }
}

int main(int argc, char* argv[]){
    int attempts = 10;
    char input[5];
    char secret[5];
    random_code(secret);
    if(param_check(argc, argv, &attempts, secret))
        return 1;
    game(secret, attempts, input);
    return 0;
}
