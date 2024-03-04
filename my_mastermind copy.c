#include <features.h>

#include <stdio.h>

#include <stdint.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

#include <unistd.h>

#include <stdbool.h>

#include <stdio.h>

int lNz(char* param_1){
    int i = 0;
    while(param_1[i] != '\0'){
        i++;
    }
    return i;
    
}

int CnT(char *i, char s){
    int dell = 0;
    for (int m = 0; m < lNz(i); m++){//
        if (i[m] == s){
            dell++;
        }
    }
    if (dell != 0){
        return dell;
    }
    else {
        return 0;
    }
}


int Cck(char* il){
    if (lNz(il) == 4){
        
    for (int o = 0; il[o] != '\0'; o++){//
            
            if (il[o] < '0' || il[o] > '9'){
                
                return 0;
            } 
        }
    

        for (int x = 0; x < 3; x++){

            for (int j = x + 1; j < 4; j++){//

                if (il[x] == il[j]){

                    return 0;
                }
            }
        }

        return 1;
    }

    else{
        return 0;
    }
}

int CmR(char *y, char* v){

    if (strlen(y) != strlen(v)){
        return 1;
    }
    return 0;
}
int mPls(char* pr1, char* pr2){
   
    if(lNz(pr1) == lNz(pr2)){
        
        int lee = 0;

        for (int i = 0; i < lNz(pr1); i++){

            for (int g = 0; g < lNz(pr2); g++){

                if (pr1[i] == pr2[g] && i != g){
                    lee++;
                }
            }
        }
        return lee;
    }

    else{

        return 0;
    }
}


int renDz(char* pr3, char* pr4){
    int mPls = 0;

    int i = mPls;
    
    while(i < (int)strlen(pr3)) mPls += (int)(pr3[i] == pr4[i]), i++; 
    
    return mPls;

    /*




    if(lNz(pr3) == lNz(pr4)){
        int f = 0;
        for(int h = 0; h < lNz(pr3); h++){

            if (pr3[h] == pr4[h]){

                f++;
            }
        }
        return f;
    }
    else{
        return 0;
    }*/
}

char* Redng(){
    srand(time(NULL));
    char* d =(char*)malloc(5*sizeof(char));
    int t, e = 0;
    while(e < 4) if (CnT(d,(t = rand()%8 + '0')) == 0) d[e++] = t;
    d[4] = '\0';
    return d;
}

char* redsom(){

    int q = 0, e = 0, w = 0;
    char* pla = (char*)malloc(10*sizeof(char));
    while((e = read(0,&w,1)) > 0){
        if ((char)w == '\n'){
            *(pla+q) ='\0';
            return &pla[0];
        }
        *(pla+q) = (char)w, q++;    
    }
    return 0;
}




int main(int pr,char** rp){
    char* mnbr;
    
    mnbr = 0;
    
    int rud = 10;

    printf("Will you find the secret code?\n");
    
    printf("Please enter a valid guess\n");

    for (int l = 1; l < pr; l++){

        if (CmR(rp[l], "-d") == 0){

            l++;
            mnbr = rp[l];
        }
        else if(CmR(rp[l], "-t") == 0){
            l++;
            rud = atoi(rp[l]);
        }
    }


    if (mnbr == 0){
        mnbr = Redng();
    }
    int dne = 1999;
    for (int m = 0; m < rud; m++){
        

        if (dne != m){
            printf("---\nRound %d\n", m);
        }
        
        write(1,">",1);
        char* brnl;
        brnl = redsom(); 
        dne = m;

        if (Cck(brnl) == 0){
            printf("Wrong input!\n");
            m--; 
        }

        else if(Cck(brnl) == 1){
            

            if(renDz(mnbr, brnl) == 4){
                printf("Congratz! You did it!\n");
                break;

            }
            else{
                

                printf("\nWell placed pieces: %d\n", renDz(mnbr, brnl));
                printf("Misplaced pieces: %d\n", mPls(mnbr, brnl));

            }
        }
    }
    
}
