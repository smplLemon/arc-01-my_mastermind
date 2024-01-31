///// Libraries /////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>

#define CODE_LENGTH 4

////////////////////////// scanf //////////////////////////

char *scan_function() {
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

bool isNumberPresent(int number, char *array, int round_size)
{
    int i = 0;
    while(i < round_size)
    {
        if (array[i] == number)
        {
            return true;
        }
        i++;
    }
    return false;
}
////////////////////////// str_chr ////////////////////////// 

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
////////////////////////// str_len ////////////////////////// 

int str_len(char *str)
{
  int count = 0;
  while (str[count] != '\0')
  {
    count+=1;
  }
  return count;
}
////////////////////////// generate_secret_code ////////////////////////// 

void create_secret_code(char* secret)
{
  srand((unsigned)time(NULL));
  char temp;
  int i = 0;
  while (i < CODE_LENGTH){
    temp = rand() % 9 + '0';
    if (str_chr(secret, temp) == 0){
      secret[i] = temp;
      i++;
    }
  }
  secret[CODE_LENGTH] = '\0';
}

////////////////////////// is_Valid_Guess ////////////////////////// 

bool acceptable_prediction(char *guess)
{
  for (int i = 0; i < CODE_LENGTH; ++i)
  {
    if ((guess[i] < '0' || guess[i] > '9') || isNumberPresent(guess[i], guess, i))
    {
      return false;
    }
  }
  return str_len(guess) == CODE_LENGTH;
}

////////////////////////// getUserGuess ////////////////////////// 

char *assessGuess()
{
  printf(">");
  fflush(stdout);

  char *guess = scan_function();

  while (!acceptable_prediction(guess))
  {
  if (guess == NULL){return NULL;}
    if (!acceptable_prediction(guess))
    {
      printf("Wrong input!\n");
      printf(">");
      fflush(stdout);
      free(guess);
      guess = scan_function();
    }
  } 
  return guess;
}
////////////////////////// evaluateGuess ////////////////////////// 

void evaluateGuess(char *secret_code, char *guess)
{
  int wellPlaced = 0;
  int missplaced = 0;
  for (int i = 0; i < CODE_LENGTH; ++i)
  {
    if (guess[i] == secret_code[i])
    {
      wellPlaced++;
    }
    else if (str_chr(secret_code, guess[i]) != NULL)
    {
      missplaced++;
    }
  }
  printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, missplaced);
}

////////////////////////// brain //////////////////////////

void main_f(char *secret_code, int move) {
  if (!acceptable_prediction(secret_code))
    exit(1);
     printf("Will you find the secret code?\nPlease enter a valid guess\n");
  for (int round = 0; round < move; round++) {
    printf("---\n");
    printf("Round %d\n", round);
    char *guess = assessGuess();
    if (guess == NULL)
      return;
    if (strcmp(secret_code, guess) == 0) {
      printf("Congratz! You did it!\n");
      free(guess);
      exit(0);
    }else
    {
      evaluateGuess(secret_code, guess);
    }free(guess);
  }
}

////////////////////////// Main //////////////////////////
int main(int argc, char **argv)
{
  char secret_c[CODE_LENGTH + 1];
  create_secret_code(secret_c);
  if (argc < 2)
  {
    main_f(secret_c, 10);
  }
  else if (argc == 3 && (strcmp(argv[1], "-c") == 0))
  {
    main_f(argv[2], 10);
  }
  else if (argc == 3 && (strcmp(argv[1], "-t") == 0))
  {
    main_f(secret_c, atoi(argv[2]));
  }
}