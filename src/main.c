/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:30 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/23 00:50:31 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "string.h"

t_star stars[STAR_COUNT];

double get_player_angle(char dir)
{
    if (dir == 'S')
        return MY_PI / 2; 
    else if (dir == 'N')
        return (3 * MY_PI) / 2;
    else if (dir == 'W')
        return MY_PI;
    return 2 * MY_PI;
}

void start_game(t_parsed_data *data)
{
    t_args p_args;
   
    p_args.p_data = data;
    p_args.mlx = mlx_init();
    load_all_textures(&p_args);
    p_args.win = mlx_new_window(p_args.mlx, WIDTH, HEIGHT, "ME SI");
    p_args.img.img = mlx_new_image(p_args.mlx, WIDTH, HEIGHT);
    p_args.img.addr = mlx_get_data_addr(p_args.img.img, &p_args.img.bits_per_pixel,
            &p_args.img.line_length, &p_args.img.endian);
    p_args.player.cords.x = data->y * TILE_HSIZE + TILE_HSIZE / 2;
    p_args.player.cords.y = data->x * TILE_HSIZE + TILE_HSIZE / 2;
    ft_memset(p_args.keys_pressed, 0, sizeof(int) * 6);
    generate_stars();
    p_args.player.speed = PLAYER_SPEED;
    p_args.player.angle = get_player_angle(data->direction);
    project_3d_map(&p_args);
    render_minimap(&p_args);
    mlx_hook(p_args.win, 2, 1L << 0, key_press, &p_args);
    mlx_hook(p_args.win, 3, 1L << 1, key_release, &p_args);
    mlx_hook(p_args.win, 17, 1L << 0, close_window, &p_args);
    mlx_loop_hook(p_args.mlx, game_loop, &p_args);    
    mlx_put_image_to_window(p_args.mlx, p_args.win, p_args.img.img, 0, 0);
    mlx_loop(p_args.mlx);
}

int main (int ac, char **av)
{
    t_parsed_data data;

    if (ac != 2)
        return 1;
    if (parse(av[1], &data) == -1)
        return (1);
    if (validation(&data))
        return (free_data(&data), ft_putstr_fd("adakaa", 2),1);
    start_game(&data);
}

