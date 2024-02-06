#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define CODE_SIZE 4

//
int my_strlen(char *str)
{
    int len = 0;
    do
    {
        len++;
    } while (str[len]);
    return len;
}

int my_strcmp(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);

    if (len1 == len2)
    {
        for (int i = 0; i < len1; i++)
        {
            if (str1[i] == str2[i])
            {
                return 0;
            }
        }
        return 0;
    }

    if (len1 > len2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int isddigit(char *sam)
{
    int str_length = my_strlen(sam);
    // Calculating string length
    for (int k = 0; k < str_length; k++)
    {
        if (!(sam[k] >= '0' && sam[k] <= '9'))
            return 1;
    }
    return 0;
}

void toInt(int *code, char *str)
{
    int i;
    char num_str[2] = {0};
    for (i = 0; str[i] != '\0'; i++)
    {
        num_str[0] = str[i];
        code[i] = atoi(num_str);
    }
}

int *genSecretCode()
{
    int *code = malloc(CODE_SIZE * sizeof(int));
    int numbs_used[9] = {0};

    srand(time(NULL));

    for (int i = 0; i < CODE_SIZE; i++)
    {
        int Random_nums = rand() % 10;

        while (numbs_used[Random_nums] == 1)
        {
            Random_nums = rand() % 10;
        }
        code[i] = Random_nums;
        numbs_used[Random_nums] = 1;
    }
    return code;
}

void my_mastermind(int argc, char **argv)
{
    int *secret_code = malloc(CODE_SIZE * sizeof(char));
    int Max_Guess = 10, rounds = 0;
    int *guess = malloc(CODE_SIZE * sizeof(int));

    if (argc > 2)
    {
        if ((isddigit(argv[2]) != 0) || (my_strlen(argv[2]) != 4))
        {
            printf("Wrong input %s passed\n", argv[2]);
            secret_code = genSecretCode();
        }
        else
        {
            if (my_strcmp(argv[1], "-c") == 0)
            {

                toInt(secret_code, argv[2]);
            }
            else if (my_strcmp(argv[1], "-t") == 0)
            {
                Max_Guess = atoi(argv[2]);
                if (Max_Guess > 10)
                {
                    Max_Guess = 10;
                }
            }
        }
    }
    else
        secret_code = genSecretCode();
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    while (Max_Guess > 0)
    {
        printf("\nRound %d\n", rounds);
        rounds++;

        int properlyPlaced = 0, misplaced = 0;
        char *buffer = malloc(5 * sizeof(char));
        if (buffer == NULL)
        {
            printf("Memory Allocation failed!\n");
        }

        int n = read(0, buffer, 5);
        if (n <= 4)
        {
            Max_Guess--;
            printf("Wrong Input Passed !\n");
            break;
        }
        else
        {
            buffer[n] = '\0';
        }

        int numbs_guessed = atoi(buffer);
        if (numbs_guessed == 0)
        {
            printf("Wrong input passed.\n");
            Max_Guess--;
            break;
        }
        else
        {
            toInt(guess, buffer);
        }

        for (int i = 0; i < CODE_SIZE; i++)
        {
            if (secret_code[i] == guess[i])
                properlyPlaced++;
            else
            {
                for (int j = 0; j < CODE_SIZE; j++)
                {
                    if (secret_code[i] == guess[j] && i != j)
                    {
                        misplaced++;
                        break;
                    }
                }
            }
        }
        if (properlyPlaced == 4)
        {
            printf("Congratz! You did it!\n");
            break;
        }
        else
        {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", properlyPlaced, misplaced);
            Max_Guess--;
        }
        free(buffer);
    }
    free(secret_code);
    free(guess);
}

int main(int argc, char **argv)
{
    my_mastermind(argc, argv);
    return 0;
}