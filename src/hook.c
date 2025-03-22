#include "../includes/cub3D.h"

static int collision(double x, double y, double buffer, t_args *args)
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
    if (tile.x > 1.0 - buffer && map_x < args->p_data->w - 1 && args->p_data->map[map_y][map_x + 1] == '1')
        return 1;
    if (tile.y < buffer && map_y > 0 && args->p_data->map[map_y - 1][map_x] == '1')
        return 1;
    if (tile.y > 1.0 - buffer && map_y < args->p_data->h - 1 && args->p_data->map[map_y + 1][map_x] == '1')
        return 1;
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
    t_pair next_pos;
    t_pair movement_vec;

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

void draw_lightsaber(t_args *args)
{
    t_texture * image = NULL;
    image->img = mlx_xpm_file_to_image(args->mlx, "textures/gun.xpm", &image->width, &image->height);
    int gun_x = (WIDTH / 2);
    int gun_y = (HEIGHT/ 2);
    mlx_put_image_to_window(args->mlx, args->win, image->img, gun_x, gun_y);
}

int game_loop(t_args *args)
{
    check_key_pressed(args);
    project_3d_map(args);
    render_minimap(args);
    //draw_lightsaber(args);
    mlx_put_image_to_window(args->mlx, args->win, args->img.img, 0, 0);
    return (0);
}

int	close_window(t_args *args)
{
	mlx_destroy_window(args->mlx, args->win);
	mlx_destroy_image(args->mlx, args->img.img);
	mlx_destroy_display(args->mlx);
	free(args->mlx);
    free_data(args->p_data);
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