#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind_h.h"
#include "master_h.h"
#define CD_LEN 4 

void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd){
    *well_plcd = 0;
    *misplcd = 0;
    int gues_hist[10] ={0};
    int secret_hist[10] ={0};

    for(int i = 0; i < CD_LEN; i++){
        if(gues[i] == scrt_cd[i]){
           (*well_plcd)++;
        } 
        else{
            gues_hist[gues[i] - '0']++;
            secret_hist[scrt_cd[i] - '0']++;
        }
    }
    for(int i = 0; i < 10; i++){
        if(secret_hist[i] < gues_hist[i]){
            *misplcd += secret_hist[i]; 
        } 
        else{
            *misplcd += gues_hist[i]; 
        }
    }
}

char* randit(char* rndm_cd){
    const char num[] = "012345678";
    for(int i = 0; i < CD_LEN; i++){
        rndm_cd[i] = num[rand() % 10];
    }
    rndm_cd[CD_LEN] = '\0';
    return rndm_cd;
}

int validation(char* inpt){
    if(strlen(inpt) != CD_LEN){
        printf("Wrong input!\n");
        return 0; 
    }
    int dig[10] = {0}; 

    for(int i = 0; i < CD_LEN; i++){
        if(inpt[i] < '0' || inpt[i] > '9' || inpt[i] == '9'){
            printf("Wrong input!\n");
            return 0; 
        }
        dig[inpt[i] - '0']++; 

        if(dig[inpt[i] - '0'] > 1){
            printf("Wrong input!\n");
            return 0; 
        }
    }
    return 1;
}
