/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:38 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/24 08:40:22 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	set_movement_logic(t_args *args, t_pair *movement_vec);

void	check_key_pressed(t_args *args)
{
	t_pair	next_pos;
	t_pair	movement_vec;

	movement_vec.x = cos(args->player.angle);
	movement_vec.y = sin(args->player.angle);
	if (args->keys_pressed[5])
		args->player.angle += 0.007;
	else if (args->keys_pressed[4])
		args->player.angle -= 0.007;
	if (set_movement_logic(args, &movement_vec))
	{
		next_pos.x = args->player.cords.x + movement_vec.x * PLAYER_SPEED;
		next_pos.y = args->player.cords.y + movement_vec.y * PLAYER_SPEED;
		if (!collision(next_pos.x, next_pos.y, 0.1, args))
			args->player.cords = (t_pair){next_pos.x, next_pos.y};
		else
		{
			if (!collision(next_pos.x, args->player.cords.y, 0.1, args))
				args->player.cords.x = next_pos.x;
			else if (!collision(args->player.cords.x, next_pos.y, 0.1, args))
				args->player.cords.y = next_pos.y;
		}
	}
}

static int	set_movement_logic(t_args *args, t_pair *movement_vec)
{
	double	tmp;

	if (args->keys_pressed[0])
		return (1);
	else if (args->keys_pressed[1])
	{
		movement_vec->x *= -1;
		movement_vec->y *= -1;
		return (1);
	}
	else if (args->keys_pressed[2])
	{
		tmp = movement_vec->y;
		movement_vec->y = -movement_vec->x;
		movement_vec->x = tmp;
		return (1);
	}
	else if (args->keys_pressed[3])
	{
		tmp = movement_vec->x;
		movement_vec->x = -movement_vec->y;
		movement_vec->y = tmp;
		return (1);
	}
	return (0);
}
