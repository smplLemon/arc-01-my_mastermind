#include<stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *my_mastermind(){
    srand(time(NULL));
    char* code=(char *)malloc(sizeof(char)*5);
    for(int i=0;i<4;i++){
        code[i]=rand()%8+'0';
    for(int k=0;k<i;k++){    
        if(code[i]==code[k]){
            i--;
        }
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
    for(int i=0;i<argc;i++){  
        if(strcmp(argv[i],"-t")==0){
            attempts=atoi(argv[i+1]);
        }
        if(strcmp(argv[i],"-c")==0){
            code=argv[i+1];
        }
    }
    if(code==NULL)code=my_mastermind();
   printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15]={0};
    char s=0;
    int i=0;
    int num=1;
    int well, missed;
    for(int J=0; J<attempts;J++){
        printf("---\nRound %d\n",J);
        do{
            write(1,">",1);
            i=0;
            while((num=read(0,&s,1))>0){
                if(s=='\n'){
                    input[i]='\0';
                    break;
                }
                input[i]=s;
                i++;
            }
            if(num==0) return 0;
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