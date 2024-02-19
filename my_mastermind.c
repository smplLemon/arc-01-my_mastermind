#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void copying(char* dest, char* src){
  while (*src){
    *dest++ = *src++;
  }
  *dest = '\0';
}

int compareSt(char* str1, char* str2){
  while (*str1 && *str2 && *str1 == *str2){
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

int count(char* str, char c){
  int count = 0;
  while(*str){
    if(*str == c){
      count++;
    }
    str++;
  }
  return count;
}

char* generate(){
  char* code = calloc(5, sizeof(char));
  srand(time(NULL));
  for(int i = 0; i < 4;){
    char n = rand() % 9 + '0';
    if(count(code, n) == 0){
      code[i++] = n;
    }
  }
  return code;
}

void clearSt(char* str){
  while(*str){
    *str++ = '\0';
  }
}

char* readLine(char* input){
  clearSt(input);
  write(1, ">", 1);
  char c = '\0';
  for(int i = 0; read(0, &c, 1);){
    if(c == '\n'){
      return input;
    }
    input[i++] = c;
  }
  return NULL;
}

int Unique(char* input){
  for(int i = 0; input[i]; i++){
    if(count(input, input[i]) != 1 || input[i] < '0' || input[i] > '8'){
      return 0;
    }
  }
  return 1;
}

void printError(){
  printf("Wrong input!\n");
}

int invalidInput(char* input){
  int inputLength = strlen(input);
  if(inputLength != 4 || !Unique(input)){
    printError();
    return 1;
  }
  return 0;
}

int checkWin(char* secretCode, char* input){
  int wellPlaced = 0, misplaced = 0;
  for(int i = 0; input[i]; i++){
    for(int j = 0; secretCode[j]; j++){
      if(input[i] == secretCode[j]){
        if(i != j){
          misplaced++;
        } 
        else{
          wellPlaced++;
        }
      }
    }
  }
  if(wellPlaced == 4){
    printf("Congratz! You did it!\n");
    return 1;
  }
  printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wellPlaced, misplaced);
  return 0;
}

void Mastermind(char* secretCode, int roundCount){
  printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");
  char* input = malloc(10);
  for(int round = 0; round < roundCount;){
    printf("Round %d\n", round);
    if(!readLine(input)){
      return;
    }
    if(!invalidInput(input)){
      if(checkWin(secretCode, input)){
        return;
      }
      round++;
    }
  }
}

int main(int argc, char** argv){
  char* secretCode = NULL;
  int roundCount = 10;
  for(int i = 0; i < argc; i++){
    if(compareSt(argv[i], "-c") == 0){
      if(argv[i + 1] && strlen(argv[i + 1]) == 4 && Unique(argv[i + 1])){
        secretCode = argv[i + 1];
      } 
      else{
        printf("Invalid secret code. Please provide exactly 4 unique numbers.\n");
        return 1;
      }
    } 
    else if(compareSt(argv[i], "-t") == 0){
      roundCount = atoi(argv[++i]);
    }
  }
  if(!secretCode){
    secretCode = generate();
  }
  Mastermind(secretCode, roundCount);
  return 0;
}