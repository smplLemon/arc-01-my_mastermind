#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *my_random(int attempts){
    srand(time(NULL));
    char* code=(char *)malloc(sizeof(char)*5);
    int used[9] = {0};
    int count = 0;
    
    while(count < 4){
        int num = rand() % 9;
        if(used[num] == 0){
            code[count] = num + '0';
            used[num] = 1;
            count++;
        }
    }
    code[4]='\0';
    return code;
}

int is_incorrect(char *input){
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

int main(int argc, char **argv){
    int attempts = 10;
    char *code=NULL;
    
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i],"-t")==0){
            attempts=atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i],"-c")==0){
            code=argv[i+1];
            i++;
        }
    }
    
    if(code==NULL)code=my_random(attempts);
    
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15]={0};
    char c=0;
    int j=0;
    int flag=1;
    int well, missed;
    
    for(int i=0; i<attempts;i++){
        printf("---\nRound %d\n",i);
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
           
            if(flag==0) return 0;
        
        }
        while(is_incorrect(input));  
        
        well = 0;
        missed = 0;
        for(int i = 0; i < 4; i++){
            if(code[i] == input[i]) well++;
        }
        
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4 ; j++){
                if(input[i] == code[j] && i != j) missed++;
            }
        }
        
        if(well == 4){
            printf("Congratz! You did it!\n");
            return 0;
        }else{
            printf("Well place pieces: %d\n", well);
            printf("Missed place pieces: %d\n", missed);
        }
    }
    
    return 0;
}