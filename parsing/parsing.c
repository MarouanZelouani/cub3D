/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:26 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:30:27 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_string(char *line, t_parsed_data *data)
{
	if (!ft_strncmp(line, "NO ", 3) && data->north_textures == NULL)
		data->north_textures = line + 3;
	else if (!ft_strncmp(line, "SO ", 3) && data->south_textures == NULL)
		data->south_textures = line + 3;
	else if (!ft_strncmp(line, "WE ", 3) && data->west_textures == NULL)
		data->west_textures = line + 3;
	else if (!ft_strncmp(line, "EA ", 3) && data->east_textures == NULL)
		data->east_textures = line + 3;
	else
	{
		free(line);
		ft_putstr_fd("invalid file\n", 2);
		return (-1);
	}
	return (0);
}

int	get_integer(char *str, t_parsed_data *data)
{
	if (!ft_strncmp(str, "F ", 2) && data->floor_rgb == -1)
	{
		data->floor_rgb = rgb(str);
		free(str);
	}
	else if (!ft_strncmp(str, "C ", 2) && data->ceiling_rgb == -1)
	{
		data->ceiling_rgb = rgb(str);
		free(str);
	}
	else
	{
		free(str);
		ft_putstr_fd("invalid file\n", 2);
		return (-1);
	}
	if (data->floor_rgb == -2 || data->ceiling_rgb == -2)
		return (-1);
	return (0);
}

int	parse(char *str, t_parsed_data *data)
{
	char		*line;
	int			fd;
	t_map_list	*head;
	t_map_list	*tail;

	head = NULL;
	tail = NULL;
	if (initialize(data, str, &fd) == -1)
		return (-1);
	if (data_p(data, &line, fd) == -1)
		return (-1);
	while (line)
	{
		append_map_list(line, &head, &tail);
		if (head == NULL)
			return (-1);
		line = get_next_line(fd, 0);
	}
	if (check_map_validity(head) == -1 || get_map(data, head) == -1)
		return (free_map_list(head), -1);
	return (free_map_list(head), get_coords(data), 0);
}
