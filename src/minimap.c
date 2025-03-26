/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:35 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:41:50 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	draw_rays_minimap(t_args *args);
static void	render_map_box(t_args *args);
static void	render_map_tile(t_args *args, int mini_x, int mini_y, int flag);

void	render_minimap(t_args *args)
{
	t_pair	rel;
	int		mini_x;
	int		mini_y;
	int		map_x;
	int		map_y;

	map_y = -1;
	render_map_box(args);
	while (++map_y < args->p_data->h)
	{
		map_x = -1;
		while (++map_x < args->p_data->w)
		{
			rel.x = (map_x * TILE_HSIZE - args->player.cords.x) * MINIMAP_SCALE;
			rel.y = (map_y * TILE_HSIZE - args->player.cords.y) * MINIMAP_SCALE;
			mini_x = (MINIMAP_W / 2) + (int)rel.x;
			mini_y = (MINIMAP_H / 2) + (int)rel.y;
			if (args->p_data->map[map_y][map_x] == '1')
				render_map_tile(args, mini_x, mini_y, 1);
			else
				render_map_tile(args, mini_x, mini_y, 0);
		}
	}
	draw_rays_minimap(args);
}

static void	draw_rays_minimap(t_args *args)
{
	t_ray	ray;
	int		t;
	int		index;
	int		rayxy[2];
	int		m[2];

	index = -1;
	while (++index < WIDTH)
	{
		init_ray_data(args, &ray, index);
		get_ray_lenght(args, &ray);
		ray.lenght *= TILE_HSIZE;
		t = -1;
		while (++t < (int)ray.lenght)
		{
			rayxy[0] = (int)((args->player.cords.x) + t * ray.dir.x);
			rayxy[1] = (int)((args->player.cords.y) + t * ray.dir.y);
			m[0] = (MINIMAP_W / 2) + (int)((rayxy[0]
						- args->player.cords.x) * MINIMAP_SCALE);
			m[1] = (MINIMAP_H / 2) + (int)((rayxy[1]
						- args->player.cords.y) * MINIMAP_SCALE);
			if (m[0] >= 0 && m[0] < MINIMAP_W && m[1] >= 0 && m[1] < MINIMAP_H)
				my_mlx_pixel_put(&args->img, m[0], m[1], RAYS_COLOR);
		}
	}
}

static void	render_map_box(t_args *args)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_H)
	{
		x = 0;
		while (x < MINIMAP_W)
		{
			if (x >= 0 || x < WIDTH || y >= 0 || y < HEIGHT)
				my_mlx_pixel_put(&args->img, x, y, MAP_BOX_COLOR);
			x++;
		}
		y++;
	}
}

static void	render_map_tile(t_args *args, int mini_x, int mini_y, int flag)
{
	int	act_x;
	int	act_y;
	int	x;
	int	y;

	y = -1;
	while (++y < MAP_TILE_SIZE)
	{
		x = -1;
		while (++x < MAP_TILE_SIZE)
		{
			act_x = mini_x + x;
			act_y = mini_y + y;
			if (act_x >= 0 && act_x <= MINIMAP_W && act_y >= 0
				&& act_y <= MINIMAP_H)
			{
				if (flag == 1)
					my_mlx_pixel_put(&args->img, mini_x + x, mini_y + y,
						MAP_TILE_COLOR);
				else
					my_mlx_pixel_put(&args->img, mini_x + x, mini_y + y,
						MAP_BOX_COLOR);
			}
		}
	}
}
