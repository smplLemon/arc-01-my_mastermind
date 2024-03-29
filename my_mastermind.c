#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "custom_mastermind.h"

int main(int argument_count, char *arguments[]){
    char cryptic_code[LENGTH_NUMBER];
    char *encoded = NULL;
    int trials = 10;
    int accuratelyPlaced, inaccuratelyPlaced;
    char decryption[LENGTH_NUMBER + 1];
    int counter = 0;
    int cd_gused = 0; 

    for(int i = 1; i < argument_count; i++){
        if(strcmp(arguments[i], "-c") == 0 && i + 1 < argument_count){
            encoded = arguments[i + 1];
        } else if(strcmp(arguments[i], "-t") == 0 && i + 1 < argument_count){
            trials = atoi(arguments[i + 1]);
        }
    }
    generate_hidden_code(cryptic_code, encoded);

    printf("Will you find the secret code? \nPlease enter a valid numbers\n");
    while(trials > 0){
        printf("---\n");
        printf("Round %d\n", counter++);
        get_decryption(decryption);
        compare_codes(cryptic_code, decryption, &accuratelyPlaced, &inaccuratelyPlaced);
        if(accuratelyPlaced == LENGTH_NUMBER){
            printf("Congratz! You did it!\n");
            cd_gused = 1; 
            break;
        }
        printf("Well-placed pieces: %d\nMisplaced pieces: %d\n", accuratelyPlaced, inaccuratelyPlaced);
        trials--;
    }

    if(trials == 0 && !cd_gused){
        printf("Sorry, you couldn't find the secret code.\n");
    }
    return 0;
}
