/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:26 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/23 00:50:27 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int game_loop(t_args *args)
{
    check_key_pressed(args);
    project_3d_map(args);
    render_minimap(args);
    mlx_put_image_to_window(args->mlx, args->win, args->img.img, 0, 0);
    return (0);
}

int	close_window(t_args *args)
{
	mlx_destroy_window(args->mlx, args->win);
	mlx_destroy_image(args->mlx, args->img.img);
	mlx_destroy_display(args->mlx);
	free(args->mlx);
    free_data(args->p_data); // free
	exit(EXIT_SUCCESS);
}

int key_press(int keycode, t_args *args)
{
    if (keycode == 119)
        args->keys_pressed[0] = 1;
    else if (keycode == 115)
        args->keys_pressed[1] = 1;
    else if (keycode == 97)
        args->keys_pressed[2] = 1;
    else if (keycode == 100)
        args->keys_pressed[3] = 1;
    else if (keycode == 65361)
        args->keys_pressed[4] = 1;
    else if (keycode == 65363)
        args->keys_pressed[5] = 1;        
    else if (keycode == 65307)
        close_window(args);
    return 0;
}

int key_release(int keycode, t_args *args)
{
    if (keycode == 119)
        args->keys_pressed[0] = 0;
    else if (keycode == 115)
        args->keys_pressed[1] = 0;
    else if (keycode == 97)
        args->keys_pressed[2] = 0;
    else if (keycode == 100)
        args->keys_pressed[3] = 0;
    else if (keycode == 65361)
        args->keys_pressed[4] = 0;
    else if (keycode == 65363)
        args->keys_pressed[5] = 0;
    return 0;
}