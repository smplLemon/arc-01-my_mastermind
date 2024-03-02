#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char *generate_code()
{
    srand(time(NULL));
    char *code = (char *)calloc(5, sizeof(char));

    for (int i = 0; i < 4; i++)
    {
        code[i] = '0' + rand() % 10;
    }

    return code;
}

int valid_input(char *guess)
{
    int length = 0;
    for (; guess[length] != '\0'; ++length);

    if (length != 4)
    {
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        if (guess[i] < '0' || guess[i] > '8')
        {
            return 0;
        }
        for (int j = i + 1; j < 4; j++)
        {
            if (guess[i] == guess[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

char *getin()
{
    write(1, ">", 1);
    char *guess = (char *)malloc(100 * sizeof(char));
    char c;
    int index = 0;
    int read_result;

    while ((read_result = read(0, &c, 1)) > 0 && c != '\n') {
        guess[index++] = c;
    }
    guess[index] = '\0';

    if (read_result == 0) {
        free(guess);
        exit(0);
    }

    while (!valid_input(guess))
    {
        printf("Wrong input!\n");
        write(1, ">", 1);
        index = 0;
        while ((read_result = read(0, &c, 1)) > 0 && c != '\n') {
            guess[index++] = c;
        }
        guess[index] = '\0';

        if (read_result == 0) {
            free(guess);
            exit(0);
        }
    }
    return guess;
}



void check_guess(char *code, char *guess, int *well_placed, int *misplaced)
{
    *well_placed = 0;
    *misplaced = 0;

    if (!valid_input(guess))
    {
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        if (code[i] == guess[i])
        {
            (*well_placed)++;
        }
        else
        {
            for (int j = 0; j < 4; j++)
            {
                if (i != j && code[j] == guess[i])
                {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
}

void arguments(int argc, char *argv[], char **code, int *attempts)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            *code = (char *)realloc(*code, 5 * sizeof(char));
            for (int j = 0; j < 4; j++)
            {
                (*code)[j] = argv[i + 1][j];
            }
            (*code)[4] = '\0';
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            *attempts = atoi(argv[i + 1]);
        }
    }
}

int main(int argc, char *argv[])
{
    char *code = NULL;
    int attempts = 10;

    arguments(argc, argv, &code, &attempts);

    if (code == NULL)
    {
        code = generate_code();
    }

    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    char *guess = NULL;
    for (int i = 0; i < attempts; i++)
    {
        printf("---\nRound %d\n", i);
        free(guess);
        guess = getin();

        int well_placed = 0;
        int misplaced = 0;
        check_guess(code, guess, &well_placed, &misplaced);

        if (well_placed == 4)
        {
            printf("Congratz! You did it!");
            free(code);
            free(guess);
            return 0;
        }
        else
        {
            printf("Well placed pieces: %d\n", well_placed);
            printf("Misplaced pieces: %d\n", misplaced);
        }
    }

    free(guess);
    free(code);
    return 0;
}
