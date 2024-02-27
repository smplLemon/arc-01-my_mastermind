#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define CODE_LENGTH 4
#define NUM_COLORS 6

struct Game
{
    char *secretCode;
    int maxAttempts;
};

void printWelcomeMessage(struct Game game)
{
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
}
int isInputValid(char *input)
{
    int length = strlen(input);
    if (length != CODE_LENGTH)
    {
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        if (!(input[i] >= '0' && input[i] <= '5'))
        {
            return 0;
        }
    }

    return 1;
}

int hasDuplicateDigits(char *input)
{
    int digits[10] = {0};
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        int digit = input[i] - '0';
        digits[digit]++;

        if (digits[digit] > 1)
        {
            return 1;
        }
    }

    return 0;
}

char *generateRandomCode()
{
    char *code = malloc(CODE_LENGTH + 1);
    srand(time(NULL));

    for (int i = 0; i < CODE_LENGTH;)
    {
        char digit = rand() % NUM_COLORS + '0';
        if (!strchr(code, digit))
        {
            code[i++] = digit;
        }
    }

    code[CODE_LENGTH] = '\0';
    return code;
}

void printRoundHeader(int roundNumber)
{
    printf("---\nRound %d\n", roundNumber);
    write(1, ">", 1);
}

char *readGuess()
{
    char *guess = malloc(CODE_LENGTH + 1); 
    int index = 0;
    char input;

    while (1)
    {
        if (read(0, &input, 1) < 0)
        {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        if (input == '\n')
        {
            guess[index] = '\0';
            if (!isInputValid(guess) || hasDuplicateDigits(guess))
            {
                printf("Wrong input!\n");
                write(1, ">", 1);
                fflush(stdout);
                free(guess);
                return readGuess();
            }
            else
            {
                return guess;
            }
        }

        guess[index++] = input;
    }
    return "abc";
}

int hasCorrectPositions(char *secretCode, char *guess)
{
    int correctPositions = 0;
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        if (secretCode[i] == guess[i])
        {
            correctPositions++;
        }
    }
    return correctPositions;
}

int hasMisplacedPieces(char *secretCode, char *guess)
{
    int misplacedPieces = 0;
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        for (int j = 0; j < CODE_LENGTH; j++)
        {
            if (secretCode[i] == guess[j] && i != j)
            {
                misplacedPieces++;
            }
        }
    }
    return misplacedPieces;
}

void printGameResult(char *secretCode, int isGameWon)
{
    if (isGameWon)
    {
        printf("Congratz! You did it!\n");
    }
    else
    {
        printf("Game over!\n");
    }
}

int playMastermind(struct Game game)
{
    char *secretCode = (game.secretCode == NULL) ? generateRandomCode() : game.secretCode;
    printWelcomeMessage(game);

    for (int round = 0; round <= game.maxAttempts; round++)
    {
        printRoundHeader(round);
        char *guess = readGuess();

        if (strcmp(guess, "abc") == 0)
        {
            return 0;
        }

        int correctPos = hasCorrectPositions(secretCode, guess);

        if (correctPos == CODE_LENGTH)
        {
            printGameResult(secretCode, 1);
            return 1;
        }
        else
        {
            int misplacedPieces = hasMisplacedPieces(secretCode, guess);
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", correctPos, misplacedPieces);
        }
    }

    printGameResult(secretCode, 0);
    return 0;
}

int main(int argc, char **argv)
{
    struct Game game;
    game.maxAttempts = 10;
    game.secretCode = NULL;
    playMastermind(game);

    return 0;
}