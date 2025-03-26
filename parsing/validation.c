/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:56 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:30:57 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	last_char(t_parsed_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
			j++;
		if (data->map[i][j - 1] == '0')
			return (-1);
		i++;
	}
	return (0);
}

int	validation(t_parsed_data *data)
{
	if (data->map[0] == NULL)
		return (-1);
	if (ft_strlen(data->map[0]) < 3)
		return (-1);
	if (last_char(data) == -1)
		return (-1);
	if (space_checker(data) == -1 || zero_checker(data) == -1)
		return (-1);
	return (0);
}
