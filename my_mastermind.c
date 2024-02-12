#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SCRT_CODE(str) (my_strlen(str) == 4 && (str[0] >= '0' && str[0] <= '8') && (str[1] >= '0' && str[1] <= '8') && (str[2] >= '0' && str[2] <= '8') && (str[3] >= '0' && str[3] <= '8') && (str[0] != str[1] && str[0] != str[2] && str[0] != str[3] && str[2] != str[1] && str[2] != str[3] && str[3] != str[1] && str[3] != str[2]))

int attempt_checker(char** att, int num){
    for(int i = 0; att[num][i] != '\0'; i++)
        if(!(att[num][i] >= '0' && att[num][i] <= '9') || atoi(att[num]) <= 0)
            return 0;
    return 1;
}

int my_strlen(char* p1){
    int i = 0;
    while(p1[i] != '\0')
        i++;
    return i;
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
    else{
        printf("Congratz! You did it!\n");
        return 1;
    }
}

char* random_code(char* code){
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

int main(int argc, char* argv[]){
    if(argc == 2 || argc > 5 || argc == 4){
        printf("Error! Parameters are incorrect.\n");
        return 1;
    }
    srand(time(NULL));
    int round = 0;
    int attempts = 9;
    char input[5];
    char secret[5];
    random_code(secret);

    if(argc > 2){
        if(strcmp(argv[1], "-c") == 0){
            if(argc < 3 || !SCRT_CODE(argv[2])){
                printf("Error! Parameters are incorrect.\n");
                return 1;
            }
            for(int i = 0; i < 4; i++)
                secret[i] = argv[2][i];
            secret[4] = '\0';

            if(argc >= 4 && strcmp((argv[3]), "-t") == 0){
                if(argc < 5 || !attempt_checker(argv, 4)){
                    printf("Error! Parameters are incorrect.\n");
                    return 1;
                }
                attempts = atoi(argv[4]) - 1;
            }
        }
        else if(strcmp((argv[1]), "-t") == 0){
            if(argc < 3 || !attempt_checker(argv, 2)){
                printf("Error! Parameters are incorrect.\n");
                return 1;
            }
            attempts = atoi(argv[2]) - 1;

            if(argc >= 4 && strcmp(argv[3], "-c") == 0){
                if(argc < 5 || !SCRT_CODE(argv[4])){
                    printf("Error! Parameters are incorrect.\n");
                    return 1;
                }
                for(int i = 0; i < 4; i++)
                   secret[i] = argv[4][i];
                secret[4] = '\0';
            }
        }
    }
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while(round <= attempts){
        printf("---\nRound %d\n>", round);
        char c;
        int i = 0;
        while(read(0, &c, 1) && c != '\n'){
            input[i] = c;
            i++;
        }   input[i] = '\0';
        if(!SCRT_CODE(input))
            while(!SCRT_CODE(input)){
                printf("Wrong input!\n>");
                int i = 0;
                while(read(0, &c, 1) && c != '\n'){
                    input[i] = c;
                    i++;
                }   input[i] = '\0';
            }
        if(wellmisplace(input, secret)){
            return 0;
        } round++;
    }
    return 0;
}