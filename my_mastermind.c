#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int hasDuplicateDigits(char *str)
{
    int digitCount[10] = {0};

    for (int i = 0; i < 4; i++)
    {
        digitCount[str[i] - '0']++;
        if (digitCount[str[i] - '0'] > 1)
        {
            return 1;
        }
    }

    return 0;
}

int my_strchr(char *str, char c)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == c)
        {
            return 1;
        }
    }
    return 0;
}

char *my_rand(char *secret_code)
{
    int i = 0;
    srand(time(0));
    char valid_numbers;
    while (i < 4)
    {
        valid_numbers = (rand() % 9) + 48;
        if (my_strchr(secret_code, valid_numbers) == 0)
        {
            secret_code[i++] = valid_numbers;
        }
    }
    secret_code[i] = '\0';
    return secret_code;
}

int my_atoi(char *str)
{
    int i = 0;
    int num = 0;
    int flag = 0;
    if (str[i] == '-')
    {
        flag = 1;
        i = 1;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if (flag == 1)
        num *= -1;
    return num;
}

int my_strlen(char *str)
{
    int i = 0;
    while (str[i])
    {
        i++;
    }
    return i;
}

int my_strcmp(char *p1, char *p2)
{
    int len1 = my_strlen(p1);
    int len2 = my_strlen(p2);
    if (len1 > len2)
    {
        return 1;
    }
    else if (len1 < len2)
    {
        return -1;
    }
    for (int i = 0; i < len1; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

char *my_strcpy(char *c1, char *c2)
{
    int i = 0;
    while (c2[i])
    {
        c1[i] = c2[i];
        i++;
    }
    c1[i] = '\0';
    return c1;
}

char *my_scanf()
{
    char c;
    int i = 0;
    char *str = calloc(sizeof(char), 6);
    printf(">");
    while (scanf("%c", &c) != EOF)
    {
        if (c == '\n' || i == 5)
        {
            break;
        }
        str[i] = c;
        i++;
    }
    str[i] = '\0';

    if (i == 0)
    {
        free(str);
        return NULL;
    }

    if (my_strcmp(str, "stop") == 0)
    {
        free(str);
        return NULL;
    }

    return str;
}

void well_misPlaces(char *entercode, char *secret_code)
{
    int well = 0;
    int mis = 0;

    for (int i = 0; i < 4; i++)
    {
        if (entercode[i] == secret_code[i])
        {
            well++;
        }
        else if (my_strchr(secret_code, entercode[i]))
        {
            mis++;
        }
    }

    printf("Well placed pieces:%d\n Misplaced pieces: %d\n", well, mis);
}

void game_parametr(int attempts, char *secret_code)
{
    int i = 0;
    char *entercode = calloc(sizeof(char), 5);
    printf("Can you find the secret code?\nPlease enter a valid guess\n");

    while (i < attempts)
    {
        printf("---\nRound %d\n", i);
        int validGuess = 1;
        entercode = my_scanf();

        if (entercode == NULL)
        {
            free(entercode);
            return;
        }

        int entercodeLength = my_strlen(entercode);
        
        if (entercodeLength > 4)
        {
            printf("Wrong input!\n");
            free(entercode);
            entercode = calloc(sizeof(char), 5);
            continue;
        }
        
        for (int j = 0; j < 4; j++)
        {
            if (entercode[j] > '8' || entercode[j] < '0')
            {
                validGuess = 0;
                printf("Wrong Input.\n");
                break;
            }
        }

        if (validGuess == 1 && hasDuplicateDigits(entercode) == 0)
        {
            well_misPlaces(entercode, secret_code);
            if (my_strcmp(entercode, secret_code) == 0)
            {
                printf("Congratz! You did it!\n");
                free(entercode);
                return;
            }
            i++;
        }
        else if (validGuess == 1 && hasDuplicateDigits(entercode) == 1)
        {
            printf("Wrong input! \n");
        }
        free(entercode);
        entercode = calloc(sizeof(char), 5);
    }

    printf("Game Over \n");
    free(entercode);
}

int main(){
    int attempts = 10;
    char* secret_code = calloc(sizeof(char), 5);
    my_rand(secret_code);
    game_parametr(attempts, secret_code);
    free(secret_code);
    return 0;
}