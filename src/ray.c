/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:42 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:42:38 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static t_texture	*get_wall_tex(t_args *args, t_ray *ray);

void	project_3d_map(t_args *args)
{
	t_ray	ray;
	int		index;

	index = 0;
	ray.side = 0;
	ray.angle_step = FOV / WIDTH;
	while (index < WIDTH)
	{
		init_ray_data(args, &ray, index);
		get_ray_lenght(args, &ray);
		draw_wall_slice(args, &ray, get_wall_tex(args, &ray), index);
		index++;
	}
}

void	init_ray_data(t_args *args, t_ray *ray, int ray_number)
{
	ray->angle_step = FOV / WIDTH;
	ray->angle = (args->player.angle - (FOV / 2)) + ray_number
		* ray->angle_step;
	ray->dir.x = cos(ray->angle);
	ray->dir.y = sin(ray->angle);
	ray->map_pos_x = (int)(args->player.cords.x / TILE_HSIZE);
	ray->map_pos_y = (int)(args->player.cords.y / TILE_HSIZE);
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
}

static t_texture	*get_wall_tex(t_args *args, t_ray *ray)
{
	t_texture	*tex;

	tex = NULL;
	if (ray->side == 0)
	{
		if (ray->step.x > 0)
			tex = &args->e_tex;
		else
			tex = &args->w_tex;
	}
	else
	{
		if (ray->step.y > 0)
			tex = &args->s_tex;
		else
			tex = &args->n_tex;
	}
	return (tex);
}
