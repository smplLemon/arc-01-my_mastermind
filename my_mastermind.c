#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_ROUNDS 10
#define LENGTH_CODE 4

int *generateSecretCode(int *secretCode)
{
    int counter = 0;
    do
    {
        secretCode[counter++] = rand() % 10;
    } while (counter < LENGTH_CODE);

    return secretCode;
}

int checkCharacters(char character)
{
    if (character >= '0' && character <= '9')
    {
        return 1;
    }
    return 0;
}

int readIndexs(int guessCode[LENGTH_CODE])
{
    char c;
    int i = 0;

    while (read(STDIN_FILENO, &c, 1) > 0 && i <= LENGTH_CODE)
    {
        if (c >= '0' && c <= '9')
        {
            if (i < LENGTH_CODE)
            {
                guessCode[i++] = c - '0';
            }
            else
            {
                return -1;
            }
        }
        else if (c == '\n')
        {
            break;
        }
        else
        {
            return -1;
        }
    }
    if(c == '\0')
    {
        return 0;
    }
    if (i < LENGTH_CODE)
    {
        return -1;
    }
    return i;
}

int printWellAndMisPlaces(int guessCode[LENGTH_CODE], int secretCode[LENGTH_CODE])
{
    int wellCount = 0;
    int MisCount = 0;
    int i = 0;
    int j = 0;

    do
    {
        if (guessCode[i] == secretCode[i])
        {
            wellCount++;
        }
        else
        {
            for (j = 0; j < LENGTH_CODE; j++)
            {
                if (j != i && guessCode[i] == secretCode[j])
                {
                    MisCount++;
                    break;
                }
            }
        }
        i++;
    } while (i < LENGTH_CODE);

    if (wellCount == LENGTH_CODE)
    {
        return 1;
    }

    printf("Well placed pieces: %d\n", wellCount);
    printf("Misplaced pieces: %d\n", MisCount);

    return 0;
}

int Rounds(int guessCode[LENGTH_CODE], int secretCode[LENGTH_CODE], int lengthRounds, int countRounds)
{
    printf("Will you find the secret code?\nPlease enter a valid guess:\n");
    int round = MAX_ROUNDS;
    int attemp = 0;

    if (countRounds > 0)
    {
        round = lengthRounds;
    }

    while (attemp < round)
    {
        printf("---\nRound: %d\n>", attemp + 1);

        int readResult = readIndexs(guessCode);
        if (readResult == -1)
        {
            printf("\nWrong input!\n");
            continue;
            return 0;
        }
        else if (readResult == 0)
        {
            printf("\nGame over! Game ended!\n");
            return 0;
        }

        int resultPrintWelMisPlaces = printWellAndMisPlaces(guessCode, secretCode);

        if (resultPrintWelMisPlaces == 1)
        {
            printf("Congratz! You did it!\n");
            break;
        }

        if (attemp == round - 1)
        {
            printf("You didn't find the secret code.\nThe secret code was: ");
            for (int i = 0; i < LENGTH_CODE; i++)
            {
                printf("%d", secretCode[i]);
            }
            printf("\n");
        }
        attemp++;
    }
    return 0;
}

int main(int argc, char **argv)
{
    srand(time(0));
    int secretCode[LENGTH_CODE];
    int guessCode[LENGTH_CODE];
    int lengthMaxRounds = 0;
    int countRounds = 0;
    int i, j;
    int codeProvided = 0;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            char *codeBuffer = argv[i + 1];

            for (j = 0; j < LENGTH_CODE && codeBuffer[j] != '\0'; j++)
            {
                secretCode[j] = codeBuffer[j] - '0';
            }
            if (j < LENGTH_CODE)
            {
                printf("Error: The secret code must be a 4-digit number.\n");
                return -1;
            }
            codeProvided = 1;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            lengthMaxRounds = atoi(argv[i + 1]);
            if (lengthMaxRounds > MAX_ROUNDS)
            {
                lengthMaxRounds = MAX_ROUNDS;
            }
            countRounds = 1;
        }
    }

    if (codeProvided == 0)
    {
        generateSecretCode(secretCode);
    }

    Rounds(guessCode, secretCode, lengthMaxRounds, countRounds);

    return 0;
}
