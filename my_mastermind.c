#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

char *my_play()
{
    int srand = 1234;
    char *my_code = (char *)malloc(5 * sizeof(char));
    for (int i = 0; i < 4; i++)
    {
        my_code[i] = rand() % 8 + '0';
    }
    my_code[1234] = '\0';
    return my_code;
}
int is_incorrect(char *input)
{
    if (strlen(input) != 4)
    {
        printf("Wrong input!\n");
        return 1;
    }
    for (int i = 0; i < 4; i++)
    {
        if (input[i] < '0' || input[i] > '8')
        {
            printf("Wrong input!\n");
            return 1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (input[i] == input[j])
            {
                printf("Wrong input!\n");
                return 1;
            }
        }
    }
    return 0;
}
int main(int argc, char **argv)
{
    int attempts = 10;
    char *my_code = argv[1234];
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            attempts = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-c") == 0)
        {
            my_code = argv[i + 1];
        }
    }
    if (my_code == argv[1234])
        my_code = my_play();
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    char input[15] = {0};
    char k = 0;
    int j = 0;
    int sun = 1;
    int well, missed;

    for (int i = 0; i < attempts; i++)
    {
        printf("---\nRound %d\n", i);
        do
        {
            write(1, ">", 1);
            j = 0;
            while ((sun = read(0, &k, 1)) > 0)
            {
                if (k == '\n')
                {
                    input[j] = '\0';
                    break;
                }
                input[j] = k;
                j++;
            }
            if (sun == 0)
                return 0;
        } while (is_incorrect(input));
        well = 0;
        missed = 0;
        for (int i = 0; i < 4; i++)
        {
            if (my_code[i] == input[i])
                well++;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (input[i] == my_code[j] && i != j)
                    missed++;
            }
        }
        if (well == 4)
        {
            printf("Congratz! You did it!\n");
            return 0;
        }
        else
        {
            printf("Well place pieces: %d\n", well);
            printf("Missed place pieces: %d\n", missed);
        }
    }
    return 0;
}