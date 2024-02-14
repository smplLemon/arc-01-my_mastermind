#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CODE_LENGTH 4
#define DEFAULT_ATTEMPTS 10

void generateSecretCode(char *secretCode)
{
    srand(time(NULL));
    const char numbers[] = "0123456789";
    int i = 0;
    while (i < CODE_LENGTH)
    {
        secretCode[i] = numbers[rand() % 10];
        i++;
    }
    secretCode[CODE_LENGTH] = '\0';
}

void evaluateGuess(char *guess, char *secretCode, int *right, int *wrong)
{
    *right = 0;
    *wrong = 0;
    int freq[10] = {0};
    int misplaced[10] = {0};
    int i = 0;
    while (i < CODE_LENGTH)
    {
        if (guess[i] == secretCode[i])
        {
            (*right)++;
        }
        else
        {
            freq[secretCode[i] - '0']++;
            misplaced[guess[i] - '0']++;
        }
        i++;
    }
    i = 0;
    while (i < 10)
    {
        *wrong += freq[i] < misplaced[i] ? freq[i] : misplaced[i];
        i++;
    }
}

int main(int argc, char *argv[])
{
    char secretCode[CODE_LENGTH + 1];
    int maxAttempts = DEFAULT_ATTEMPTS;

    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            strncpy(secretCode, argv[i + 1], CODE_LENGTH);
            secretCode[CODE_LENGTH] = '\0';
            i += 2;
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            maxAttempts = atoi(argv[i + 1]);
            i += 2;
        }
        else
        {
            i++;
        }
    }

    if (strlen(secretCode) == 0)
    {
        generateSecretCode(secretCode);
    }

    int attempts = 0;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    while (attempts < maxAttempts)
    {
        printf("---\nRound %d\n>", attempts);
        char guess[CODE_LENGTH + 1];
        scanf("%s", guess);

        if (strlen(guess) != CODE_LENGTH)
        {
            printf("Wrong input!\n");
            continue;
        }

        int right, wrong;
        evaluateGuess(guess, secretCode, &right, &wrong);

        if (right == CODE_LENGTH)
        {
            printf("Congratz! You did it!\n");
            return 0;
        }
        else
        {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", right, wrong);
        }

        attempts++;
    }

    printf("---\nGame over. You didn't find the secret code.\n");
    return 0;
}
