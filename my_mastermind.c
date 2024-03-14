#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define CODE_SIZE 4

int my_strlen(char *str) {
  int len = 0;
  while (str[len] != '\0')
    len++;
  return len;
}

int my_strcmp(char *str1, char *str2) {
  int len1 = my_strlen(str1);
  int len2 = my_strlen(str2);
  if (len1 != len2)
    return len1 - len2;
  for (int i = 0; i < len1; i++) {
    if (str1[i] != str2[i])
      return str1[i] - str2[i];
  }
  return 0;
}

void my_strncpy(char *dest, char *src, int n) {
  int i;
  for (i = 0; i < n && src[i] != '\0'; i++)
    dest[i] = src[i];
  dest[i] = '\0';
}

int isddigit(char *sam) {
  int str_length = my_strlen(sam);
  for (int k = 0; k < str_length; k++) {
    if (!(sam[k] >= '0' && sam[k] <= '8'))
      return -1;
  }
  return 0;
}

char *genSecretCode() {
  char *number = calloc(CODE_SIZE + 1, sizeof(char));
  srand(time(NULL));
  for (int i = 0; i < CODE_SIZE; i++) {
    int digit, found = 1;
    while (found) {
      digit = rand() % 10;
      found = 0;
      for (int j = 0; j < i; j++) {
        if (number[j] == digit + '0') {
          found = 1;
          break;
        }
      }
    }
    number[i] = digit + '0';
  }
  number[CODE_SIZE] = '\0';
  return number;
}

char *readInpVal() {
  char *buffer = calloc((CODE_SIZE + 1), sizeof(char));
  char tempChar;
  int i = 0;
  while ((read(0, &tempChar, 1)) > 0) {
    if (tempChar != '\n')
      buffer[i++] = tempChar;
    else if (tempChar == EOF)
      break;
    else
      break;
  }
  return buffer;
}

int CheckDuplicates(char *input) {
  int len = my_strlen(input);
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (input[i] == input[j])
        return -1;
    }
  }
  return 0;
}

int CheckInputErrors(char *outerGuess) {
  int bufferLeng = my_strlen(outerGuess);
  if ((bufferLeng != CODE_SIZE) || ((isddigit(outerGuess)) != 0) || ((CheckDuplicates(outerGuess)) != 0))
    return -1;
  else
    return 0;
}

int hasWellPlaced(char *secretCode, char *guess) {
  int WellPlaced = 0;
  for (int i = 0; i < CODE_SIZE; i++) {
    if (secretCode[i] == guess[i]) {
      WellPlaced++;
    }
  }
  return WellPlaced;
}

int hasMissPlaced(char* secretCode, char* guess) {
  int misplacedPieces = 0;
  for (int i = 0; i < CODE_SIZE; i++) {
    for (int j = 0; j < CODE_SIZE; j++) {
      if (secretCode[i] == guess[j] && i != j) {
        misplacedPieces++;
        }
      }
    }
    return misplacedPieces;
}

int CheckCorrection(char *secretCode, char *guess) {
  int WellPlaced = hasWellPlaced(secretCode, guess);
  if (WellPlaced == CODE_SIZE) {
    printf("Congratz! You did it!\n");
    return 0;
  } 
  else {
    int MissPlaced = hasMissPlaced(secretCode, guess);
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", WellPlaced, MissPlaced);
    return -1;
  }
}

void collectArgs(int argc, char **argv, int *Max_Guess, char **secret_code) {
  for (int i = 1; i < argc; i++) {
    if (my_strcmp(argv[i], "-c") == 0) {
      *secret_code = calloc((CODE_SIZE + 1), sizeof(char));
      my_strncpy(*secret_code, argv[i + 1], CODE_SIZE);
    }
    if (my_strcmp(argv[i], "-t") == 0) {
      *Max_Guess = atoi(argv[i + 1]);
      if (*Max_Guess > 10)
        *Max_Guess = 10;
    }
  }
}

void printInterface(int status, int rounds) {
  if (status == 3) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    printf("---\nRound %d\n", rounds);
    write(1, ">", 1);
  }
  else if (status == 2) {
    printf("---\nRound %d\n", rounds);
    write(1, ">", 1);
  }
  else if (status == 1) {
    printf("Wrong Input!\n");
    printf("---\nRound %d\n", rounds);
    write(1, ">", 1);
  }
}
  
void myMastermind(int argc, char **argv) {
    char *secret_code = NULL;
    int Max_Guess = 10, rounds = 1;
    char *guess = NULL;
    collectArgs(argc, argv, &Max_Guess, &secret_code);
    if (secret_code == NULL) secret_code = genSecretCode();
    printInterface(3, rounds);
    while (Max_Guess > 0 && (guess = readInpVal())[0] != '\0') {
        if (CheckInputErrors(guess) == 0) {
            rounds++;
            Max_Guess--;
            if (CheckCorrection(secret_code, guess) == 0) break;
            else Max_Guess != 0 ? printInterface(2, rounds) : NULL;
        } else printInterface(1, rounds);
        free(guess);
    }
    free(secret_code);
}


int main(int argc, char **argv) {
  myMastermind(argc, argv);
  return 0;
}
