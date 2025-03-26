/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:59 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:31:00 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	zero_checker(t_parsed_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
			{
				if ((i == 0) || (data->map[i + 1] == NULL) || (j == 0)
					|| (data->map[i][j + 1] == 0))
					return (ft_putstr_fd("no!\n", 2), -1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
