#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_mastermind.h"


int main(int argc, char **argv)
{
    char *code = NULL;
    int attempts = 10;
    time_t t;

    for (int i = 1; i < argc; i++)
    {
        if (my_strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            code = argv[i + 1];
        }
        else if (my_strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            attempts = atoi(argv[i + 1]);
        }
    }
    if (code == NULL)
    {
        srand((unsigned)time(&t));
        int random_number = 0;
        char temp[5];
        for (int i = 0; i < 4; i++)
        {
            random_number = rand() % 9 + 1;
            temp[i] = random_number + '0';
        }
        temp[4] = '\0';
        code = temp;
    }
    engine_mastermind(code, attempts);

    return 0;
}
