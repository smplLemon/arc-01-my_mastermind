#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

bool step(int argc, char *argv[], int *code);
int generate(int *code);
int play(int code[]);

bool step(int argc, char *argv[], int *code)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            if (i + 1 < argc && strlen(argv[i + 1]) == 4)
            {
                for (int j = 0; j < 4; j++)
                {
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
            generate(code);
            return true;
        }
    }
    printf("No code provided\n");
    return false;
}

int generate(int *code)
{
    srand(time(NULL));

    for (int i = 0; i < 4; i++)
    {
        code[i] = rand() % 9;
    }
    return 0;
}

int inputCheck(int guess)
{
    int numDigits = 0;
    int temp = guess;

    while (temp != 0)
    {
        temp /= 10;
        numDigits++;
    }

    if (numDigits != 4)
    {
        printf("Wrong input!!!\n");
        return -1;
    }
    int digit1 = guess / 1000;
    int digit2 = (guess / 100) % 10;
    int digit3 = (guess / 10) % 10;
    int digit4 = guess % 10;

    if (digit1 > 8 || digit1 < 0 || digit2 > 8 || digit2 < 0 || digit3 > 8 || digit3 < 0 || digit4 > 8 || digit4 < 0)
    {
        printf("Wrong input!!!\n");
        return -1;
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
    if (mp == 4 )
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

int play(int code[])
{
    int round = 0;
    while (round <= 10)
    {
        int guess;
        printf("---\n");
        printf("Round %d \n", round);
        printf(">");
        int result = scanf("%d", &guess);
        if (result == EOF) {
            printf("\nReceived EOF (Ctrl+D). Exiting...\n");
            return 1;
        } else if (result != 1) {
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

    if (!step(argc, argv, code))
    {
        return 1;
    }

    printf("Will you find secret code?\n");
    printf("Please enter a valid guess\n");

    return play(code);
}
