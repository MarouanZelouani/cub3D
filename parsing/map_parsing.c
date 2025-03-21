#include "../includes/cub3D.h"

void append_map_list(char *line, t_map_list **head, t_map_list **tail)
{
  t_map_list *node;

  node = ft_calloc(sizeof(t_map_list), 1);
  if (node == NULL)
    return ;
  node->str = line;
  node->next = NULL;
  if (*head == NULL)
  {
    *head = node;
    *tail = node;
  }
  else
  {
    (*tail)->next = node;
    *tail = node;
  }
}

static int check_invalid_characters(char *str, int *number_of_players)
{
  int i = 0;
  if (str[i] && str[i] == '\n')
    return (-1);
  while (str[i])
  {
    if (str[i] != '1' && str[i] != '0' &&\
        str[i] != 'W' && str[i] != 'S' &&\
        str[i] != 'E' && str[i] != 'N' &&\
        str[i] != ' ' && str[i] != '\n')
      return (-1);
    if (str[i] == 'W' || str[i] == 'N' ||\
        str[i] == 'E' || str[i] == 'S')
        (*number_of_players)++;
    i++;
   }
  return (0);
}

int check_map_validity(t_map_list *head)
{
  t_map_list *tmp;
  int number_of_players;

  tmp = head;
  number_of_players = 0;
  while (tmp)
  {
    if (check_invalid_characters(tmp->str, &number_of_players) == -1)
      return (ft_putstr_fd("invalid map\n", 2), -1);
    tmp = tmp->next;
  }
  if (number_of_players != 1)
    return (ft_putstr_fd("invalid map\n", 2), -1);
  return (0);
}

static int get_size(t_map_list *node, int *len, int *rows)
{
  int size;
  int longest;
  t_map_list *tmp;

  size = 0;
  longest = 0;
  tmp = node;
  while (tmp)
  {
    size++;
    (*rows)++;
    if (longest < (int)ft_strlen(tmp->str) - 1)
      longest = (int)ft_strlen(tmp->str) - 1;
    tmp = tmp->next;
  }
  *len = longest;
  return (longest * (size + 1));
}

void write_to_map(t_parsed_data *data, t_map_list *node, int i, int *j)
{
  if (data->map[i])
  {
    while (node->str[*j])
    {
      if (node->str[*j] == 'N' || node->str[*j] == 'S' ||\
          node->str[*j] == 'W' || node->str[*j] == 'E')
        {
          data->map[i][*j] = '0'; 
          // hadchi ra zedto
          data->direction = node->str[*j];
          data->x = i; 
          data->y = *j;  
        }
      else if (node->str[*j] == '\n')
        return ;
      else
        data->map[i][*j] = node->str[*j];
      (*j)++;
    }
  }
}

void fill(t_parsed_data *data, int j, int i, int len)
{
  while (j < len)
  {
    data->map[i][j] = ' ';
    j++;
  }
  data->map[i][j] = 0;
}

void fill_map(t_parsed_data *data, t_map_list *node, int len)
{
  t_map_list *tmp;
  int i;
  int j;
  
  tmp = node;
  i = 0;
  j = 0;
  while (tmp)
  {
    j = 0;
    write_to_map(data, tmp, i, &j);
    fill(data, j, i, len);
    i++;
    tmp = tmp->next;
  }
}

int get_map(t_parsed_data *data, t_map_list *node)
{
  int len;
  int size;
  int rows;
  int i;

  i = 0;
  len = 0;
  rows = 0;
  size = get_size(node, &len, &rows);
  data->map = ft_calloc(size, sizeof(char *));
  if (data->map == NULL)
    return (ft_putstr_fd("fatal error\n", 2), -1);
  data->map[rows - 1] = NULL;
  while (i < rows)
  {
    data->map[i] = ft_calloc(len + 1, sizeof(char));
    if (data->map[i++] == NULL)
      return (ft_putstr_fd("fatal error\n", 2), -1);
  }
  fill_map(data, node, len);
  data->h = rows;
  data->w = len;
  return (0);
}
