#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>

#define the_length_of_secret_code 4



char *scan_func() {
  int round_size = 8;
  char temp;
  int i = 0;
  char *entry = calloc(sizeof(char), round_size);
  ssize_t ret;
  while ((ret = read(0, &temp, 1)) > 0)
  {
    if (temp == '\n'){
      entry[i] = '\0';
      return entry;
    }
    entry[i++] = temp;
  }
  if (ret == 0){
    free(entry);
    printf("\nStopping the program...\n");
    exit(0);
  }free(entry);
  return NULL;
}

bool isNumberPresent(int number, char *array, int rounds)
{
    int i = 0;
    while(i < rounds)
    {
        if (array[i] == number)
        {
            return true;
        }
        i++;
    }
    return false;
}


char *str_chr(char *a, char b)
{
  int i = 0;
  while (a[i] != '\0')
  {
    if(a[i] == b)
    {
      return &a[i];
    }
    i++;
  }
  return 0;
}

int str_len(char *str)
{
  int count = 0;
  while (str[count] != '\0')
  {
    count+=1;
  }
  return count;
}

void create_secret_code(char* secret)
{
  srand((unsigned)time(NULL));
  char temp;
  int i = 0;
  while (i < the_length_of_secret_code){
    temp = rand() % 8 + '0';
    if (str_chr(secret, temp) == 0){
      secret[i] = temp;
      i++;
    }
  }
  secret[the_length_of_secret_code] = '\0';
}


bool acceptable_prediction(char *build)
{
  for (int i = 0; i < the_length_of_secret_code; ++i)
  {
    if ((build[i] < '0' || build[i] > '8') || isNumberPresent(build[i], build, i))
    {
      return false;
    }
  }
  return str_len(build) == the_length_of_secret_code;
}


char *assessGuess()
{
  printf(">");
  fflush(stdout);

  char *build = scan_func();

  while (!acceptable_prediction(build))
  {
  if (build == NULL){return NULL;}
  }

if (!acceptable_prediction(build))
    {
      printf("Wrong input!\n");
      printf(">");
      fflush(stdout);
      free(build);
      build = scan_func();
    }
    return build;
  } 
  


void evaluateGuess(char *secret_code, char *build)
{
  int wellPlaced = 0;
  int missplaced = 0;
  for (int i = 0; i < the_length_of_secret_code; ++i)
  {
    if (build[i] == secret_code[i])
    {
      wellPlaced++;
    }
    else if (str_chr(secret_code, build[i]) != NULL)
    {
      missplaced++;
    }
  }
  printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, missplaced);
}


void main_f(char *secret_code, int move) {
  if (!acceptable_prediction(secret_code))
    exit(1);
     printf("Will you find the secret code?\nPlease enter a valid guess\n");
  for (int round = 0; round < move; round++) {
    printf("---\n");
    printf("Round %d\n", round);
    char *build = assessGuess();
    if (build == NULL)
      return;
    if (strcmp(secret_code, build) == 0) {
      printf("Congratz! You did it!\n");
      free(build);
      exit(0);
    }else
    {
      evaluateGuess(secret_code, build);
    }free(build);
  }
}

int main(int argc, char **argv)
{
  char secret_c[the_length_of_secret_code + 1];
  create_secret_code(secret_c);
  if (argc < 2){
    main_f(secret_c, 10);
  }else if (argc == 3 && (strcmp(argv[1], "-c") == 0))
  {
    main_f(argv[2], 10);
  }else if (argc == 3 && (strcmp(argv[1], "-t") == 0))
  {
    main_f(secret_c, atoi(argv[2]));
  }else if (argc == 5 && (strcmp(argv[3], "-t") == 0) && (strcmp(argv[1], "-c") == 0))
  {
    main_f(argv[2], atoi(argv[4]));
  }else if (argc == 5 && (strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-c") == 0))
  {
    main_f(argv[4], atoi(argv[2]));
  }
}
