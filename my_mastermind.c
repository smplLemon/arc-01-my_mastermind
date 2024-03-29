#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "mastermind.h"

int main(int acc, char *arg[]){
    int trails = 10, accuratelyPlaced, inaccuratelyPlaced, counter = 0, cd_gused = 0;
    char cryptic_code[Len], *encoded = NULL, decryption[Len + 1];
    for(int i = 1; i < acc; i++){
        if(strcmp(arg[i], "-c") == 0 && i + 1 < acc){ encoded = arg[i + 1]; } 
        else if(strcmp(arg[i], "-t") == 0 && i + 1 < acc){ trails = atoi(arg[i + 1]); } }
    generateCod(cryptic_code, encoded);
    printf("Will you find the secret code? \n");
    printf("Please enter a valid numbers\n");
    while(trails > 0){
        printf("---\n");
        printf("Round %d\n", counter++);
        getDescryption(decryption);
        compareCod(cryptic_code, decryption, &accuratelyPlaced, &inaccuratelyPlaced);
        if(accuratelyPlaced == Len){
            printf("Congratz! You did it!\n");
            cd_gused = 1; 
            break; }
        printf("Well-placed pieces: %d\n", accuratelyPlaced);
        printf("Misplaced pieces: %d\n", inaccuratelyPlaced);
        trails--; }
    if(trails == 0 && !cd_gused){
        printf("Sorry, you couldn't find the secret code.\n"); }
    return 0; } 