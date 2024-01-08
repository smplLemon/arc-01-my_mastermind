#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4

void my_guess(char* guess, char* secret_code, int* well_placed, int* misplaced)
{
    *well_placed = 0;
    *misplaced = 0;
    int guess_histogram[10] = {0};
    int secret_histogram[10] = {0};
    int i = 0;
   while ( i < CODE_LENGTH)
     
    {
        if (guess[i] == secret_code[i])
        {
            (*well_placed)++;
        }
        else
        {
            guess_histogram[guess[i] - '0']++;
            secret_histogram[secret_code[i] - '0']++;
        }
        i++;
    }

    for (int i = 0; i < 10; i++)
    {
        if (secret_histogram[i] < guess_histogram[i])
        {
            *misplaced += secret_histogram[i];
        }
        else
        {
            *misplaced += guess_histogram[i];
        }
    }
}

char* generate_random_code(char* random_code)
{
    const char numbers[] = "0123456789";

    for (int i = 0; i < CODE_LENGTH; i++)
    {
        random_code[i] = numbers[rand() % 10];
    }

    random_code[CODE_LENGTH] = '\0';

    return random_code;
}

int is_valid_input(char* input)
{
    if (strlen(input) != CODE_LENGTH)
    {
        return 0;
    }

    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (input[i] < '0' || input[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char** argv)
{
    char* secret_code = calloc(sizeof(char), CODE_LENGTH + 1);
    int max_attempts = 10;
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            strncpy(secret_code, argv[i + 1], CODE_LENGTH);
            secret_code[CODE_LENGTH] = '\0';
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            max_attempts = atoi(argv[i + 1]);
        }
        i++;
    }

    if (strlen(secret_code) == 0)
    {
        srand(time(NULL));
        generate_random_code(secret_code);
    }

    char user_guess[CODE_LENGTH + 1];
    int well_placed, misplaced;
    int rounds = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (rounds < max_attempts)
    {
        printf("---\nRound %d\n>", rounds);

        if (read(0, user_guess, CODE_LENGTH + 1) == -1)
        {
            printf("Error reading input.\n");
            return 1;
        }

        user_guess[CODE_LENGTH] = '\0';

        if (!is_valid_input(user_guess))
        {
            printf("Wrong input!\n");
            continue;
        }

        my_guess(user_guess, secret_code, &well_placed, &misplaced);

        if (well_placed == CODE_LENGTH)
        {
            printf("Congratz! You did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
        rounds++;
    }

    printf("---\nGame over. You didn't find the secret code.\n");

    return 0;
}