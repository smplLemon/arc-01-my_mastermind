#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int my_strlen(char* p1){
    int counter = 0;
    while(p1[counter]){
        counter++;
    }
    return counter;
}

int my_strcmp(char* p1, char* p2){
    int len_1 = my_strlen(p1);
    int len_2 = my_strlen(p2);
    if( len_1 != len_2){
        return 1;
    }for(int i = 0; i < len_1; i++){
        if(p1[i] != p2[i]){
            return 1;
        }
    }
    return 0;
}

char* my_strcpy(char* buffer, char*  str){
    for(int i = 0; str[i]; i++){
        buffer[i] = str[i];
    }
    return buffer;
}

int my_atoi(char* str){
    int num = 0, i = 0, flag = 0;
    if(str[0] == '-'){
        flag = 1;
        i = 1;
    }
    while(str[i]){
        num *= 10;
        num += (str[i++] -48); 
    }
    if(flag == 1){
        num *= -1;
    }
    return num;
}

int repetition_checker_and_num_checker(char* str){
    if((my_strlen(str)) != 4){
        return 1;
    }
    for(int i = 0; i < 4; i++){
        for(int j = i + 1; j < 4; j++){
            if(str[i] == str[j] || str[i] > 56 && str[i] < 48){
                return 1;
            }
        }
    }
    return 0;
}

int str_and_char_comparer(char* str, char c){
    for(int i = 0; str[i]; i++){
        if(str[i] == c){
            return 1;
        }
    }
    return 0;
}

char* my_random_num_generetor(char* secret_code){
    int i = 0, num = 4;
    time_t t1;
    char c;
    srand((unsigned) time(&t1));
    while(i < num){
        c = (rand() % 9) + 48;
        if((str_and_char_comparer(secret_code, c)) == 0){
            secret_code[i] = c;
            i++;
        }
    }
    return secret_code;
}

char* my_reader_function(char* code_of_player){
        char c = '>';
        write(1, &c, 1);
        for(int i = 0; i < 6; i++){
        read(0 , &c, 1);
        if(c == '\n'){
            return code_of_player;
        }
        else if(c == 4){
            return "stop";
        }
        else{
        code_of_player[i] = c;
        }
    }
    return code_of_player;
}

char* my_scanf(){
    char* player_code = calloc(sizeof(char), 6);
    player_code = my_reader_function(player_code);
    return player_code;
}

void  mis_pl_well_pl_checker(char* secret_code, char* player_code){
    int mis_pl = 0, well_pl = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(secret_code[i] == player_code[i]){
                well_pl += 1;
                break;
            }else if(secret_code[i] == player_code[j]){
                mis_pl +=1;
                break;
            }
        }
    }
    if(well_pl == 4){
        printf("Congratz! You did it!\n");
        exit(0);
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_pl, mis_pl);
}

void secondory_main_work(int attemps, char* secret_code){
    int i = 0;
    char* player_code;
    while( attemps > 0){
        printf("--- \nRound %d\n", i++);
        player_code = my_scanf();
        while(repetition_checker_and_num_checker(player_code) != 0){
            printf("wrong input\n");
            free(player_code);
         player_code = my_scanf();
        }
        mis_pl_well_pl_checker(secret_code, player_code);
        attemps -= 1;
    }
}

void main_work(int argc, char** argv){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    int attemps = 10;
    char* secret_code = calloc(sizeof(char), 6);
    for(int i = 1; i < argc; i++){
        if((my_strcmp(argv[i], "-c")) == 0){
            secret_code = my_strcpy(secret_code, argv[i+1]);
        }else if((my_strcmp(argv[i], "-t")) == 0){
            attemps = my_atoi(argv[i+1]);
        }
    }
    if(secret_code[0] == 0){
        secret_code = my_random_num_generetor(secret_code);
    }else if(repetition_checker_and_num_checker(secret_code) == 1){
        printf("Your secret code is unavailable, so that we generated a random secret code\n");
        secret_code = my_random_num_generetor(secret_code);
    }
    secondory_main_work(attemps, secret_code);
}

int main(int argc, char** argv){
    main_work(argc, argv);
    return 0;
}