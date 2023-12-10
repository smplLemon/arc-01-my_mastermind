#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LENGTH 4

void check(char *val, char *matter, int *p1, int *p2)
{
  *p1 = 0;
  *p2 = 0;
  int guess[10] = {0};
  int arr[10] = {0};

  int i = 0;
  while (i < LENGTH)
  {
    if (val[i] == matter[i])
    {
      (*p1)++;
    }
    else
    {
      guess[val[i] - '0']++;
      arr[matter[i] - '0']++;
    }
    i++;
  }

  int i = 0;
  while (i < 10)
  {
    if (arr[i] < guess[i])
    {
      *p2 += arr[i];
    }
    else
    {
      *p2 += guess[i];
    }
    i++;
  }
}

char *gen_random(char *random)
{
  const char num[] = "0123456789";

  int i = 0;
  while (i < LENGTH)
  {
    random[i] = num[rand() % 10];
    i++;
  }
  random[LENGTH] = '\0';
  return random;
}

int valid_input(char *input)
{
  if (strlen(input) != LENGTH)
  {
    return 0;
  }

  for (int i = 0; i < LENGTH; i++)
  {
    if (input[i] < '0' || input[i] > '9')
    {
      return 0;
    }
  }

  return 1;
}

int main(int argc, char **argv)
{
  char *matter = calloc(sizeof(char), LENGTH + 1);
  int max_attempts = 10;

  int i = 1;
  while (i < argc)
  {
    if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
    {
      strncpy(matter, argv[i + 1], LENGTH);
      matter[LENGTH] = '\0';
    }
    else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
    {
      max_attempts = atoi(argv[i + 1]);
    }
    i++;
  }

  if (strlen(matter) == 0)
  {
    srand(time(NULL));
    gen_random(matter);
  }

  char user_val[LENGTH + 1];
  int p1, p2;
  int rounds = 0;

  printf("Will you find the secret code?\n Enter a valid guess\n");

  while (rounds < max_attempts)
  {
    printf("---\nRound %d\n>", rounds);

    if (read(0, user_val, LENGTH + 1) == -1)
    {
      printf("Error reading input.\n");
      return 1;
    }

    user_val[LENGTH] = '\0';

    if (!valid_input(user_val))
    {
      printf("Wrong input!\n");
      continue;
    }

    check(user_val, matter, &p1, &p2);

    if (p1 == LENGTH)
    {
      printf("Congratz! You did it!\n");
      return 0;
    }

    printf("Well placed pieces: %d\np2 pieces: %d\n", p1, p2);
    rounds++;
  }

  printf("---\nGame over. You didn't find the secret code.\n");

  return 0;
}
