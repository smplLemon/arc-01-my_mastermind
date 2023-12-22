#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind.h"


char* generate_rm_code(char* random_code)
{
    const char numbers[] = "0123456789";

    int i = 0;
    while (i < 4)
    {
        random_code[i] = numbers[rand() % 10];
        i++;
    }

    random_code[4] = '\0';

    return random_code;
}

void my_gues(char* gs, char* st_cd, int* wl_plc, int* misplcd)
{
    int gs_hm[10] = {0};
    int st_hm[10] = {0};
    *wl_plc = 0;
    *misplcd = 0;
    int i = 0;

    while (i < 4)
    {
        if (gs[i] == st_cd[i])
        {
            (*wl_plc)++;
        }
        else
        {
            gs_hm[gs[i] - '0']++;
            st_hm[st_cd[i] - '0']++;
        }
        i++;
    }

    for (int i = 0; i < 10; i++)
    {
        *misplcd += (st_hm[i] < gs_hm[i]) ? st_hm[i] : gs_hm[i];
    }
}


int correct_inpt(char* input)
{
    return (strlen(input) != 4) ? 0 : 1;

    int i = 0;
    while (i < 4)
    {
        return (input[i] < '0' || input[i] > '9') ? 0 : (i++, 1);
    }

    return 1;
}