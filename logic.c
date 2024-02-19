#include <my_mastermind.h>

char *random_code()
{
  char *code = (char *)malloc(sizeof(char) * 5);
  code[4] = '\0';
  srand(time(0));
  for (int i = 0; i < 4; i++)
  {
    code[i] = (rand() % 8) + 48;
  }
  return code;
}

char *get_input()
{
  char *code = (char *)malloc(sizeof(char) * 5);
  str_fill(code, '\0', 4);
  char sym;
  int i = 0;

  while (read(0, &sym, 1) > 0)
  {
    if (i < 4)
    {
      code[i] = sym;
    }
    if (sym == '\n')
    {
      break;
    }
    i++;
  }
  if (i > 4)
  {
    code[0] = '\0';
    return code;
  }
  return code;
}

int check_code(char *code)
{
  if (my_strlen(code) != 4)
  {
    return -1;
  }
  while (*code)
  {
    if (!(*code > 47 && *code < 56))
    {
      return -1;
    }
    code++;
  }
  return 0;
}

char *get_valid_input()
{
  char *code = NULL;
  while (1)
  {
    code = get_input();
    if (check_code(code) == 0)
    {
      break;
    }
    else
    {
      free(code);
      printf("Wrong input!\n");
    }
  }
  return code;
}

void end_game_message(int game_status)
{
  if (game_status == WIN)
  {
    printf("Congratz! You did it!\n");
  }
  else
  {
    printf("You've lost! Better luck next time.\n");
  }
}

int well_placed(char *input, char *code)
{
  int well_placed = 0;
  while (*input)
  {
    if (*input == *code)
    {
      well_placed += 1;
    }
    input++;
    code++;
  }
  return well_placed;
}

int misplaced(char *input, char *code, int well)
{
  int mis = 0;
  int input_arr[8];
  int code_arr[8];
  for (int i = 0; i < 8; i++)
  {
    input_arr[i] = 0;
    code_arr[i] = 0;
  }
  for (int i = 0; i < 4; i++)
  {
    input_arr[input[i] - 48] += 1;
    code_arr[code[i] - 48] += 1;
  }
  for (int i = 0; i < 8; i++)
  {
    if (input_arr[i] != 0 && code_arr[i] != 0)
    {
      if (input_arr[i] > code_arr[i])
      {
        mis += code_arr[i];
      }
      else
      {
        mis += input_arr[i];
      }
    }
  }
  return (mis - well);
}

void print_well_mis(int well, int mis)
{
  printf("Well placed pieces: %d\n", well);
  printf("Misplaced pieces: %d\n", mis);
}

int mastermind_logic(char *player_input, char *code)
{
  int well = 0;
  int mis = 0;

  if (my_strcmp(player_input, code) == 0)
  {
    free(player_input);
    return WIN;
  }
  well = well_placed(player_input, code);
  mis = misplaced(player_input, code, well);
  print_well_mis(well, mis);
  free(player_input);
  return ONGOING;
}
