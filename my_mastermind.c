#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *random(){
    srand(time(NULL));
    char* letter=(char *)malloc(sizeof(char)*5);
    for(int i=0;i<4;i++){
        letter[i]=rand()%9+'0';
        for(int j=0;j<i;j++){    
            if(letter[i]==letter[j]){
                i--;
                break;
            }
        }
    }
    letter[4]='\0';
    return letter;
}

int wrong(char *input){
    if(strlen(input) != 4){
        printf("Wrong input!\n");
        return 1;
    } 
    
    for(int i = 0; i < 4; i++){
        if(input[i] < '0' || input[i] > '8'){
            printf("Wrong input!\n");
            return 1;
        }
    }
    
    for(int i = 0; i < 4; i++){
        for(int j = i+1; j < 4; j++){
            if(input[i] == input[j]){
                printf("Wrong input!\n");
                return 1;
            }
        }
    }
    
    return 0;
}

char *iinput(){
    char *input = (char *)malloc(sizeof(char) * 15);
    char a = 0;
    int b = 0;
    int d = 1;
    
    do{
        write(1,">",1);
        b=0;
        while((d=read(0,&a,1))>0){
            if(a=='\n'){
                input[b]='\0';
                break;
            }
            input[b]=a;
            b++;
            printf("%c",a);
        }

        if(d==0) return NULL;

    }
    while(wrong(input));  

    return input;
}

void stage(int p1, char *code){
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    
    
    for(int i = 0; i < p1; i++){
        printf("---\nRound %d\n", i);
        
        char *input = iinput();
        if(input == NULL) return;

       int good = 0;
       int assignment = 0;
        for(int i = 0; i < 4; i++){
            if(code[i] == input[i]) good++;
        }
        
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4 ; j++){
                if(input[i] == code[j] && i != j) assignment++;
            }
        }
        
        if(good == 4){
            printf("congratulations you made it!\n");
            return;
        }else{
            printf("Well place pieces: %d\n", good);
            printf("Missed place pieces: %d\n", assignment);
        }
    }
}

int main(int argc, char **argv){
    int apply = 10;
    char *code=NULL;
    for(int i=0; i<argc; i++){
        if(strcmp(argv[i],"-t")==0){
            apply=atoi(argv[i+1]);
        }
        if(strcmp(argv[i],"-c")==0){
            code=argv[i+1];
        }
    }
    
    if(code==NULL) code=random();
    
    stage(apply, code);

    return 0;
}