#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 4
#define MAX_ATTEMPTS 10

void generate_secret_code(int *code)
{
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        code[i] = rand() % 10;
    }
}

int get_user_input(int *input)
{
    char c;
    int i = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (c < '0' || c > '9')
        {
            while (c != '\n' && c != EOF)
            {
                c = getchar();
            }
            return -1;
        }
        if (i < SIZE)
        {
            input[i++] = c - '0';
        }
        else
        {
            while (c != '\n' && c != EOF)
            {
                c = getchar(); 
            }
            return -1;
        }
    }
    if (c == EOF)
    {
        return 0;
    }
    return 1;
}

int check_guess(int *guess, int *code)
{
    int correct_place = 0;
    int correct_number = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (guess[i] == code[i])
        {
            correct_place++;
        }
        else
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (guess[i] == code[j])
                {
                    correct_number++;
                    break;
                }
            }
        }
    }
    printf("Well placed pieces: %d\n", correct_place);
    printf("Misplaced pieces: %d\n", correct_number);
    return correct_place == SIZE;
}

int main(int argc, char *argv[])
{
    int secret_code[SIZE];
    int max_attempts = MAX_ATTEMPTS;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            char *code_str = argv[i + 1];
            for (int j = 0; j < SIZE && code_str[j] != '\0'; j++)
            {
                secret_code[j] = code_str[j] - '0';
            }
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            max_attempts = atoi(argv[i + 1]);
        }
    }

    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int attempt = 0; attempt < max_attempts; attempt++)
    {
        printf("--\nRound %d:\n>", attempt);
        int guess[SIZE] = {0};
        int result = get_user_input(guess);
        if (result == 0)
        {
            printf("Game over!\nYou ended the game.\n");
            return 0;
        }
        else if (result == -1)
        {
            printf("Wrong input!\nAt least 4 digits.\n");
            attempt--;
            continue;
        }
        if (check_guess(guess, secret_code))
        {
            printf("Congratz! You did it! The secret code was: ");
            for (int i = 0; i < SIZE; i++)
            {
                printf("%d", secret_code[i]);
            }
            printf("\n");
            return 0;
        }
    }

    printf("Game over!\nYou couldn't find the secret code.\nThe secret code was: ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d", secret_code[i]);
    }
    printf("\n");

    return 0;
}
