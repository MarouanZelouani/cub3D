#include "../includes/cub3D.h"

int is_a_string(char *str)
{
  return (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3) || !ft_strncmp(str, "WE ", 3) || !ft_strncmp(str, "EA ", 3));
}

int is_an_integer(char *str)
{
  return (!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2));
}

int done_parsing_data(t_parsed_data *data)
{
  return (data->north_textures == NULL || data->south_textures == NULL\
      || data->west_textures == NULL || data->east_textures == NULL ||\
      data->floor_rgb == -1 || data->ceiling_rgb == -1);
}
