/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:17 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:30:18 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_map(t_parsed_data *data, t_map_list *node)
{
	int	len;
	int	size;
	int	rows;
	int	i;

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

void	write_to_map(t_parsed_data *data, t_map_list *node, int i, int *j)
{
	if (data->map[i])
	{
		while (node->str[*j])
		{
			if (node->str[*j] == 'N' || node->str[*j] == 'S'
				|| node->str[*j] == 'W' || node->str[*j] == 'E')
			{
				data->map[i][*j] = '0';
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

void	fill(t_parsed_data *data, int j, int i, int len)
{
	while (j < len)
	{
		data->map[i][j] = ' ';
		j++;
	}
	data->map[i][j] = 0;
}
