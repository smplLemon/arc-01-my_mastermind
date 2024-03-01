#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

int my_strlen(char str[]){
  int i = 0;
  while (str[i]){
    i++;
  }
  return i;
}

int includes(char array[], char c){
  int len = my_strlen(array);
  for (int i = 0; i < len; i++){
    if (array[i] == c){
      return 1;
    }
  }
  return 0;
}

char *my_strcpy(char *str_1, char *str_2){
  int i = 0;
  while (str_2[i] != '\0'){
    str_1[i] = str_2[i];
    i++;
  }
  str_1[i] = '\0';
  return str_1;
}

char *my_random(){
  time_t t;
  char *array = calloc(5, sizeof(char));
  srand(time(&t));
  int i = 0;
  char randomed = '0';
  while (i < 4){
    randomed = rand() % 9 + 48;
    if (includes(array, randomed) == 1){
       continue;
    }
    array[i++] = randomed;
  }
  return array;
}

int my_strcmp(char *s1, char *s2){
  int i = 0;
  if (my_strlen(s1) > my_strlen(s2)) return 1;
    if (my_strlen(s1) < my_strlen(s2)) return -1;
  while (my_strlen(s1) > i){
    if (s1[i] != s2[i]){
      return s1[i] - s2[i];
    }
    i++;
  }
  return 0;
}

void user_settings(int argc, char **argv, char **code, char **attemp_2){
  char attemp[37] = "10";
  *code = malloc(sizeof(char) * 5);
  my_strcpy(*code, my_random());
  for (int i = 0; i < argc; i++) {
      if (my_strcmp(argv[i], "-c") == 0){
         my_strcpy(*code, argv[i + 1]);
      }else if (my_strcmp(argv[i], "-t") == 0){
         my_strcpy(attemp, argv[i + 1]);
    }
  }
  *attemp_2 = malloc(sizeof(char) * (my_strlen(attemp) + 1));
  my_strcpy(*attemp_2, attemp);
}

char *my_read(){
  char *buff = calloc(2, sizeof(char));
  write(1, ">", 1);
  int i = 0;
  char c;
  while(read(0, &c , 1)){
      if (c == '\n') {
          return buff;
      }
    buff = realloc(buff,i + 1);   
    buff[i++] = c;
  }
  return "EOT";
}

int well_place(char *code, char *user_code){
  int count = 0;
  for (int i = 0; i < 4; i++){
    if (code[i] == user_code[i]){
      count++;
    }
  }
  return count;
}

int miss_place(char *code, char *user_code){
  int count = 0;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if (code[i] == user_code[j] && code[i] != user_code[i]){
        count++;
      }
    }
  }
  return count;
}

int wrong_input(char *user_code){
  for(int p = 0; p < 4; p++){
      for(int j = p + 1; j < 4; j++) {
      if(user_code[p] == user_code[j]){
        return 0;
      }
    }
  }
  int i = 0;
  while (i < 4){
    if (user_code[i] < 48 || user_code[i] > 56 ){
      return 0;
    }
    i++; 
  }
  return 1;
}

int my_atoi(char *attemp){
 int res = 0;
  for (int i = 0; attemp[i] != '\0'; i++){
     res = res * 10 + attemp[i] - '0';
  }
    return res;
}

int my_call(char *code , char* user_code){
  int well = well_place(code, user_code);
  int miss = miss_place(code, user_code);
    if(well == 4){
      printf("Congratz! You did it!\n");
     return 1;
    }
    else {
      printf("Well placed pieces: %d\n", well);
      printf("Misplaced pieces: %d\n---\n", miss);
    }
    
return 0;
}

void main_func(int argc, char **argv){
  char *code, *attemp, *user_code = calloc(4, sizeof(char));
  user_settings(argc, argv, &code, &attemp);
  int attemp_1 = my_atoi(attemp), i = 0;
  while (i < attemp_1){
    printf("Round: %d\n", i);
    user_code = my_read();
      if(my_strcmp(user_code,"EOT") == 0){
        return;
      }else if (wrong_input(user_code) == 0 || my_strlen(user_code) > 4){
          printf("Wrong input!\n");
          continue;
      }
    int res = my_call(code, user_code);
    if(res != 0 ){
        return;
    } 
    i++;
  }
  printf("\nYuo lose, let's try again\n");
}


int main(int argc, char *argv[]){
  printf("Will you find the secret code?\nPlease enter a valid guess\n");
  main_func(argc, argv); 
  return 0;
}