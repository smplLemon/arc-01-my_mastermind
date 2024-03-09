#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define CODE_LENGTH 4
#define DEFAULT_ATTEMPTS 10

char *randomNumGenerator();
int valid_input_test(char *input);
    
int main (int argc, char **argv)
{
    int attempts = DEFAULT_ATTEMPTS;
    char *secret_code = NULL;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp (argv[i], "-t") == 0)
        {
            attempts = atoi (argv[i + 1]);
        }
        if (strcmp (argv[i], "-c") == 0)
        {
            secret_code = argv[i + 1];
        }
    }
    
    if (secret_code == NULL) 
    {
        secret_code = randomNumGenerator();
    }

    printf ("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[CODE_LENGTH + 1] = {0};
    char c = 0;
    int abort = 0, index;
    for (int i = 0; i < attempts; i++)
    {
        printf("---\nRound %d\n>",i);
        do{
            index = 0;
            while((abort = read(0, &c, 1)) > 0)
            {
                if (c == '\n')
                {
                    input[index] = '\0';
                    break;
                }
                input[index] = c;
                index++;
            }
           
            if (index == 0) 
            {
                return 0;
            }
        }
        while (valid_input_test(input));  
        int wellpieces = 0, mispieces = 0;
        for (int i = 0; i < CODE_LENGTH; i++)
        {
            if (secret_code[i] == input[i]) wellpieces++;
        }
        for(int i = 0; i < CODE_LENGTH; i++)
        {
            for (int j = 0; j < CODE_LENGTH; j++)
            {
                if (input[i] == secret_code[j] && i != j)
                {
                    mispieces++;
                }
            }
        }
        if(wellpieces == CODE_LENGTH)
        {
            printf("Congratz! You did it!\n");
            return 0;
        }
        else
        {
            printf("Well place pieces: %d\n", wellpieces);
            printf("Missed place pieces: %d\n", mispieces);
        }
    }
    printf("You were close. Better luck next time!");
    return 0;
}

char *randomNumGenerator()
{
    srand(time(NULL));
    char* secret_code = (char *)calloc(CODE_LENGTH + 1, sizeof(char));
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        secret_code[i] = rand() % 9 + '0';
        for (int j = 0; j < i; j++)
        {    
            if(secret_code[i] == secret_code[j])
            {
                i--;
            }
        }
    }
    secret_code[CODE_LENGTH]= '\0';
    return secret_code;

}

int valid_input_test(char *input)
{
    if (strlen(input) != CODE_LENGTH)
    {
        printf("Wrong input!\n");
        return 1;
    } 
    
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (input[i] < '0' || input[i] > '8'){
            printf("Wrong input!\n");
            return 1;
        }
    }
    
    for (int i = 0; i < CODE_LENGTH - 1; i++)
    {
        for (int j = i + 1; j < CODE_LENGTH; j++)
        {
            if (input[i] == input[j]){
                printf("Wrong input!\n");
                return 1;
            }
        }
    }
    return 0;
}