#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

bool step(int argc, char *argv[], int *code, int *round);
int generate(int *code);
int play(int code[], int *round);

bool step(int argc, char *argv[], int *code, int *round)
{
    if (argc == 1)
    {
        generate(code);
        return true;
    }

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            if (i + 1 < argc && strlen(argv[i + 1]) == 4)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (argv[i + 1][j] == '9') {
                        printf("Invalid input! Code cannot contain '9'.\n");
                        return false;
                    }
                    code[j] = argv[i + 1][j] - '0';
                }
                return true;
            }
            else
            {
                printf("Invalid or missing code after -c\n");
                return false;
            }
        }
        if (strcmp(argv[i], "-t") == 0)
        {
            if (argc == 3)
            {
                *round = atoi(argv[i + 1]);
            }

            generate(code);
            return true;
        }
    }
    return false;
}

int generate(int *code)
{
    srand(time(NULL));

    bool unique = false;

    while (!unique)
    {
        unique = true;

        for (int i = 0; i < 4; i++)
        {
            code[i] = rand() % 8;
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                if (code[i] == code[j])
                {
                    unique = false;
                    break;
                }
            }
            if (!unique)
                break;
        }
    }

    return 0;
}

int inputCheck(int guess)
{
    int numDigits = 0;
    int temp = guess;
    int digits[10] = {0};

    while (temp != 0)
    {
        int digit = temp % 10;
        temp /= 10;
        numDigits++;
        digits[digit]++;
    }

    if (numDigits != 4)
    {
        printf("Wrong input!\n");
        return -1;
    }

    if (digits[9] > 0)
    {
        printf("Wrong input!\n");
        return -1;
    }

    for (int i = 0; i < 10; i++)
    {
        if (digits[i] > 1 || digits[i] == 3 || digits[i] == 4)
        {
            printf("Wrong input!\n");
            return -1;
        }
    }

    return 0;
}

int check(int code[], int guess)
{
    int mp = 0;
    int wp = 0;
    int guess_digits[4];
    guess_digits[0] = guess / 1000;
    guess_digits[1] = (guess / 100) % 10;
    guess_digits[2] = (guess / 10) % 10;
    guess_digits[3] = guess % 10;
    for (int i = 0; i < 4; i++)
    {
        if (code[i] == guess_digits[i])
        {
            mp++;
        }
        else
        {
            for (int j = 0; j < 4; j++)
            {
                if (j != i && code[j] == guess_digits[i])
                {
                    wp++;
                    break;
                }
            }
        }
    }
    if (mp == 4)
    {
        return 1;
    }

    printf("Well placed pieces: %d\n", mp);
    printf("Misplaced pieces: %d\n", wp);
    return 0;
}

int playRound(int code[], int guess)
{
    if (inputCheck(guess) == -1)
    {
        return -1;
    }
    else if (check(code, guess) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void congrats()
{
    printf("Congratz! You did it!\n");
}

int play(int code[], int *roundI)
{
    int round = 0;
    while (round <= *roundI || round <= 10)
    {
        int guess;
        printf("---\n");
        printf("Round %d \n", round);
        printf(">");
        int result = scanf("%d", &guess);
        if (result == EOF)
        {
            return 1;
        }
        else if (result != 1)
        {
            printf("Wrong input!\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        int temp = playRound(code, guess);
        if (temp == 1)
        {
            congrats();
            return 1;
        }
        else if (temp == 0)
        {
            round++;
        }
    }
    printf("You didn't find code:(\n");
    return 0;
}

int main(int argc, char *argv[])
{
    int code[4];
    int round;

    if (!step(argc, argv, code, &round))
    {
        return 1;
    }

    printf("Will you find secret code?\n");
    printf("Please enter a valid guess\n");

    return play(code, &round);
}
