#include <my_mastermind.h>

char check_option(char *str)
{
  if (str[0] != '-')
  {
    return 0;
  }
  if ((str[1] == 'c' || str[1] == 't') && str[2] == '\0')
  {
    return str[1];
  }
  return 0;
}

int set_option_c(char **code, char *str)
{
  if (!str)
  {
    return -1;
  }
  if (my_strlen(str) == 4 && check_nbr(str) == 0)
  {
    free(*code);
    *code = my_strdup(str);
    return 0;
  }
  return -1;
}

int set_option_t(int *attempts, char *str)
{
  if (!str)
  {
    return -1;
  }
  if ((*attempts = atoi(str)) < 1)
  {
    return -1;
  }
  return 0;
}

int handle_option(char option, int *attempts, char **code, char *str)
{
  if (option == 'c')
  {
    return set_option_c(code, str);
  }
  else
  {
    return set_option_t(attempts, str);
  }
}

int handle_flags(int *attempts, char **code, char **argv)
{
  char option = '\0';

  while (*argv)
  {
    if ((option = check_option(*argv)))
    {
      argv++;
      if ((handle_option(option, attempts, code, *argv)) == 0)
      {
        argv++;
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
  return 0;
}