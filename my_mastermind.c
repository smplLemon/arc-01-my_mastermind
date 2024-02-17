#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int check_character(char *str1, char c){
    int i = 0;
    while (str1[i]){
        if (str1[i] == c){
            return 1;
        }
        i++;
    }
    return 0;
}

char *my_random(){
    char *Secredcode = malloc((4 + 1) * sizeof(char));
    char c;
    srand(time(NULL));
    int i = 0;
    while (i < 4){
        c = (rand() % 9) + 48;
        if ((check_character(Secredcode, c)) == 0){
            Secredcode[i] = c;
            i++;
        }
    }
    return Secredcode;
}

char *my_scanf(){
    char *guescode = calloc(sizeof(char), 6);
    char c;
    int i = 0;
    printf(">");
    fflush(stdout);
    while (read(0, &c, 1)){
        if (c == '\n' || 4 < i){
            return guescode;
        }
        guescode[i++] = c;
    }
    return "EOT";
}

int repetation_check(char *guescode){
    int i = 0;
    for (i = 0; i < 3; i++){
        for (int j = i + 1; j < 4; j++){
            if (guescode[i] == guescode[j]){
                return 0;
            }
        }
    }
    return 1;
}

int wrong_input_check(char *guescode){
    int len = strlen(guescode);
    if (len != 4){
        return 0;
    }
    int i = 0;
    while (i < 4){
        if (guescode[i] < 48 || guescode[i] > 56)
        {
            return 0;
        }
        i++;
    }
    return repetation_check(guescode);
}

void mis_pl_well_pl_checker(char *secret_code, char *player_code){
    int mis_pl = 0, well_pl = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (secret_code[i] == player_code[i]){
                well_pl++;
                break;
            }
            else if (secret_code[i] == player_code[j]){
                mis_pl++;
                break;
            }
        }
    }
    if (well_pl == 4){
        printf("Congratz! You did it!\n");
        exit(0);
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_pl, mis_pl);
}

void my_mastermind2(int attemp, char *secredcode){
    int j = 9;
    int ok = 10;
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\nRound 0\n");
    char *guescode;
    while (attemp > 0)
    {
        guescode = my_scanf();
        if (strcmp(guescode, "EOT") == 0)
        {
            break;
        }

        while ((wrong_input_check(guescode)) == 0)
        {
            printf("wrong input\n");
            guescode = my_scanf();
        }
        mis_pl_well_pl_checker(secredcode, guescode);
        printf("---\nRound %d\n", ok - j);
        attemp--;
        j--;
    }
}

void check(int rounds, char *secret_code){
    int r = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\nRound %d\n", r++);
    for (int round = 1; round <= rounds; round++){
        char *playerGuess = my_scanf();
        if (strcmp(playerGuess, "EOT") == 0){
            break;
        }
        else if (wrong_input_check(playerGuess)){
            if (!(strcmp(secret_code, playerGuess) == 0)){
                mis_pl_well_pl_checker(secret_code, playerGuess);
                if (r != rounds){
                    printf("---\nRound %d\n", r++);
                }
            }
            else{
                printf("Congratz! You did it!\n");
                exit(0);
            }
        }
        else{
            printf("Wrong input!\n");
            round--;
        } free(playerGuess);
    }
}

void all(int argc, char **argv){
    int attemp = 10, i = 0;
    char *SecretCode = calloc(sizeof(char), 5);

    while (i < argc)
    {
        if ((strcmp(argv[i], "-c")) == 0)
        {
            SecretCode = strcpy(SecretCode, argv[i + 1]);
        }
        else if ((strcmp(argv[i], "-t")) == 0)
        {
            attemp = atoi(argv[i + 1]);
        }
        i++;
    }
    if (SecretCode[0] == 0)
    {
        SecretCode = my_random();
    }
    check(attemp, SecretCode);
}

int main(int argc, char **argv){
    all(argc, argv);
    return 0;
}
