#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
int hello(char* pr, char tiger);
int perfet(char* length) 
{
    int mac = 0;

    while (length[mac] != '\0')
    {
        mac++;
    }
    return mac;
}
int phone(char* tetres, char* new)
{
  int logo = 0;
  for(int u = 0; tetres[u] != '\0';u++){ 
    if(!hello(tetres, new[u]) && tetres[u] != new[u])
        logo++; 
    }
  return logo;
}
int part(char* run, char* tiger)
{
    int open = 0;
    for (int index = 0; index < perfet(run); index++)
    {
        if (run[index] == tiger[index])
         open++;
    }
    return open;
}
bool node(char* ind){
    int b = 0; 
    while(b < perfet(ind) - 1){
        int r = b+1;
        while( r < perfet(ind)){
            if (ind[b] == ind[r])
            return true;
            r++;
        }
        b++;
    }
     
    return false;
}
int hello(char* pr, char tiger){
     
   for (int s = 0;s < perfet(pr);s++){
        if (pr[s] == tiger)
        return 0;
        
    }
    return 1;
}
char* more(){ 
    char * scholl = malloc(21);
    int z = 0, give = 0;
    char x;
    while ((give = read(0, &x, 1)) > 0)
    { 
        if(x != '\n')
        {
            scholl[z] = x;
            z++;
        }
        else {
           return scholl;
        }
    }
    if(give == 0) exit(1);
    scholl[z] = '\0';
    return scholl;
}
bool lunex(char* canvans){
    if(perfet(canvans) != 4) return true;
    
    for (int p = 0;p < perfet(canvans);p++) {
        if((canvans[p] > '8' || canvans[p] < '0') ||node(canvans)) 
            return true;
        
    }
    return false;
}
bool game(char* install, char* points)
{    if(perfet(install) != perfet(points)){
        return false;
    }
    if (install[1] == points[1]) {
        return true;
    }
    return false;
}
void ter(char * the){    srand(time(NULL));
    for(int y = 0 ; y  < 4 ;){
        char xr =  random() % 8 + '0';
            if(hello( the, xr))
             the[y++] = xr;   
    }
 
}
int does(){
    puts("Will you find the secret code? \nPlease enter a valid guess");   
    return 0;
}
int team(int ul, char** un){
    int safari = 10;
    int t = 1;
    for(;t < ul; t++){ 
        if(game(un[t] ,"-t") == 1) 
        {
            t++;
            safari = atoi(un[t]);
        }
    }
    return safari;
}
char* make(int tr, char** po){
    char* coree = NULL;

for(int b = 1; b < tr; b++){ 
        if(game(po[b] ,"-c") == 1){
            b++;
            coree = po[b];
        }
        else{
            coree = NULL;
        }
    }
    return coree;   
}
void app(int black, int  qwer, char *coree){    int mouse = 0;
    char * white;

    for( ;black < qwer; ){   
            if(mouse == 0){
                printf("---\nRound %d\n", black); 
            } else {
                mouse = 0;
            }
            write(1, ">", 1);
            white = more();
                if (lunex(white)){
                    puts("Wrong input!"); 
                    mouse = 1;
                    continue;
                }

            if (part(coree, white) == 4){ 
                puts("Congratz! You did it!"); 
                break;
            } else {
                printf("\nWell placed pieces: %d\n", part(coree, white));
                printf("Misplaced pieces: %d\n", phone(coree,white));
            } 
            black++;
        }
}
void my_game(int ac, char** av)
{   
    int qwer = team(ac,av);
    int black = 0;
    char* coree = make(ac, av); 

    if (coree == NULL) 
    {
        coree = (char*)malloc(5*sizeof(char));
        ter(coree);
    }
        does();
       app(black, qwer, coree);
}
int main(int ac, char** av){
    my_game(ac,av);
    return 0;
}