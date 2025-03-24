/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 00:50:14 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/23 00:50:15 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int check_corners(t_args *args, t_pair tile, int map_x, int map_y, double buffer);

int collision(double x, double y, double buffer, t_args *args)
{
    int map_x;
    int map_y;
    t_pair tile;

    map_x = (int)(x / TILE_HSIZE);
    map_y = (int)(y / TILE_HSIZE);
    if (args->p_data->map[map_y][map_x] == '1')
        return 1;
    tile.x = (x / TILE_HSIZE) - map_x;
    tile.y = (y / TILE_HSIZE) - map_y;
    if (tile.x < buffer && map_x > 0 && args->p_data->map[map_y][map_x - 1] == '1')
        return 1;
    if (tile.x > 1.0 - buffer && map_x < args->p_data->w - 1 
        && args->p_data->map[map_y][map_x + 1] == '1')
        return 1;
    if (tile.y < buffer && map_y > 0 && args->p_data->map[map_y - 1][map_x] == '1')
        return 1;
    if (tile.y > 1.0 - buffer && map_y < args->p_data->h - 1  
        && args->p_data->map[map_y + 1][map_x] == '1')
        return 1;
    if (check_corners(args, tile, map_x, map_y, buffer))
        return 1;
    return 0;
}

static int check_corners(t_args *args, t_pair tile, int map_x, int map_y, double buffer)
{
    if (tile.x < buffer && tile.y < buffer && map_x > 0 && map_y > 0 && 
        args->p_data->map[map_y - 1][map_x - 1] == '1')
        return 1;
    if (tile.x > 1.0 - buffer && tile.y < buffer && map_x < args->p_data->w - 1 && map_y > 0 && 
        args->p_data->map[map_y - 1][map_x + 1] == '1') 
        return 1;
    if (tile.x < buffer && tile.y > 1.0 - buffer && map_x > 0 && map_y < args->p_data->h - 1 && 
        args->p_data->map[map_y + 1][map_x - 1] == '1')
        return 1;
    if (tile.x > 1.0 - buffer && tile.y > 1.0 - buffer && map_x < args->p_data->w - 1 && 
        map_y < args->p_data->h - 1 && args->p_data->map[map_y + 1][map_x + 1] == '1')
        return 1;
    return 0;
}
