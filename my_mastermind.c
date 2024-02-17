#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_DIGITS 4

void generate_secret(int secret[4])
{
    for (int i = 0; i < 4; i++)
    {
        secret[i] = rand() % 10;
    }
}

void set_secret(int secret[4], int input)
{
    for (int i = 3; i >= 0; i--)
    {
        secret[i] = input % 10;
        input /= 10;
    }
}

int get_user_guess(int guess[4])
{
    char buffer[MAX_DIGITS + 2];
    ssize_t len = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    if (len <= 0)
    {
        return -1;
    }
    buffer[len] = '\0';
    int input = atoi(buffer);
    if (input < 1000 || input > 9999 || (input % 1111 == 0))
    {
        return 0;
    }
    for (int i = 3; i >= 0; i--)
    {
        guess[i] = input % 10;
        input /= 10;
    }
    return 1;
}

void give_feedback(int secret[4], int guess[4], int *black, int *white)
{
    *black = 0, *white = 0;
    for (int i = 0; i < 4; i++)
    {
        if (secret[i] == guess[i])
        {
            (*black)++;
        }
        else
        {
            for (int j = 0; j < 4; j++)
            {
                if (secret[i] == guess[j])
                {
                    (*white)++;
                    break;
                }
            }
        }
    }
    printf("Well placed: %d\n", *black);
    printf("Miss placed: %d\n", *white);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int secret[4], guess[4], black, white;
    if (argc == 3 && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-t") == 0))
    {
        int input = atoi(argv[2]);
        if (input < 1000 || input > 9999)
        {
            return 1;
        }
        set_secret(secret, input);
    }
    else
    {
        generate_secret(secret);
    }
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    for (int attempts = 0; attempts < 10; attempts++)
    {
        printf("---\nRound: %d\n>", attempts);
        int ret = get_user_guess(guess);
        if (ret == -1)
        {
            return 0;
        }
        else if (ret == 0)
        {
            printf("Wrong input!\n");
            attempts--;
            continue;
        }

        give_feedback(secret, guess, &black, &white);
        if (black == 4)
        {
            printf("Congratz! You did it!\n");
            break;
        }
    }

    printf("\nThe secret code was: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d", secret[i]);
    }
    printf("\n");
    return 0;
}
