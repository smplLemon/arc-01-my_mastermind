#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int my_strlen(char *str_1)
{
    int len = 0;
    while (str_1[len] != '\0')
    {
        len++;
    }
    return len;
}

int my_strcmp(char *str_1, char *str_2)
{
    int len_1 = my_strlen(str_1);
    int len_2 = my_strlen(str_2);
    if (len_1 != len_2)
        return 1;
    for (int i = 0; i < len_1; i++)
    {
        if (str_1[i] != str_2[i])
        {
            return 1;
        }
    }
    return 0;
}

char *my_strcpy(char *p1, char *p2)
{
    int i = 0;
    while (p2[i])
    {
        p1[i] = p2[i];
        i++;
    }
    return p1;
}

int my_atoi(char *str_1)
{
    int res = 0, i = 0;

    while (str_1[i])
    {
        res *= 10;
        res += (int)str_1[i] - 48;
        i++;
    }
    return res;
}

int check_character(char *str1, char c)
{
    int i = 0;
    while (str1[i])
    {
        if (str1[i] == c)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

char *my_random()
{
    char *Secredcode = calloc(sizeof(char), 5);
    char c;
    time_t t1;
    srand((unsigned)time(&t1));
    int i = 0;
    while (i < 4)
    {
        c = (rand() % 9) + 48;
        if ((check_character(Secredcode, c)) == 0)
        {
            Secredcode[i] = c;
            i++;
        }
    }
    return Secredcode;
}

char *my_scanf()
{
    char *guescode = calloc(sizeof(char), 6);
    char c;
    int i = 0;
    printf(">");
    fflush(stdout);
    while (read(0, &c, 1))
    {
        if (c == '\n')
            break;
        ;
        guescode[i++] = c;
    }
    return guescode;
}

int repetation_check(char *guescode)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (guescode[i] == guescode[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int wrong_input_check(char *guescode)
{
    int len = my_strlen(guescode);
    if (len != 4)
        return 0;
    int i = 0;
    while (i < 4)
    {
        if (guescode[i] < 48 || guescode[i] > 56)
        {
            return 0;
        }
        i++;
    }
    return repetation_check(guescode);
}

void mis_pl_well_pl_checker(char *secret_code, char *player_code)
{
    int mis_pl = 0, well_pl = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (secret_code[i] == player_code[i])
            {
                well_pl += 1;
                break;
            }
            else if (secret_code[i] == player_code[j])
            {
                mis_pl += 1;
                break;
            }
        }
    }
    if (well_pl == 4)
    {
        printf("Congratz! You did it!\n");
        exit(0);
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_pl, mis_pl);
}

void my_mastermind2(int attemp, char *secredcode)
{
    int j = 9;
    int i = 0;
    int ok = 10;
    printf("---\nRound 0\n");
    char *guescode;
    while (attemp > 0)
    {
        guescode = my_scanf();
        while ((wrong_input_check(guescode)) == 0)
        {
            printf("wrong input\n");
            guescode = my_scanf();
        }
        mis_pl_well_pl_checker(secredcode, guescode);
        printf("---\nRound %d\n", ok - j);
        attemp--;
        j--;
    }
}

void my_mastermind(int argc, char **argv)
{
    int attemp = 10, i = 0;
    char *SecretCode = calloc(sizeof(char), 5);

    while (i < argc)
    {
        if ((my_strcmp(argv[i], "-c")) == 0)
        {
            SecretCode = my_strcpy(SecretCode, argv[i + 1]);
        }
        else if ((my_strcmp(argv[i], "-t")) == 0)
        {
            attemp = my_atoi(argv[i + 1]);
        }
        i++;
    }
    if (SecretCode[0] == 0)
    {
        SecretCode = my_random();
    }
    my_mastermind2(attemp, SecretCode);
}

int main(int argc, char **argv)
{

    my_mastermind(argc, argv);
    return 0;
}  