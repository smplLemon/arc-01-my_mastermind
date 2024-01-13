#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int my_strcmp(char *param_1, char *param_2)
{
    int i = 0;

    while (param_1[i] != '\0')
    {
        if (param_1[i] > param_2[i])
        {
            return 1;
        }
        else if (param_1[i] < param_2[i])
        {
            return -1;
        }
        ++i;
    }
    return 0;
}

int check_well_placed(char *buff, char *code)
{
    int placed = 0;

    for (int i = 0; i < 4; i++)
    {
        if (buff[i] == code[i])
        {
            placed++;
        }
    }

    return placed;
}

int check_buff(char *buff)
{
    int res = 0;

    for (int i = 0; i < 4; i++)
    {
        if (buff[i] >= 48 && buff[i] <= 57)
        {
            res = 0;
        }
        else
        {
            res = 1;
        }
    }

    return res;
}

int check_misplaced(char *buff, char *code)
{
    int counter = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((buff[i] == code[j]) && i != j)
            {
                counter++;
            }
        }
    }
    return counter;
}

void engine_mastermind(char *code, int attempts)
{
    char buff[5];

    printf("%s\n", "Will you find the secret code?");
    printf("%s\n", "Please enter a valid guess");
    for (int i = 0; i < attempts; i++)
    {
        printf("%s\n%s%d\n", "---", "Round ", i);
        int res = read(STDIN_FILENO, buff, 5);
        if (res == 0)
        {
            break;
        }
        if (res == 5 && check_buff(buff) == 0)
        {
            int well_placed = check_well_placed(buff, code);
            int misplaced = check_misplaced(buff, code);
            if (well_placed < 4)
            {
                printf("%s%d\n", "Well placed pieces: ", well_placed);
                printf("%s%d\n", "Misplaced pieces: ", misplaced);
            }
            else
            {
                printf("%s\n", "Congratz! You did it!");
                break;
            }
        }
        else
        {
            printf("%s\n", "Wrong input!");
        }
    }
}
