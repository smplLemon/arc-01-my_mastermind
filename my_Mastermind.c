#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int my_strlen(char *string1)
{
    int length = 0;
    while (string1[length] != '\0')
    {
        length++;
    }
    return length;
}
int my_strcmp(char *string1, char *string2)
{
    int length1 = my_strlen(string1);
    int length2 = my_strlen(string2);
        if (length1 != length2)
        return 1;
    for (int i = 0; i < length1; i++)
    {
        if (string1[i] != string2[i])
        {
            return 1;
        }
    }
    return 0;
}
char *my_strcpy(char *param1, char *param2)
{
    int i = 0;
    while (param2[i])
    {
        param1[i] = param2[i];
        i++;
    }
    param1[i] = '\0';
    return param1;
}
int my_atoi(char *string1)
{
    int the_result = 0;
    for (int i = 0; string1[i]; i++)
    {
        the_result *= 10;
        the_result += (int)string1[i] - '0';
    }
    return the_result;
}
int check_mark(char *string1, char c)
{
    for (int i = 0;string1[i]; i++)
    {
        if (string1[i] == c)
        {
            return 1;
        }
    }
    return 0;
}
char *my_random_code()
{
    char *hidden_code = calloc(sizeof(char), 5);
    char n;
    time_t time1;
    srand((unsigned)time(&time1));
    int i = 0;
    while (i < 4)
    {
        n = (rand() % 9) + '0';
        if (check_mark(hidden_code, n) == 0)
        {
            hidden_code[i] = n;
            i++;
        }
    }
    return hidden_code;
}
char *my_scanf()
{
    char *approximate_code = calloc(sizeof(char), 6);
    char n;
    int i = 0;
    printf("→");
    
    fflush(stdout);
    while (read(0, &n, 1))
    {
        if (n == '\n')
        {
            break;
        }
        approximate_code[i++] = n;
    }
    return approximate_code;
}
int incorrect_input_checking(char *approximate_code)
{
    int length = my_strlen(approximate_code);
    if (length != 4)
    {
        return 0;
    }
    for (int i = 0; i < 4; i++)
    {
        if (approximate_code[i] < '0' || approximate_code[i] > '9')
        {
            return 0;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (approximate_code[i] == approximate_code[j])
            {
                return 0;
            }
        }
    }
    return 1;
}
void right_try_wrong_try(char *hiddenCode, char *guessCode)
{
    int wrong_try = 0, right_try = 0;
    for (int i = 0; i < 4; i++)
    {
        int found = 0;
        if (hiddenCode[i] == guessCode[i])
        {
            right_try++;
            found = 1;
        }
        else
        {
            for (int j = 0; j < 4; j++)
            {
                if (hiddenCode[i] == guessCode[j])
                {
                    wrong_try++;
                    found = 1;
                    break;
                }
            }
        }
        if (found)
        continue;
    }
    if (right_try == 4)
    {
        printf("Great, you did it! Keep it up!\n");
        exit(0);
    }
    printf("Correct guess: %d\nWrong guess: %d\n", right_try, wrong_try);
}
void my_game(int argc, char **argv)
{
    int j = 9; 
    int l = 10;
    int number_of_attempts = 10;
    char *hidden_code = NULL;
    for (int i = 0; i < argc; i++)
    {
        if (my_strcmp(argv[i], "-c") == 0)
        {
            hidden_code = (char *)malloc(sizeof(char) * 5);
            hidden_code = my_strcpy(hidden_code, argv[i + 1]);
        }
        else if (my_strcmp(argv[i], "-t") == 0)
        {
            number_of_attempts = my_atoi(argv[i + 1]);
        }
    }
        if (hidden_code == NULL)
    {
        hidden_code = my_random_code();
    }
        printf("► 0 - Round ◄\n<••••>\n");
        char *approximate_code;
    while (number_of_attempts > 0)
    {
        approximate_code = my_scanf();
        while ((incorrect_input_checking(approximate_code)) == 0)
        {
            printf("Error input\n");
            approximate_code = my_scanf();
        }
        right_try_wrong_try(hidden_code, approximate_code);
        if (number_of_attempts > 1) 
        {
            printf("<••••>\n► %d - Round ◄\n", l - j);
        }
        number_of_attempts--;
        j--;
    }
    free(hidden_code);
}
int main(int argc, char **argv)
{
    my_game(argc, argv);
    return 0;
}