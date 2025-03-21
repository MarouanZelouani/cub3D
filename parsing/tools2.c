#include "../includes/cub3D.h"

void get_coords(t_parsed_data *data)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (data->map[i])
  {
    while (data->map[i][j])
    {
      if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||\
          data->map[i][j] == 'E' || data->map[i][j] == 'W')
      {
        data->x = j;
        data->y = i;
        data->direction = data->map[i][j];
        return ;
      }
      j++;
    }
    i++;
  }
}

// 0 if valid -1 if invalid
int check_file_extension(char *filename, char *extension)
{
  int i;
  int len;

  i = 0;
  if (filename == NULL || extension == NULL)
    return (-1);
  len = (int)ft_strlen(filename);
  while(len != 0 && filename[len] != '.')
    len--;
  if (len == 0)
    return -1;
  len++;
  while (filename[len])
  {
    if (filename[len] != extension[i])
      return (-1);
    len++;
    i++;
  }
  if (extension[i])
    return (-1);
  return (0);
}

int check_ex(t_parsed_data *data)
{
  return (check_file_extension(data->north_textures, "xpm") == -1 ||\
      check_file_extension(data->south_textures, "xpm") == -1 ||\
      check_file_extension(data->west_textures, "xpm") == -1 ||\
      check_file_extension(data->east_textures, "xpm") == -1);
}

void free_str(char **str)
{
  free((*str) - 3);
  *str = NULL;
}

void free_map(t_parsed_data *data)
{
  int i;
  
  i = 0;
  if (data->map != NULL)
  {
    while (data->map[i] != NULL)
    {
      free(data->map[i]);
      data->map[i] = NULL;
      i++;
    }
    free(data->map);
    data->map = NULL;
  }
}

void free_data(t_parsed_data *data)
{
  if (data->north_textures)
    free_str(&(data->north_textures));
  if (data->south_textures)
    free_str(&(data->south_textures));
  if (data->west_textures)
    free_str(&(data->west_textures));
  if (data->east_textures)
    free_str(&(data->east_textures));
  free_map(data);
}

void free_map_list(t_map_list *head)
{
  t_map_list *next;

  if (!head)
    return ;
  next = head->next;
  while (next)
  {
    next = head->next;
    if ((head->str) != NULL)
    {
      free(head->str);
      head->str = NULL;
    }
    free(head);
    head = next;
  }
}

void cut(char **str)
{
  int i;

  i = ft_strlen(*str) - 1;
  if ((*str)[i] == '\n')
    i--;
  while ((*str)[i] == ' ' || (*str)[i] == '\t')
    i--;
  ft_putchar_fd((*str)[i], 2);
  ft_putchar_fd('\n', 2);
  (*str)[i + 1] = '\0';
}

void trim(t_parsed_data *data)
{
  cut(&(data->north_textures));
  cut(&(data->south_textures));
  cut(&(data->west_textures));
  cut(&(data->east_textures));
}
