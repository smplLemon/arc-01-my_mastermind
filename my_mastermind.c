#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int values(char *main_in) {
  int i = 0;
  while (main_in[i] != '\0') {
    i++;
  }
  return i;
}

char *strln(char *param_1, char *param_2) {
  int i = 0;
  for (; param_2[i] != '\0'; i++) {
    param_1[i] = param_2[i];
  }
  param_1[i] = '\0';
  return param_1;
}

int new_strchr(char *numbers, char num) {
  for (int i = 0; numbers[i] != '\0'; i++) {
    if (numbers[i] == num) {
      return i;
    }
  }
  return -1;
}

int new_input(char param_1) {
  if (param_1 >= '0' && param_1 <= '8') {
    return 1;
  }
  return 0;
}

int bubble(char *main_in) {
  int last = values(main_in);
  for (int i = 0; i < last - 1; i++) {
    for (int j = i + 1; j < last; j++) {
      if (main_in[i] == main_in[j]) {
        return 1;
      }
    }
  }
  return 0;
}

int nested(char *main_in, char *numbeses) {
  int b = 0;
  int c = 0;
  for (int i = 0; main_in[i] != '\0'; i++) {
    for (int j = 0; numbeses[j] != '\0'; j++) {
      if (main_in[i] == numbeses[j] && i != j) {
        c++;
      } else if (main_in[i] == numbeses[j]) {
        b++;
      }
    }
  }
  if (b == 4) {
    printf("Congratz! You did it!\n");
    return 1;
  }

  printf("Well placed numbers: %d\nMisplaced numbers: %d\n", b, c);
  return 0;
}

char *inrct() {
  int i = 0;
  char j;
  char *inclusion = malloc(6);
  write(1, ">", 1);
  while (read(0, &j, 1)) {
    if (j == '\n') {
      inclusion[i] = '\0';
      return inclusion;
    }
    inclusion[i++] = j;
  }
  return "stop";
}

char *numbers() {
  int i = 0;
  char *numbers = malloc(sizeof(char) * 5);
  numbers[4] = '\0';
  char num;
  while (i < 4) {
    num = rand() % 9 + 48;
    if (new_strchr(numbers, num) == -1) {
      numbers[i] = num;
      i++;
    }
  }
  return numbers;
}

int error(char *main_in) {
  int len = values(main_in);
  int i = 0;
  if ((len != 4) || (bubble(main_in) == 1)) {
    printf("Wrong input!\n");
    return 1;
  }
  while (i < len) {
    if ((new_input(main_in[i]) == 0)) {
      printf("Wrong input!\n");
      return 1;
    }
    i++;
  }
  return 0;
}

void begin(int round, char *numbeses) {
  printf("Will you find the secret code?\n");
  printf("Please enter a valid guess\n");
  char *input_value;
  int flag = 0;
  int i = 0;
  while (i < round) {
    printf("---\n");
    printf("Round %d\n", i);
    if (strcmp(input_value = inrct(), "stop") == 0)
      return;
    flag = error(input_value);
    if (flag == 0) {
      if (1 == nested(input_value, numbeses)) {
        return;
      }
      i++;
    }
  }

  if (flag == 0)
  {
    exit(0);
  }
  
}

void replace(int argc, char **argv) {
  int i = 1;
  int round = 10;
  char *numbeses = numbers();
  while (i < argc) {
    if (strcmp(argv[i], "-c") == 0) {
      numbeses = argv[i + 1];
      i += 2;
    } else if (strcmp(argv[i], "-t") ==0) {
      round = atoi(argv[i + 1]);
      i += 2;
    }
  }
  begin(round, numbeses);
}

int main(int argc, char **argv) {
  replace(argc, argv);
  return 0;
}