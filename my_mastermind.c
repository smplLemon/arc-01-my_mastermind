#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define the_length_of_secret_code 4
#define the_line "--------------------------"
#define the_second_line "---------------------"
/*
  good afternoon mr Simple Lemon. finally I finished this project. after 2 weeks of trying to solve all bugs I realized that it's better to delete all this code and rewrite it from the beginning. Because there was to many bugs and when I was writing mastermind first time  i didn't understood all the tasks.
  I'll tell you straight! when I wrote this project I studyed from KhanTechPro's code how to write mastermind and where I have done mistakes in last porject.
  But I can say with confidence that I didn't copied any functions or parts of code (except the function the_scanf unfortunately i didn't understand how does that function works :(  but I promise that in next time I won't copy any functions from others code!) and all other functions I wrote by myself.
  And I have customized a little bit the user interface (ㆁωㆁ) I think this will add a little coziness to this game.

  P.s: I apologize if I made grammatical errors in the text Ó╭╮Ò 
*/

char *the_scanf() {
  int the_size_array = 10, the_index = 0;
  char *the_user_input = calloc(sizeof(char), the_size_array), temp;
  for (; read(0, &temp, 1); the_user_input[the_index++] = temp) {
    if (temp == '\n') {
      the_user_input[the_index] = '\0';
      return the_user_input;
    }
    if (the_index >= the_size_array - 1) {
      the_size_array *= 2;
      the_user_input = realloc(the_user_input, the_size_array);
      if (the_user_input == NULL) {
        exit(EXIT_FAILURE);
      }
    }
  }
  free(the_user_input);
  return NULL;
}

int my_str_len(char string[]){
  int len = 0;
  for (int i = 0;string[i]!='\0'; ++i)len++;
    return len;
}

int my_str_chr(char* str, char letter)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == letter) return true;
  }
  return false;
}

void general_inspector(char* the_secret_code, char* users_guess){
  int WellPlaced = 0, MisPlaced = 0;
  for (int i = 0; i < the_length_of_secret_code; ++i)
  {
    if (the_secret_code[i] == users_guess[i])
    {
      WellPlaced++;
    }
    else if (my_str_chr(the_secret_code, users_guess[i]) == true)
    {
      MisPlaced++;
    }
  }
  printf("Well placed pieces: %d\nMisplaced pieces: %d\n", WellPlaced, MisPlaced);
}

bool is_number_repating(int the_number, char *the_array, int the_size){
  for (int i = 0; i < the_size; ++i)
  {
    if (the_array[i] == the_number)
    {
      return true;
    }
  }
  return false;
}

//inspector gadjet :)
bool inspector(char* users_guess){ 
  if (my_str_len(users_guess) != the_length_of_secret_code)
  {
    return false;
  }
  else
  {
    for (int i = 0; i < the_length_of_secret_code; ++i)
    {
      if (!(users_guess[i] >= '0') || !(users_guess[i] <= '8') ||  is_number_repating(users_guess[i], users_guess, i))
      {
        return false;
      }
    }
    return true;
  }
}

char* the_users_guess(){
  printf("> ");
  fflush(stdout);
  char* users_guess = the_scanf();
  if (users_guess == NULL) return NULL;
  while(!inspector(users_guess)){
    printf("wrong input\n>");
    fflush(stdout);
    free(users_guess);
    users_guess = the_scanf();
  } 
  return users_guess;
}

void the_main_function(char *the_secret_code, int the_turns){
  if (!inspector(the_secret_code)){exit(1);}
  printf("\n%s\nWelcome to game mastermind\n%s\n\nWill you find the secret code?\nPlease enter a valid guess\n", the_line, the_line);
  for (int the_round = 0; the_round < the_turns; ++the_round)
  {
    printf("\n%s\nRound %d\n", the_second_line, the_round);
    char *users_guess = the_users_guess();
    if (users_guess == NULL)return;

    if (strcmp(the_secret_code, users_guess) == 0){
      printf("\n%s\nCongratz! You did it!\n%s\n", the_second_line, the_second_line);
      free(users_guess);
      exit(0);
    }else {
      general_inspector(the_secret_code, users_guess);
    }
    free(users_guess);
  }
  printf("\n%s\nSorry your turn is over :(\n\n \tGame Over\n%s", the_line, the_line); // this wasn't in instruction but I think without this point it's difficult to calculate this is a game
}

char* Randomiser(char* rand_code){
  srand(time(NULL));
  char temp;
  int i = 0;
  while (i < the_length_of_secret_code){
    temp = rand() % 9 + '0';
    if (my_str_chr(rand_code, temp) == 0){
      rand_code[i] = temp;
      i++;
    }
  }
  rand_code[the_length_of_secret_code] = '\0';
  return rand_code;
}

void sorting_function(int argc, char **argv){
  char the_secert_code[the_length_of_secret_code];
  Randomiser(the_secert_code);
  if (argc < 2){
    the_main_function(the_secert_code, 10);
  }else if (argc == 3 && (strcmp(argv[1], "-c") == 0)){
    the_main_function(argv[2], 10);
  }else if (argc == 3 && (strcmp(argv[1], "-t") == 0)){
    the_main_function(the_secert_code, atoi(argv[2]));
  }else if (argc == 5 && (strcmp(argv[1], "-t") == 0) && (strcmp(argv[3], "-c") == 0)){
    the_main_function(argv[4], atoi(argv[2]));
  }else if (argc == 5 && (strcmp(argv[1], "-c") == 0) && (strcmp(argv[3], "-t") == 0)){
    the_main_function(argv[2], atoi(argv[4]));
  }
}

int main(int argc, char **argv)
{
  sorting_function(argc, argv);
}