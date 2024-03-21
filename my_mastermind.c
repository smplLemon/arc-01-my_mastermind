#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define CODE_LENGTH 4
#define DEFAULT_ATTEMPTS 10

int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);
void process_arguments(int argc, char **argv, int *attempts, char **secret_code);
char* get_user_input();
void play_game(int attempts, char *secret_code);
void calculate_pieces(char *input, char *secret_code, int *wellpieces, int *mispieces);
char *randomNumGenerator();
int valid_input_test(char *input);

int main (int argc, char **argv)
{
    int attempts = DEFAULT_ATTEMPTS;
    char *secret_code = NULL;

    process_arguments(argc, argv, &attempts, &secret_code);
    play_game(attempts, secret_code);

    return 0;
}

void process_arguments(int argc, char **argv, int *attempts, char **secret_code)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp (argv[i], "-t") == 0)
        {
            *attempts = atoi (argv[i + 1]);
        }
        if (strcmp (argv[i], "-c") == 0)
        {
            *secret_code = argv[i + 1];
        }
    }
    
    if (*secret_code == NULL) 
    {
        *secret_code = randomNumGenerator();
    }
}

char* get_user_input()
{
    char *input = (char *)calloc(CODE_LENGTH + 1, sizeof(char));
    char c = 0;
    int abort = 0, index;

    do{
        index = 0;
        while((abort = read(0, &c, 1)) > 0 && index < CODE_LENGTH)
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
            free(input);
            return NULL;
        }
    }
    while (valid_input_test(input));  

    return input;
}

void play_game(int attempts, char *secret_code)
{
    printf ("Will you find the secret code?\nPlease enter a valid guess:\n");

    for (int i = 0; i < attempts; i++)
    {
        printf("---\nRound %d\n>",i);
        char *input = get_user_input();
        if(input == NULL)
        {
            return;
        }

        int wellpieces = 0, mispieces = 0;
        calculate_pieces(input, secret_code, &wellpieces, &mispieces);
        free(input);

        if(wellpieces == CODE_LENGTH)
        {
            printf("Congratz! You did it!\n");
            return;
        }
        else
        {
            printf("Well-placed pieces: %d\n", wellpieces);
            printf("Miss-placed pieces: %d\n", mispieces);
        }
    }
    printf("You were close. Better luck next time!");
}

void calculate_pieces(char *input, char *secret_code, int *wellpieces, int *mispieces)
{
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (secret_code[i] == input[i]) (*wellpieces)++;
    }
    for(int i = 0; i < CODE_LENGTH; i++)
    {
        for (int j = 0; j < CODE_LENGTH; j++)
        {
            if (input[i] == secret_code[j] && i != j)
            {
                (*mispieces)++;
            }
        }
    }
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

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

size_t strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s);
    return s - str;
}