#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define CODE_SIZE 4

int my_strlen(char *str)
{
  int len = 0;
  while (str[len] != '\0')
  {
    len++;
  }
  return len;
}

int my_strcmp(char *str1, char *str2)
{
  int len1 = my_strlen(str1);
  int len2 = my_strlen(str2);

  if (len1 != len2)
  {
    return len1 - len2;
  }

  for (int i = 0; i < len1; i++)
  {
    if (str1[i] != str2[i])
    {
      return str1[i] - str2[i];
    }
  }

  return 0;
}

int isddigit(char *sam)
{
  int str_length = my_strlen(sam);
  for (int k = 0; k < str_length; k++)
  {
    if (!(sam[k] >= '0' && sam[k] <= '8'))
      return 1;
  }
  return 0;
}

void toInt(int *code, char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    code[i] = str[i] - '0';
  }
}

int *genSecretCode()
{
  int *code = malloc(CODE_SIZE * sizeof(int));
  int numbs_used[9] = {0};
  srand(time(NULL));

  for (int i = 0; i < CODE_SIZE; i++)
  {
    int Random_nums = rand() % 10;

    while (numbs_used[Random_nums] == 1)
    {
      Random_nums = rand() % 10;
    }
    code[i] = Random_nums;
    numbs_used[Random_nums] = 1;
  }
  return code;
}

int checkInputErrors(char *buffer, int n, int *guess)
{

  if (n - 1 != CODE_SIZE  || buffer[n - 1] != '\n')
  {
    return -1;
  }

  for (int i = 0; i < n - 1; i++)
  {
    if (!(buffer[i] >= '0' && buffer[i] <= '9'))
    {
      return -1;
    }
  }

  toInt(guess, buffer);
  return 0;
}

void CheckCorrection(int *secretCode, int *guess)
{
  int WellPlaced = 0, MissPlaced = 0;
  for (int i = 0; i < CODE_SIZE; i++)
  {
    if (secretCode[i] == guess[i])
      WellPlaced++;
    else
    {
      for (int j = 0; j < CODE_SIZE; j++)
      {
        if (secretCode[i] == guess[j] && i != j)
        {
          MissPlaced++;
          break;
        }
      }
    }
  }
  if (WellPlaced == CODE_SIZE)
  {
    printf("Congratz! You did it!\n");
  }
  else
  {
    printf("\nWell placed pieces: %d\nMisplaced pieces: %d\n", WellPlaced, MissPlaced);
  }
}

void my_mastermind(int argc, char **argv)
{
  int *secret_code = NULL;
  int Max_Guess = 10, rounds = 0;
  int *guess = malloc(CODE_SIZE * sizeof(int));

  if (argc > 2)
  {
    if ((isddigit(argv[2]) != 0) || (my_strlen(argv[2]) != CODE_SIZE))
    {
      printf("Wrong input %s passed\n", argv[2]);
      secret_code = genSecretCode();
    }
    else
    {
      if (my_strcmp(argv[1], "-c") == 0)
      {
        secret_code = malloc(CODE_SIZE * sizeof(int));
        toInt(secret_code, argv[2]);
      }
      else if (my_strcmp(argv[1], "-t") == 0)
      {
        Max_Guess = atoi(argv[2]);
        if (Max_Guess > 10)
        {
          Max_Guess = 10;
        }
      }
    }
  }
  else
  {
    secret_code = genSecretCode();
  }
  printf("Will you find the secret code?\nPlease enter a valid guess\n");

  printf("\n---\nRound %d\n>", rounds);
  while (Max_Guess >= 0)
  {
    char *buffer = malloc((CODE_SIZE + 1) * sizeof(char));
    int n = read(STDIN_FILENO, buffer, CODE_SIZE + 1);

    if (checkInputErrors(buffer, n, guess) >= 0)
    {
      rounds++;
      Max_Guess--;
      CheckCorrection(secret_code, guess);
      printf("\n---\nRound %d.\n>", rounds);
    }
    else
    {
      printf("\nWrong Input Passed !\n");
      printf("\n---\nRound %d\n>", rounds);
    }
    free(buffer);
  }
  free(secret_code);
  free(guess);
}

int main(int argc, char **argv)
{
  my_mastermind(argc, argv);
  return 0;
}
