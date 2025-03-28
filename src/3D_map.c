/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:07 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/24 08:31:23 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_data(t_args *args, t_wall_slice *data, t_ray *ray,
		t_texture *tex)
{
	data->wall_h = HEIGHT / (ray->lenght * cos(ray->angle
				- args->player.angle));
	data->start = (HEIGHT / 2) - (int)data->wall_h / 2;
	data->end = (HEIGHT / 2) + (int)data->wall_h / 2;
	if (data->start < 0)
		data->start = 0;
	if (data->end > HEIGHT)
		data->end = HEIGHT - 1;
	if (ray->side == 0)
		data->wall_x = ((args->player.cords.y / TILE_HSIZE) + ray->lenght
				* ray->dir.y);
	else
		data->wall_x = ((args->player.cords.x / TILE_HSIZE) + ray->lenght
				* ray->dir.x);
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (tex->width));
	if (data->tex_x >= tex->width)
		data->tex_x = tex->width - 1;
	if (data->tex_x < 0)
		data->tex_x = 0;
	data->stepping = (double)tex->height / data->wall_h;
	data->tex_yy = (data->start - HEIGHT / 2 + data->wall_h / 2)
		* data->stepping;
}

void	draw_wall_slice(t_args *args, t_ray *ray, t_texture *tex, int x)
{
	t_wall_slice	data;
	int				color;
	int				y;

	y = 0;
	init_data(args, &data, ray, tex);
	while (y < HEIGHT)
	{
		if (y < data.start)
			my_mlx_pixel_put(&args->img, x, y, args->p_data->ceiling_rgb);
		else if (y > data.end)
			my_mlx_pixel_put(&args->img, x, y, args->p_data->floor_rgb);
		else
		{
			data.tex_y = (int)data.tex_yy % tex->height;
			color = get_texture_pixel(tex, data.tex_x, data.tex_y);
			my_mlx_pixel_put(&args->img, x, y, color);
			data.tex_yy += data.stepping;
		}
		y++;
	}
}
