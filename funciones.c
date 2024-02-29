#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind_h.h"
#define CD_LEN 4

void guess(char* gues, char* scrt_cd, int* well_plcd, int* misplcd){
    *well_plcd = 0;
    *misplcd = 0;
    int gues_hist[10] ={0};
    int secret_hist[10] ={0};

    for(int i = 0; i < CD_LEN; i++){
        if(gues[i] == scrt_cd[i]){
           (*well_plcd)++;
        } else{
            gues_hist[gues[i] - '0']++;
            secret_hist[scrt_cd[i] - '0']++;
        }
    }
    for(int i = 0; i < 10; i++){
        if(secret_hist[i] < gues_hist[i]){
            *misplcd += secret_hist[i];
        } else{
            *misplcd += gues_hist[i];
        }
    }
}

char* randit(char* random_code){
    const char num[] = "0123456789";
    for(int i = 0; i < CD_LEN; i++){
        random_code[i] = num[rand() % 10];
    }
    random_code[CD_LEN] = '\0';
    return random_code;
}
int validation(char* input){
    if(strlen(input) != CD_LEN) return 0;
    for(int i = 0; i < CD_LEN; i++){
        if(input[i] < '0' || input[i] > '9') return 0;
    }
    return 1;
}
