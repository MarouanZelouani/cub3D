#include "../includes/cub3D.h"

int fetch_data(char *str, t_game_data *data);
int check_file_name(char *str);

int parser(char *str, t_game_data *data)
{
    if (check_file_name(str))
        return (EXIT_FAILURE);
    if (fetch_data(str, data))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int check_file_name(char *str)
{
    int itr;

    itr = 0;
    if (!str || str[itr] == '\0')
        return (EXIT_FAILURE);
    while (str[itr] && str[itr] != '.')
        itr++;
    if (ft_strlen(str) == itr)
        return (EXIT_FAILURE);
    if (ft_strncmp("cub", str + itr, 3) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int is_empty_line(char *line)
{
    size_t itr;

    itr = 0;
    while (line[itr])
    {
        if (line[itr] != ' ')
            return (0);
        itr++;
    }
    return (1);
}

char *get_type_identifier (char *line)
{
    int len;
    int itr;
    char *identifier;

    itr = 0;
    len = 1;
    if (!line)
        return (NULL);
    while (line[itr] && line[itr] == ' ')
        itr++;
    while(line[itr] && line[itr] != ' ')
        len++;
    identifier = ft_substr(line, itr, len);
    if (!identifier)
        return (NULL);
    return (identifier);
}

int check_color_format(char *str)
{
    int itr;
    int count;

    itr = 0;
    count = 0;
    while (str[itr])
    {
        if (itr != 0 && str[itr] == ',' && str[itr + 1] 
            && str[itr + 1] != ',')
        {
            count++;
            itr++;
        }
        else if (ft_isdigit(str[itr]))
            itr++;
        else 
            break;
    }
    if (itr != ft_strlen(str) || count != 2)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}


int parse_color(char *str)
{
    char **split;
    int red;
    int green;
    int blue;

    if (check_color_format(str))
        return (-1);
    split = ft_split(str, ',');
    red = ft_atoi(split[0]);
    green = ft_atoi(split[1]);
    blue = ft_atoi(split[2]);
    free_strarray(split);
    if (red < 0 || green < 0 || blue < 0)
        return (-1);
    return ((red << 16) | (green << 8) | blue);
}


int check_identifier(char *identifier, char *path, t_game_data *data)
{
    if (!identifier)
        return (EXIT_FAILURE);
    if (!ft_strncmp("NO", identifier, ft_strlen(identifier)))
        data->north_texture_path = path;
    else if (!ft_strncmp("SO", identifier, ft_strlen(identifier)))
        data->south_texture_path = path;
    else if (!ft_strncmp("WE", identifier, ft_strlen(identifier)))
        data->west_texture_path = path;
    else if (!ft_strncmp("EA", identifier, ft_strlen(identifier)))
        data->east_texture_path = path;
    else if (!ft_strncmp("F", identifier, ft_strlen(identifier)))
    {
        data->floor_color = parse_color(path);
        if (data->floor_color == -1)
            return (EXIT_FAILURE);
    }
    else if (!ft_strncmp("C", identifier, ft_strlen(identifier)))
    {
        data->ceiling_color = parse_color(path);
        if (data->ceiling_color == -1)
            return (EXIT_FAILURE);
    }
    else 
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int parse_one_line(char *line, t_game_data *data)
{
    int itr;
    char *identifier;
    char *path;

    itr = 0;
    identifier = get_type_identifier(line);
    while (line[itr] && line[itr] == ' ')
        itr++;
    while (line[itr] && line[itr] != ' ')
        itr++;
    path = ft_substr(line, itr, ft_strlen(line) - itr);
    if (!path)
        return (EXIT_FAILURE);
    if (check_identifier(identifier, path, data))
        return (free(path), free(identifier), EXIT_FAILURE);
    free(identifier);
    return (EXIT_SUCCESS);
}

void fill_map(char ***map, char *tmp_map)
{
    
    return (EXIT_SUCCESS);
}

int read_map(int fd, char ***map)
{
    char *line;
    char *tmp_map;
    char *tmp;

    tmp_map = NULL;
    line = get_next_line(fd);
    while (line)
    {
        if (is_empty_line(line))
            return (free(line), EXIT_FAILURE);
        tmp = ft_strjoin(tmp_map, line);
        free(tmp_map);
        tmp_map = tmp;
        free(line);
        line = get_next_line(fd);
    }
    *map = ft_split(tmp_map, '\n');
    free(tmp_map);
    return (EXIT_SUCCESS);
}

int chech_map_element(char **map, int x, int y)
{
    if ((x == 0 || x == (sizeof(map) / sizeof(map[0])) - 1) 
        && map[x][y] == '0')
        return (EXIT_FAILURE);
    else if (map[x][y] == '0')
    {
        if (map[x - 1][y] == ' ' || (map[x + 1][y] && map[x + 1][y] == ' ') 
            || (map[x][y + 1] && map[x][y + 1] == ' '))
            return (EXIT_FAILURE);
    }
    else if (!(map[x][y] == ' ' || map[x][y] == '1'))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int map_parser(int fd, t_game_data *data)
{
    char **map;
    int x;
    int y;
    
    map = NULL;
    x = 0;
    y = 0;
    if (read_map(fd, &map))
        return (EXIT_FAILURE);
    while (map[x])
    {
        while (map[x][y])
        {
            if (chech_map_element(map, x, y))
                return (EXIT_FAILURE);
            y++;
        }
        x++;
    }
    return (EXIT_SUCCESS);
}

int fetch_data(char *str, t_game_data *data)
{
    int fd;
    char *line;
    int count;

    count = 0;
    fd = open(str, O_RDONLY, 0644);
    if (fd < 0)
    {
        perror("Failed to open the file");
        return (EXIT_FAILURE);
    }
    line = get_next_line(fd);
    while (line)
    {
        if (!is_empty_line(line))
        {
            if (parse_one_line(line, data))
                return (free(line), close(fd), EXIT_FAILURE);
            count++;
        }
        free(line);
        if (count == 6)
            break;
        line = get_next_line(fd);
    }
    if (map_parser(fd, data))
        return (close(fd), EXIT_FAILURE);
    close(fd);
    return (EXIT_SUCCESS);
}