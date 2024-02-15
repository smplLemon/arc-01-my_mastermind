#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *generate_random_code(){
    srand(time(NULL));
    char* code=(char *)malloc(sizeof(char)*5);
    for(int i=0;i<4;i++){
        code[i]=rand()%9+'0';
        for(int j=0;j<i;j++){
            if(code[i]==code[j]){
                i--;
                break;
            }
        }
    }
    code[4]='\0';
    return code;
}

int count_missed(char *code, char *input){
    int missed = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4 ; j++){
            if(input[i] == code[j] && i != j) missed++;
        }
    }
    return missed;
}

int count_well(char *code, char *input){
    int well = 0;
    for(int i = 0; i < 4; i++){
        if(code[i] == input[i]) well++;
    }
    return well;
}

int WRONG_input(char *input){
    if(strlen(input) != 4){
        write(1,"Wrong input!\n",13);
        return 1;
    } 
    for(int i = 0; i < 4; i++){
        if(input[i] < '0' || input[i] > '8'){
            write(1,"Wrong input!\n",13);
            return 1;
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = i+1; j < 4; j++){
            if(input[i] == input[j]){
                write(1,"Wrong input!\n",13);
                return 1;
            }
        }
    }
    return 0;
} 

int get_input(char *input){
    char c=0;
    int j=0;
    int flag=1;
    do{
        write(1,">",1);
        j=0;
        while((flag=read(0,&c,1))>0){
            if(c=='\n'){
                input[j]='\0';
                break;
            }
            input[j]=c;
            j++;
        }
        if(flag==0)
            return 0;
    }
    while(WRONG_input(input));  
    return 1;
}

void play_game(int attempts, char *code){
    char input[15]={0};
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    for(int i=0; i<attempts;i++){
        printf("---\nRound %d\n",i);
        if(!get_input(input))
            return;
        int well = count_well(code, input);
        int miss = count_missed(code, input);
        if(well == 4){
            printf("Congrats! You did it!\n");
            return;
        }
        else{
            printf("Well place pieces: %d\n", well);
            printf("Missed place pieces: %d\n", miss);
        }
    }
}
void main_brain(int argc, char **argv){
    int attempts = 10;
    char *code = NULL;
    for(int i=0;i<argc;i++){
        if(strcmp(argv[i],"-t")==0){
            attempts=atoi(argv[i+1]);
        }
        if(strcmp(argv[i],"-c")==0){
            code=argv[i+1];
        }
    }
    if(code==NULL)
        code = generate_random_code();
         play_game(attempts, code);
}       
int main(int argc, char **argv){
    main_brain(argc, argv);
    return 0;
}