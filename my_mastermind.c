#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mastermind.h"

int main(int argc, char** argv)
{
    char* st_cdd = calloc(sizeof(char), 4 + 1);
    int max_att = 10;

    int i = 1;
    while (i < argc)
    {
        (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
            ? (strncpy(st_cdd, argv[i + 1], 4), st_cdd[4] = '\0')
            : (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
                  ? (max_att = atoi(argv[i + 1]))
                  : 0;
        i++;
    }

    (strlen(st_cdd) == 0) ? (srand(time(NULL)), generate_rm_code(st_cdd)) : 0;

    char user_guess[4 + 1];
    int well_placed, misplaced;
    int rounds = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (rounds < max_att)
    {
        printf("---\nRound %d\n>", rounds);

        if (read(0, user_guess, 4 + 1) == -1)
        {
            printf("Error reading input.\n");
            return 1;
        }

        user_guess[4] = '\0';

        if (!correct_inpt(user_guess))
        {
            printf("Wrong input!\n");
            continue;
        }

        my_gues(user_guess, st_cdd, &well_placed, &misplaced);

        (well_placed == 4)
            ? printf("Congratz! You did it!\n")
            : printf("Well placed pieces: %d\nMisplaced pieces: %d\n",
                     well_placed, misplaced);

        rounds++;
    }

    printf("---\nGame over. You didn't find the secret code.\n");

    return 1;
}