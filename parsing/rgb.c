#include "../includes/cub3D.h"

static int checker(char *str)
{
  int i;
  int j;
  int number_of_digits;

  i = 2;
  j = 0;
  while (j < 3)
  {
    if (!str[i] || str[i] == '\n')
      return (ft_putstr_fd("invalid rgb value\n", 2), -1);
    number_of_digits = 0;
    while (str[i] && str[i] != ',' && str[i] != '\n')
    {
      if (str[i] > '9' || str[i] < '0' || number_of_digits > 2)
        return (ft_putstr_fd("invalid rgb value\n", 2), -1);
      i++;
      number_of_digits++;
    }
    if(str[i] && str[i] == ',' && j != 2)
       i++;
    j++;
  }
  if (str[i] && str[i] != '\n')
    return (ft_putstr_fd("invalid rgb value\n", 2), -1);
  return (0);
}

static int get_value(char *str, int flag)
{
  static int i = 2;
  int j;
  char holder[4];

  j = 0;
  while (str[i] && str[i] != ',')
  {
    if (str[i] == ' ' || str[i] == '\t')
      i++;
    else
      holder[j++] = str[i++];
  }
  if (str[i] == ',' && (str[i + 1] == ','))
    return (-1);
  i++;
  holder[j] = 0;
  if (flag)
    i = 2;
  return (ft_atoi(holder));
}

int rgb(char *str)
{
  int r;
  int g;
  int b;

  if (checker(str) == -1)
    return (-2);
  r = get_value(str, 0);
  g = get_value(str, 0);
  b = get_value(str, 1);
  if (r == -1  || g == -1 || b == -1)
    return (ft_putstr_fd("invalid rgb value\n", 2), -2);
  if (r > 255 || g > 255 || b > 255 ||\
      r < 0 || g < 0 || b < 0)
  {
    ft_putstr_fd("invalid rgb value\n", 2);
    return (-2);
  }
  return ((r<<16) | (g<<8) | b);
}
