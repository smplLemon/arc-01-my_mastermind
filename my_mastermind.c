#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define PIECES 9
#define CODE_LEN 4
#define MAX_ATTEMPTS 10
#define BUFFER_SIZE 5

void generate_secret_code(char code[]);
int parse_input(char *input, int max_len);
void check_guess(char *guess, char *code, int *well_placed, int *misplaced);
// void print_feedback(int well_placed, int misplaced);
void print_feedback(int well_placed, int misplaced) {
    printf("Well placed pieces: %d\n", well_placed);
    printf("Misplaced pieces: %d\n", misplaced);
}
int main(int argc, char *argv[])
{
  int attempts = MAX_ATTEMPTS;
  int well_placed, misplaced;
  char secret_code[CODE_LEN + 1];
  char guess[BUFFER_SIZE];

  // Generate secret code or use provided code
  if (argc == 3 && strcmp(argv[1], "-c") == 0)
  {
    strcpy(secret_code, argv[2]);
  }
  else
  {
    generate_secret_code(secret_code);
  }

  // Check for -t option
  if (argc == 5 && strcmp(argv[3], "-t") == 0)
  {
    attempts = atoi(argv[4]);
  }

  printf("Will you find the secret code?\n");
  printf("Please enter a valid guess\n");

  for (int i = 0; i < attempts; i++)
  {
    well_placed = 0;
    misplaced = 0;

    printf("---\n");
    printf("Round %d\n", i + 1);
    printf(">");

    if (!parse_input(guess, CODE_LEN))
    {
      printf("Wrong input!\n");
      i--;
      continue;
    }

    check_guess(guess, secret_code, &well_placed, &misplaced);
    print_feedback(well_placed, misplaced); 
  if (well_placed > 0) {
    printf("Well placed pieces: %d\n", well_placed);
  } else {
    printf("Misplaced pieces: %d\n", misplaced);
  
}  
      printf("Congratz! You did it!\n");
      return 0;
  
  }

  printf("You lost! The code was: %s\n", secret_code);

  return 0;
  
}

void generate_secret_code(char code[])
{
  srand(time(NULL));

  for (int i = 0; i < CODE_LEN; i++)
  {
    code[i] = rand() % PIECES + '0';
  }

  code[CODE_LEN] = '\0';
}

int parse_input(char *input, int max_len) {
    int i = 0;
    char c;

    while (read(0, &c, 1) > 0 && c != '\n' && i < max_len - 1) {
        input[i++] = c;
    }

    input[i] = '\0';

    return i;
}


void check_guess(char guess[], char code[], int *well_placed, int *misplaced)
{
    int i, j;
    *well_placed = *misplaced = 0;
    for (i = 0; i < CODE_LEN; i++) {
        if (guess[i] == code[i])
            (*well_placed)++;
        else {
            for (j = 0; j < CODE_LEN; j++) {
                if (j == i)
                    continue;
                if (guess[i] == code[j]) {
                    (*misplaced)++;
                    break;
                }
            }
        }
    }
}

