/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:31 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:30:32 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	get_data(char *line, t_parsed_data *data)
{
	if (is_a_string(line))
		return (get_string(line, data));
	else if (is_an_integer(line))
		return (get_integer(line, data));
	else
	{
		free(line);
		ft_putstr_fd("invalid file\n", 2);
		return (-1);
	}
	return (0);
}

static void	init(t_parsed_data *data)
{
	data->north_textures = NULL;
	data->south_textures = NULL;
	data->west_textures = NULL;
	data->east_textures = NULL;
	data->floor_rgb = -1;
	data->ceiling_rgb = -1;
	data->map = NULL;
	data->x = 0;
	data->y = 0;
	data->direction = 0;
}

int	initialize(t_parsed_data *data, char *str, int *fd)
{
	init(data);
	if (check_file_extension(str, "cub") == -1)
		return (ft_putstr_fd("invalid filename\n", 2), -1);
	*fd = open(str, O_RDONLY);
	if (*fd < 0)
		return (ft_putstr_fd("invalid file\n", 2), -1);
	return (0);
}

int	data_p(t_parsed_data *data, char **line, int fd)
{
	while (done_parsing_data(data))
	{
		*line = get_next_line(fd, 0);
		if (!(*line))
			return (ft_putstr_fd("invalid file\n", 2), -1);
		if ((*line)[0] == '\n')
		{
			free(*line);
			continue ;
		}
		if (get_data(*line, data) == -1)
			return (-1);
	}
	trim(data);
	if (check_ex(data))
		return (ft_putstr_fd("invalid textures files\n", 2), -1);
	*line = get_next_line(fd, 0);
	while (*line && (*line)[0] == '\n')
	{
		free(*line);
		*line = get_next_line(fd, 0);
	}
	return (0);
}
