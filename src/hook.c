#include "../includes/cub3D.h"

static int is_wall_collision(double x, double y, double buffer)
{
    int map_x;
    int map_y;
    t_pair tile;

    map_x = (int)(x / TILE_HSIZE);
    map_y = (int)(y / TILE_HSIZE);
    if (map[map_y][map_x] == 1)
        return 1;
    tile.x = (x / TILE_HSIZE) - map_x;
    tile.y = (y / TILE_HSIZE) - map_y;
    if (tile.x < buffer && map_x > 0 && map[map_y][map_x - 1] == 1)
        return 1;
    if (tile.x > 1.0 - buffer && map_x < MAP_WIDTH - 1 && map[map_y][map_x + 1] == 1)
        return 1;
    if (tile.y < buffer && map_y > 0 && map[map_y - 1][map_x] == 1)
        return 1;
    if (tile.y > 1.0 - buffer && map_y < MAP_HIGHT - 1 && map[map_y + 1][map_x] == 1)
        return 1;
    if (tile.x < buffer && tile.y < buffer && map_x > 0 && map_y > 0 && 
        map[map_y - 1][map_x - 1] == 1)
        return 1;
    if (tile.x > 1.0 - buffer && tile.y < buffer && map_x < MAP_WIDTH - 1 && map_y > 0 && 
        map[map_y - 1][map_x + 1] == 1) 
        return 1;
    if (tile.x < buffer && tile.y > 1.0 - buffer && map_x > 0 && map_y < MAP_HIGHT - 1 && 
        map[map_y + 1][map_x - 1] == 1)
        return 1;
    if (tile.x > 1.0 - buffer && tile.y > 1.0 - buffer && map_x < MAP_WIDTH - 1 && 
        map_y < MAP_HIGHT - 1 && map[map_y + 1][map_x + 1] == 1)
        return 1;
    return 0;
}

int set_movement_logic(t_args *args, t_pair *movement_vec)
{
    double tmp;

    if (args->keys_pressed[0])
        return 1;
    else if (args->keys_pressed[1])
    {   
        movement_vec->x *= -1;
        movement_vec->y *= -1;
        return 1;
    }
    else if (args->keys_pressed[2])
    {
        tmp = movement_vec->y;
        movement_vec->y = -movement_vec->x;
        movement_vec->x = tmp;
        return 1;
    }
    else if (args->keys_pressed[3])
    {
        tmp = movement_vec->x;
        movement_vec->x = -movement_vec->y;
        movement_vec->y = tmp;
        return 1;
    }
    return 0;
}

void check_key_pressed(t_args *args)
{
    t_pair new_cords;
    t_pair next_pos;
    t_pair movement_vec;

    movement_vec.x = cos(args->player.angle);
    movement_vec.y = sin(args->player.angle);
    new_cords = args->player.cords;
    if (args->keys_pressed[5])
        args->player.angle += 0.007;
    else if (args->keys_pressed[4])
        args->player.angle -= 0.007;
    if (set_movement_logic(args, &movement_vec))
    {
        // collision checks
        next_pos.x = new_cords.x + movement_vec.x * PLAYER_SPEED;
        next_pos.y = new_cords.y + movement_vec.y * PLAYER_SPEED;
        double buffer = 0.1;
        if (!is_wall_collision(next_pos.x, next_pos.y, buffer))
        {
            new_cords.x = next_pos.x;
            new_cords.y = next_pos.y;
        }
        else
        {
            if (!is_wall_collision(next_pos.x, new_cords.y, buffer))
                new_cords.x = next_pos.x;
            else if (!is_wall_collision(new_cords.x, next_pos.y, buffer))
                new_cords.y = next_pos.y;
        }
        args->player.cords = new_cords;
        args->player.cords = new_cords;
    }
}

int game_loop(t_args *args)
{
    check_key_pressed(args);
    project_3d_map(args);
    render_minimap(args);
    mlx_put_image_to_window(args->mlx, args->win, args->img.img, 0, 0);
    return (0);
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
        exit(0); // clean up
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