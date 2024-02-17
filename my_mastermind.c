    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <time.h>
   
    char *my_random(){
        srand(time(NULL));
        char* cood=(char *)malloc(sizeof(char)*5);
        for(int i=0;i<4;i++){
            cood[i]=rand()%9+'0';
        for(int j=0;j<i;j++){    
            if(cood[i]==cood[j]){
                i--;
            }
        }
        }
        cood[4]='\0';
        return cood;

    }
    int incorrect_input(char *put_up){
        if(strlen(put_up) != 4){
            printf("Wrong input!\n");
            return 1;
        } 
        
        for(int i = 0; i < 4; i++){
            if(put_up[i] < '0' || put_up[i] > '8'){
                printf("Wrong input!\n");
                return 1;
            }
        }
        
        for(int i = 0; i < 4; i++){
            for(int j = i+1; j < 4; j++){
                if(put_up[i] == put_up[j]){
                    printf("Wrong input!\n");
                    return 1;
                }
            }
        }
        
        return 0;
    }
    
    
    int main(int argc, char **argv){
        int attempts = 10;
        char *cood=NULL;
        char input[15]={0};
        char c=0;
        int j=0;
        int F_mag=1;
        int good;
        int unitized;
        good = 0;
        unitized = 0;
        for(int i=0;i<argc;i++){
            if(strcmp(argv[i],"-t")==0){
                attempts=atoi(argv[i+1]);
            }
            if(strcmp(argv[i],"-c")==0){
                cood=argv[i+1];
            }
        }
        
        if(cood==NULL)cood=my_random();
        printf("Will you find the secret code?\nPlease enter a valid guess:\n");
        for(int i=0; i<attempts;i++){
            printf("---\nRound %d\n",i);
            do{
                write(1,">",1);
                j=0;
                while((F_mag=read(0,&c,1))>0){
                    if(c=='\n'){
                        input[j]='\0';
                        break;
                    }
                    input[j]=c;
                    j++;
                }
            
                if(F_mag==0) return 0;
                
            
            }
            while(incorrect_input(input));  
            for(int i = 0; i < 4; i++){
                if(cood[i] == input[i]) good++;
            }
            
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4 ; j++){
                    if(input[i] == cood[j] && i != j) unitized++;
                }
            }
            
            if(good == 4){
                printf("Congratz! You did it!\n");
                return 0;
            }else{
                printf("Well place pieces: %d\n", good);
                printf("Missed place pieces: %d\n", unitized);
            }
        }
        
        return 0;
    }