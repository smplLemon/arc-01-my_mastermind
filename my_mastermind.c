#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define CODE_SIZE 4

int my_strlen(char *str)
{
  int len = 0;
  while (str[len] != '\0')
    len++;
  return len;
}

int my_strcmp(char *str1, char *str2)
{
  int len1 = my_strlen(str1);
  int len2 = my_strlen(str2);

  if (len1 != len2)
    return len1 - len2;

  for (int i = 0; i < len1; i++)
  {
    if (str1[i] != str2[i])
      return str1[i] - str2[i];
  }
  return 0;
}

char *my_strchr(char *s, int c)
{
  while (*s && *s != c)
    s++;
  return (*s == c) ? (char *)s : NULL;
}

int isddigit(char *sam)
{
  int str_length = my_strlen(sam);
  for (int k = 0; k < str_length; k++)
  {
    if (!(sam[k] >= '0' && sam[k] <= '8'))
    {
      printf("Invalid digit detected\n");
      return -1;
    }
  }
  return 0;
}

void toInt(int *code, char *str)
{
  int result = 0;
  for (int i = 0; str[i] >= '0' && str[i] <= '8'; i++)
  {
    result = result * 10 + (str[i] - '0');
    code[i] = result;
  }
}

char *genSecretCode()
{
  char *number = malloc(5 * sizeof(char));
  srand(time(NULL));
  for (int i = 0; i < 4; i++)
  {
    int digit;
    int found = 1;
    while (found)
    {
      digit = rand() % 10;
      found = 0;
      for (int j = 0; j < i; j++)
      {
        if (number[j] == digit + '0')
        {
          found = 1;
          break;
        }
      }
    }
    number[i] = digit + '0';
  }
  number[4] = '\0';
  return number;
}

char *readInpVal()
{
  char *buffer = calloc((CODE_SIZE + 1), sizeof(char));
  char tempChar;
  int i = 0;
  while ((read(0, &tempChar, 1)) > 0)
  {
    if (tempChar != '\n')
      buffer[i++] = tempChar;
    else if (tempChar == EOF)
    {
      printf("\nCtrl+D pressed. Stopping the program.\n");
      break;
    }
    else
      break;
  }
  return buffer;
}

int CheckDuplicates(char *input)
{
  int len = my_strlen(input);
  for (int i = 0; i < len; i++)
  {
    for (int j = i + 1; j < len; j++)
    {
      if (input[i] == input[j])
      {
        printf("Duplicate digits detected!\n");
        return -1;
      }
    }
  }
  return 0;
}

int CheckInputErrors(char *outerGuess)
{
  int bufferLeng = my_strlen(outerGuess);
  if ((bufferLeng != CODE_SIZE) || ((isddigit(outerGuess)) != 0) || ((CheckDuplicates(outerGuess)) != 0))
    return -1;
  else
    return 0;
}

int CheckCorrection(int *secretCode, int *guess)
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
    return 0;
  }
  else
    printf("\nWell placed pieces: %d\nMisplaced pieces: %d\n", WellPlaced, MissPlaced);
  return -1;
}

void myMastermind(int argc, char **argv)
{
  int *secret_code = NULL;
  int Max_Guess = 10, rounds = 1;
  char *guess;

  for (int i = 1; i < argc; i++)
  {
    if (my_strcmp(argv[i], "-c") == 0)
    {
      secret_code = calloc(CODE_SIZE, sizeof(int));
      toInt(secret_code, argv[i + 1]);
    }
    if (my_strcmp(argv[i], "-t") == 0)
    {
      Max_Guess = atoi(argv[i + 1]);
      if (Max_Guess > 10)
      {
        printf("Guess limit 10!\n");
        Max_Guess = 10;
      }
    }
  }

  if (secret_code == NULL)
  {
    secret_code = calloc(CODE_SIZE, sizeof(int));
    char *gen_secret_code = genSecretCode();
    if (CheckDuplicates(gen_secret_code) != 0)
    {
      gen_secret_code = genSecretCode();
      printf("Secret code was re-generated\n");
    }
    toInt(secret_code, gen_secret_code);
  }
  printf("\nWill you find the secret code?\nPlease enter a valid guess\n");
  printf("\n---\nRound %d\n>", rounds);
  while (Max_Guess > 0)
  {
    guess = readInpVal();
    if (guess[0] == '\0')
      break;
    if (CheckInputErrors(guess) == 0)
    {
      rounds++;
      Max_Guess--;
      int *tempArr = calloc(CODE_SIZE, sizeof(int));

      toInt(tempArr, guess);
      if (CheckCorrection(secret_code, tempArr) == 0)
        break;
      else
      {
        if (Max_Guess == 0)
          printf("\nGame Over!\n");
        else
          printf("\n---\nRound %d\n>", rounds);
      }
    }
    else
    {
      printf("Wrong Input Passed !\n");
      printf("\n---\nRound %d\n>", rounds);
    }
  }
  free(guess);
  free(secret_code);
}

int main(int argc, char **argv)
{
  myMastermind(argc, argv);
  return 0;
}