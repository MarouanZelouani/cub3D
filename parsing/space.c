#include "../includes/cub3D.h"

static int up(t_parsed_data *data, int i, int j)
{
  return (data->map[i - 1][j] != ' ' && data->map[i - 1][j] != '1');
}

static int down(t_parsed_data *data, int i, int j)
{
  return (data->map[i + 1][j] != ' ' && data->map[i + 1][j] != '1');
}

static int left(t_parsed_data *data, int i, int j)
{
  return (data->map[i][j - 1] != ' ' && data->map[i][j - 1] != '1');
}

static int right(t_parsed_data *data, int i, int j)
{
  return (data->map[i][j + 1] != ' ' && data->map[i][j + 1] != '1');
}

int space_checker(t_parsed_data *data)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (data->map[i])
  {
    j = 0;
    while (data->map[i][j])
    {
      if (data->map[i][j] == ' ')
      {
        if ((i != 0 && up(data, i, j)) ||\
            (data->map[i + 1] != NULL && down(data, i, j)) ||\
            (j != 0 && left(data, i, j)) ||\
            (data->map[i][j + 1] != 0 && right(data, i, j))
            )
          return (ft_putstr_fd("grrno\n", 2), -1);
      }
      j++;
    }
    i++;
  }
  return (0);
}
