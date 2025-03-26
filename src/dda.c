/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:21 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/24 09:12:19 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	calculate_ray_lenght(t_ray *ray, t_args *args);

void	dda(t_ray *ray, t_args *args)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos_x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos_y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map_pos_x < 0 || ray->map_pos_x >= args->p_data->w
			|| ray->map_pos_y < 0 || ray->map_pos_y >= args->p_data->h)
			break ;
		if (args->p_data->map[ray->map_pos_y][ray->map_pos_x] == '1')
			break ;
	}
}

void	get_ray_lenght(t_args *args, t_ray *ray, int ray_number)
{
	init_ray_data(args, ray, ray_number);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (args->player.cords.x / TILE_HSIZE - ray->map_pos_x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos_x + 1.0 - args->player.cords.x
				/ TILE_HSIZE) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (args->player.cords.y / TILE_HSIZE - ray->map_pos_y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos_y + 1.0 - args->player.cords.y
				/ TILE_HSIZE) * ray->delta_dist.y;
	}
	calculate_ray_lenght(ray, args);
}

static void	calculate_ray_lenght(t_ray *ray, t_args *args)
{
	dda(ray, args);
	if (ray->side == 0)
		ray->lenght = (ray->map_pos_x - (args->player.cords.x / TILE_HSIZE) + (1
					- ray->step.x) / 2) / ray->dir.x;
	else
		ray->lenght = (ray->map_pos_y - (args->player.cords.y / TILE_HSIZE) + (1
					- ray->step.y) / 2) / ray->dir.y;
}
