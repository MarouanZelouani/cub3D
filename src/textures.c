/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:46 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:00:59 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void free_er_tex(t_args *args, int num)
{
	if (num >= 1)
		mlx_destroy_image(args->mlx, args->w_tex.img);
	if (num >= 2)
		mlx_destroy_image(args->mlx, args->n_tex.img);
	if (num >= 3)
		mlx_destroy_image(args->mlx, args->e_tex.img);
	mlx_destroy_display(args->mlx);
	free(args->mlx);
	free_data(args->p_data);
	exit(EXIT_FAILURE);
}

void	load_all_textures(t_args *args)
{
	args->w_tex = load_texture(args->mlx, args->p_data->west_textures);
	if (!args->w_tex.img)
		free_er_tex(args, 0);
	args->n_tex = load_texture(args->mlx, args->p_data->north_textures);
	if (!args->n_tex.img)
		free_er_tex(args, 1);
	args->e_tex = load_texture(args->mlx, args->p_data->east_textures);
	if (!args->e_tex.img)
		free_er_tex(args, 2);
	args->s_tex = load_texture(args->mlx, args->p_data->south_textures);
	if (!args->s_tex.img)
		free_er_tex(args, 3);
}

t_texture	load_texture(void *mlx, char *texture_path)
{
	t_texture	texture;
	
	while (*texture_path && *texture_path == ' ')
		texture_path++;
	texture.img = mlx_xpm_file_to_image(mlx, texture_path, &texture.width,
			&texture.height);
	if (!texture.img)
	{
		perror("Error: can't open file");
		return texture;
	}
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp,
			&texture.line_length, &texture.endian);
	return (texture);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	int		color;
	char	*pixel;

	pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(int *)pixel;
	return (color);
}
