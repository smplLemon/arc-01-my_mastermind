#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void my_strcpy(char* s1, char* s2){
  for(int i = 0; s2[i]; i++){
    s1[i] = s2[i];
  }
}

int my_strcmp(char* s1, char* s2){
  for(int i = 0; s1[i] || s2[i]; i++){
    if(s1[i] != s2[i]){
      return (int)(s1[i] - s2[i]);
    }
  }
  return 0;
}

int is_exist(char* s1, char c){
  short count = 0;
  for(int i = 0; s1[i]; i++ ){
    if(s1[i] == c){
      count++;
    }
  }
  return count;
}

char* code_generator(){
  char* str = calloc(5 , sizeof(char));
  srand( (unsigned) time(NULL));
  char n;
  for(int i = 0; i < 4 ;){
    if(!is_exist(str , n = (char)(rand() % 9 + '0'))){
      str[i++] = n;
    }
  }
  return str;
}

void my_free(char* s1){
  for(int i = 0; s1[i]; i++){
    s1[i] = '\0';
  }
}

char* my_readline(char* input){
  my_free(input);
  write(1, ">", 1);
  char x = '\0';
  for(int i = 0; read(0,&x,1); ){
    if(x == (int)10){
      return input;
    }
    input[i++] = x;
  }
  return NULL;
}

short is_uniq(char* input){
  for(short i = 0; input[i]; i++){
    if(is_exist(input, input[i]) != 1){
      return 0;
    }
    if(input[i] < '0' || input[i] > '8'){
      return 0;
    }
  }
  return 1;
}

void print_err(){
  printf("Wrong input!\n");
}

int is_input_wrong(char* input){
  short input_length;
  if(4 != (input_length = strlen(input))){
    print_err();
    return 1;
  }
  else if (!is_uniq(input)){
    print_err();
    return 1;
  }
  return 0;
}

int win_check(char* mistery_code, char* input){
  short well_placed_pieces = 0;
  short miss_placed_pieces = 0;
  for(int i = 0; input[i]; i++){
    for(int j = 0; mistery_code[j]; j++){
      if(input[i] == mistery_code[j]){
        if(i != j){
          miss_placed_pieces++;
        }else{
          well_placed_pieces++;
        }
      }
    }
  }
  if(well_placed_pieces == 4){
    printf("Congratz! You did it!\n");
    return 1;
  }
  printf("Well placed pieces: %d\n", well_placed_pieces);
  printf("Misplaced pieces: %d\n", miss_placed_pieces);
  return 0;
}

void mastermind_game(char* mistery_code, int round_counter){
  printf("Will you find the secret code?\nPlease enter a valid guess\n---\n");
  char* input = malloc(10);
  short n = 0; 
  for(int i = 0; i < round_counter;){
    if(n != i){
      printf("Round %d\n", n = i);
    }
    if(!my_readline(input)){
      return;
    }
    if(!is_input_wrong(input)){
      if(win_check(mistery_code, input) == 1){
        return;
      }
    }else{
      continue;
    }
    i++;
  }
}

int main(int ac, char** av){
  char* mistery_code = NULL;
  int round_counter = 10;
  for(int i = 0; i < ac; i++){
    if(!my_strcmp(av[i], "-c")){
      mistery_code = av[++i];
    }
    else if(!my_strcmp(av[i], "-t")){
      round_counter = atoi(av[++i]);
    }
  }
  if(!mistery_code){
    mistery_code = code_generator();
  }
  // printf("sec = %s\nround = %d\n", mistery_code, round_counter);
  mastermind_game(mistery_code, round_counter);
  return 0;
}
