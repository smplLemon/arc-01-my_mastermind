#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int new_strlen(char* input_checker){
    int i = 0;
    while (input_checker[i] != '\0'){
        i++;
    }
    return i;
}


char* new_strcpy(char* param_1, char* param_2)
{
    int i = 0;
    for (; param_1[i] != '\0'; i++) {
        param_1[i] = param_2[i];
    }
    return param_1;
}

int new_strchr(char* numbers, char num){
    for(int i = 0; numbers[i] != '\0'; i++){
        if(numbers[i] == num){
            return i;
        }
    }
    return -1;
}

int new_isdigit(char param_1){
    if(param_1 >= '0' && param_1 <= '8'){
        return 1;
    }
    return 0;
}

int new_bubble(char* input_checker){
    int last = new_strlen(input_checker);
    for(int i = 0; i < last-1; i++){
        for(int j = i+1; j < last; j++){
            if(input_checker[i] == input_checker[j]){
                return 1;
            }
        }
    }
    return 0;
}

int posting_scores(char* input_checker, char* anonym_num){
    int i = 0;
    int well = 0;
    int miss = 0;
    for(i = 0; input_checker[i] != '\0';i++){
        for (int j = 0;anonym_num[j] != '\0';j++) {
            if (input_checker[i] == anonym_num[j] && i != j ) {
                miss++;
            }
            else if (input_checker[i] == anonym_num[j]) {
                well++;
            }
        }
    }
    if(well == 4){
        printf("Congratz! You did it!\n");
        return 1;
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well,miss);
    return 0;
}

char* read_the_introduction(){
    int i = 0;
    char j;
    char* inclusion = malloc(6);
    write(1, ">", 1);
    while(read(0, &j, 1)){
        if(j == '\n'){
            inclusion[i] = '\0';
            return inclusion;
        }
        inclusion[i++] = j;
    }
    return "stop";
}

char* anonym_num_picker(){
    srand((unsigned) time(0));
    int i = 0;
    char* numbers = malloc(sizeof(char)* 5);
    numbers[4] = '\0';
    char num;
    while(i < 4){
        num = rand() % 9 + 48;
        if(new_strchr(numbers, num) == -1){
            numbers[i] = num;
            i++;
        }
    }
    return numbers;
}

int finder_wrong_or_not(char* input_checker){
    int len = new_strlen(input_checker);
    int i = 0;
    if((len != 4 ) || (new_bubble(input_checker) == 1)){
        printf("Wrong input!\n");
        return 1;
    }
    while(i < len){
        if((new_isdigit(input_checker[i]) == 0)){
            printf("Wrong input!\n");
            return 1;
        }
        i++;
    }
    return 0;
}

void starting_the_game(int round,char* anonym_num){
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    char* input_value;
    int flag = 0;
    int i = 0;
    while(i < round){
        printf("---\nRound %d\n", i);
        if(strcmp(input_value = read_the_introduction(), "stop") == 0) return;
        flag = finder_wrong_or_not(input_value);
        if(flag == 0){
            if(1 == posting_scores(input_value, anonym_num)){
                return;
            }
            i++;
        }
    }
}

void recipient(int argc,char** argv){
    int i = 1;
    int round = 10;
    char* anonym_num = anonym_num_picker();
    for (int j = 1; j < argc; j++) {
        if(strcmp(argv[i] ,"-c") == 0){
            anonym_num = argv[i + 1];
        }
        else if (strcmp(argv[i], "-t") == 0) {
            round = atoi(argv[i + 1]);
        }
        
    }
    starting_the_game(round, anonym_num);
}

int main(int argc, char** argv){
    recipient(argc, argv);
    return 0;
}