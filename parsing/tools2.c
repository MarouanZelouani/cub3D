/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:48 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:30:49 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_file_extension(char *filename, char *extension)
{
	int	i;
	int	len;

	i = 0;
	if (filename == NULL || extension == NULL)
		return (-1);
	len = (int)ft_strlen(filename);
	while (len != 0 && filename[len] != '.')
		len--;
	if (len == 0)
		return (-1);
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

int	check_ex(t_parsed_data *data)
{
	return (check_file_extension(data->north_textures, "xpm") == -1
		|| check_file_extension(data->south_textures, "xpm") == -1
		|| check_file_extension(data->west_textures, "xpm") == -1
		|| check_file_extension(data->east_textures, "xpm") == -1);
}

void	free_str(char **str, int a)
{
	free((*str) - a);
	*str = NULL;
}

void	free_map(t_parsed_data *data)
{
	int	i;

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

void	free_data(t_parsed_data *data)
{
	get_next_line(5, 1);
	if (data->north_textures)
		free_str(&(data->north_textures), 3);
	if (data->south_textures)
		free_str(&(data->south_textures), 3);
	if (data->west_textures)
		free_str(&(data->west_textures), 3);
	if (data->east_textures)
		free_str(&(data->east_textures), 3);
	free_map(data);
}
