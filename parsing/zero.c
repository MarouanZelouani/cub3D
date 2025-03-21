#include "../includes/cub3D.h"

int zero_checker(t_parsed_data *data)
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
      if (data->map[i][j] == '0')
      {
        if ((i == 0 ) ||\
            (data->map[i + 1] == NULL) ||\
            (j == 0) ||\
            (data->map[i][j + 1] == 0)
            )
          return (ft_putstr_fd("hhhno\n", 2), -1);
      }
      j++;
    }
    i++;
  }
  return (0);
}
