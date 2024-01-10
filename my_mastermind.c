#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define CODE_LENGTH 4

void check_out(char* str, char* secret_code, int* well, int* mis)
{
    int i = 0;
     *well = 0;
     *mis = 0;

    int arr1[10] = {0};
    int arr2[10] = {0};

    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (str[i] == secret_code[i]){
            (*well)++;
        }
         else 
        {
            arr1[str[i] - '0']++;
            arr2[secret_code[i] - '0']++;
        }
    }
    while (i<10)
    {
        if (arr2[i] < arr1[i]){
            *mis += arr2[i];
        }
         else
        {
            *mis += arr1[i];
        }
        i++;
    }
}

char* random_generated(char* code)
{
    const char string[] = "0123456789";
    int number = 0;

    while (number<CODE_LENGTH)
    {
        code[number] = string[rand() % 10];
        number++;
    }
    code[CODE_LENGTH] = '\0';
    return code;
}



int input_check(char* input)
{
    int i = 0;
    if (strlen(input) != CODE_LENGTH){
        return 0;
    }

    while (i < CODE_LENGTH)
    {
        if (input[i] < '0' || input[i] > '9')
        {
            return 0;
        }
        i++;
    }
           return 1;
}



int main(int argc, char** argv)
{
    char* secret__code = calloc(sizeof(char), CODE_LENGTH + 1);

    int numbers = 10;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            strncpy(secret__code, argv[i + 1], CODE_LENGTH);

            secret__code[CODE_LENGTH] = '\0';

        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            numbers = atoi(argv[i + 1]);
        }
    }

       if (strlen(secret__code) == 0)
       {
        srand(time(NULL));
        random_generated(secret__code);
    }

    char str[CODE_LENGTH + 1];
    int well, mis;
    int round = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

     while (round < numbers)
     {
        printf("---\nRound %d\n>", round);

     if (read(0, str, CODE_LENGTH + 1) == -1)
     {
            printf("Error reading input.\n");

            return 1;
        }

     str[CODE_LENGTH] = '\0';

      if (!input_check(str))
      {
            printf("mis input!\n");
            continue;
      }

        check_out(str, secret__code, &well, &mis);

        if (well == CODE_LENGTH)
        {
            printf("Congratz! You did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well, mis);
        round++;
    }

    printf("---\nGame over. You didn't find the secret code.\n");

    return 0;
}