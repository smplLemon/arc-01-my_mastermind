#include <my_mastermind.h>

int my_strlen(char *str)
{
  int count = 0;
  while (*str)
  {
    str++;
    count++;
  }
  return count;
}

int check_nbr(char *str)
{
  while (*str)
  {
    if (!(*str > 47 && *str < 58))
    {
      return -1;
    }
    str++;
  }
  return 0;
}

char *my_strdup(char *str)
{
  int len = my_strlen(str);
  char *dup = (char *)malloc(sizeof(char) * (len + 1));
  int i;
  for (i = 0; i < len; i++)
  {
    dup[i] = str[i];
  }
  dup[i] = '\0';
  return dup;
}

void str_fill(char *str, char fill, int len)
{
  for (int i = 0; i < len; i++)
  {
    str[i] = fill;
  }
  str[len] = '\0';
}

int my_strcmp(char *str1, char *str2)
{
  while (*str1 || *str2)
  {
    if (*str1 > *str2)
    {
      return 1;
    }
    else if (*str1 < *str2)
    {
      return -1;
    }
    str1++;
    str2++;
  }
  return 0;
}