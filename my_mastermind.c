#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

char *my_scanf(){
    char *data = calloc(32, sizeof(char));
    int i = 0;
    char c;
    write(1,">", 1);
    while (read(0, &c, 1)){
        // if (read(0, &c, 1) <= 0)
        // {
        //     free(data);
        //     return 0;
        // }
        if (c == '\n' || i > 4){
            // free(data);
            return data;
        }
        data[i++] = c;
    }
    return "EOT";
}

bool isDigit(char *c){
    for (int i = 0; i < 4; i++){
        if (c[i] < '0' || c[i] > '8')
            return false;
    }
    return true;
}

bool isFour(char *four){
    return strlen(four) == 4;
}

int valid_code(char *string){
    for (int i = 0; i < 4; i++){
        for (int j = i + 1; j < 4; j++){
            if (string[i] == string[j])
                return 0;
        }
    }
    return 1;
}

char *generateSecretCode(){
    char *secretCode = malloc((4 + 1) * sizeof(char));
    srand(time(NULL));
    for (int i = 0; i < 4; i++){
        char num;
        do{
            num = '0' + rand() % 9;
        } while (strchr(secretCode, num) != NULL);
        secretCode[i] = num;
    }
    secretCode[4] = '\0';
    return secretCode;
}

// char *my_scanf(){
//     char *guess = malloc((4 + 1) * sizeof(char));
//     printf("> ");
//     return my_scanf("%s", guess);
// }

void places(char *secret, char *guess){
    int wellPlaced = 0;
    int misplaced = 0;

    for (int i = 0; i < 4; i++){
        if (secret[i] == guess[i])
            wellPlaced++;
        else{
            for (int j = 0; j < 4; j++){
                if (i != j && secret[i] == guess[j]){
                    misplaced++;
                    break;
                }
            }
        }
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
}

void check(int rounds, char *secret_code){
    int r = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n---\nRound %d\n",r++);
    for (int round = 1; round <= rounds; round++){  
        char *playerGuess = my_scanf();
        // printf("r bu : %d\nround bu : %d\nrounds bu : %d\n", r, round, rounds);

        
        // printf("players code : %s\n", playerGuess);
        if (strcmp(playerGuess,"EOT") == 0){
            break;  
        }           
        else if (valid_code(playerGuess) && isDigit(playerGuess) && isFour(playerGuess)){
            // r++;
            bool check_bool = strcmp(secret_code, playerGuess) == 0;
            if (!check_bool){
                places(secret_code, playerGuess);
                if(r != rounds ){
                    printf("---\nRound %d\n",r++);
                }
            }else{
                printf("Congratz! You did it!\n");
                break;
            }
        }else{
            printf("Wrong input!\n");
            round--;
        }
        free(playerGuess);
    }
}

int all(int argc, char **argv){
    int rounds = 10;
    char *secret_code = generateSecretCode();
    for (int i = 1; i < argc; i++){
        if (!strcmp(argv[i], "-t")){
            if (!isDigit(argv[i + 1])){
                rounds = atoi(argv[i + 1]);
                // printf("%i attempts \n", rounds);
            }else{
                printf("Invalid code!\n");
                return 1;
            }
        }
        else if (!strcmp(argv[i], "-c")){
            if (isDigit(argv[i + 1]) && isFour(argv[i + 1])){
                free(secret_code);
                secret_code = strdup(argv[i + 1]);
            }else{
                printf("Invalid secret code!\n");
                return 1;
            }
        }
    }check(rounds, secret_code);
    free(secret_code);
    return 0;
}

int main(int argc, char **argv){
    all(argc, argv);
    return 0;
}
