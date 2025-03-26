/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:52 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:30:53 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_coords(t_parsed_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
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

void	free_map_list(t_map_list *head)
{
	t_map_list	*next;

	if (!head)
		return ;
	next = head->next;
	if (next == NULL)
	{
		free(head->str);
		free(head);
	}
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

void	cut(char **str)
{
	int	i;

	i = ft_strlen(*str) - 1;
	if ((*str)[i] == '\n')
		i--;
	while ((*str)[i] == ' ' || (*str)[i] == '\t')
		i--;
	(*str)[i + 1] = '\0';
}

void	trim(t_parsed_data *data)
{
	cut(&(data->north_textures));
	cut(&(data->south_textures));
	cut(&(data->west_textures));
	cut(&(data->east_textures));
}
