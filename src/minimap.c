#include "../includes/cub3D.h"

void draw_rays_minimap(t_args *args)
{
    double angle_step;
    double ray_angle;
    t_pair ray_dir;
    t_pair side_dist;
    t_pair delta_dist;
    t_pair step;
    t_pair map_pos;
    double perp_wall_dist;
    int side;
    double ray_lenght;
    int i;
    int mini_x, mini_y;
    int minimap_center_x = MINIMAP_WIDTH / 2;
    int minimap_center_y = MINIMAP_HIEGHT / 2;

    i = -1;
    side = 0;
    angle_step = FOV / WIDTH;
    while (++i < WIDTH)
    {
        ray_angle = args->player.angle - (FOV / 2) + i * angle_step;
        ray_dir.x = cos(ray_angle);
        ray_dir.y = sin(ray_angle);
        map_pos.x = (int)args->player.cords.x / TILE_HSIZE;
        map_pos.y = (int)args->player.cords.y / TILE_HSIZE;
        delta_dist.x = fabs(1 / ray_dir.x);
        delta_dist.y = fabs(1 / ray_dir.y);
        if (ray_dir.x < 0)
        {
            step.x = -1;
            side_dist.x = (args->player.cords.x / TILE_HSIZE - map_pos.x) * delta_dist.x;
        }
        else
        {
            step.x = 1;
            side_dist.x = (map_pos.x + 1.0 - args->player.cords.x / TILE_HSIZE) * delta_dist.x;
        }
        if (ray_dir.y < 0)
        {
            step.y = -1;
            side_dist.y = (args->player.cords.y / TILE_HSIZE - map_pos.y) * delta_dist.y;
        }
        else
        {
            step.y = 1;
            side_dist.y = (map_pos.y + 1.0 - args->player.cords.y / TILE_HSIZE) * delta_dist.y;
        }
        while (1)
        {
            if (side_dist.x < side_dist.y)
            {
                side_dist.x += delta_dist.x;
                map_pos.x += step.x;
                side = 0;
            }
            else
            {
                side_dist.y += delta_dist.y;
                map_pos.y += step.y;
                side = 1;
            }
            if (map[(int)map_pos.y][(int)map_pos.x] == 1)
                break;
        }
        if (side == 0)
            perp_wall_dist = (map_pos.x - args->player.cords.x / TILE_HSIZE + (1 - step.x) / 2) / ray_dir.x;
        else
            perp_wall_dist = (map_pos.y - args->player.cords.y / TILE_HSIZE + (1 - step.y) / 2) / ray_dir.y;
        ray_lenght = perp_wall_dist * TILE_HSIZE;
        for (int t = 0; t < ray_lenght; t++)
        {
            int ray_x = (int)((args->player.cords.x) + t * ray_dir.x);
            int ray_y = (int)((args->player.cords.y) + t * ray_dir.y);
            mini_x = minimap_center_x + (int)((ray_x - args->player.cords.x) * MINIMAP_SCALE);
            mini_y = minimap_center_y + (int)((ray_y - args->player.cords.y) * MINIMAP_SCALE);
            if (mini_x >= 0 && mini_x < MINIMAP_WIDTH && mini_y >= 0 && mini_y < MINIMAP_HIEGHT)
                my_mlx_pixel_put(&args->img, mini_x, mini_y, 0xFF0000);
        }
    }
}

void render_minimap(t_args *args)
{
    int tile_size;
    t_pair minimap_center;
    int player_size;
    t_pair rel;
    int mini_x;
    int mini_y;
    int map_x;
    int map_y;

    map_y = -1;
    player_size = PLAYER_WIDTH * MINIMAP_SCALE;
    minimap_center.x = MINIMAP_WIDTH / 2;
    minimap_center.y = MINIMAP_HIEGHT / 2;
    tile_size = TILE_HSIZE * MINIMAP_SCALE;
    for (int y = 0; y < MINIMAP_HIEGHT; y++)
    {
        for (int x = 0; x < MINIMAP_WIDTH; x++)
            my_mlx_pixel_put(&args->img, x,  y, 0x000000);
    }
    while (++map_y < MAP_HIGHT)
    {
        map_x = -1;
        while (++map_x < MAP_WIDTH)
        {
            rel.x = (map_x * TILE_HSIZE - args->player.cords.x) * MINIMAP_SCALE;
            rel.y = (map_y * TILE_HSIZE - args->player.cords.y) * MINIMAP_SCALE;
            mini_x = minimap_center.x + (int)rel.x;
            mini_y = minimap_center.y + (int)rel.y;
            int color = (map[map_y][map_x] == 1) ? 0xFFFFFF : 0x000000;
            for (int y = 0; y < tile_size; y++)
            {
                for (int x = 0; x < tile_size; x++)
                {
                    int act_x = mini_x + x;
                    int act_y = mini_y + y;
                    if (act_x >= 0 && act_x <= MINIMAP_WIDTH && act_y >= 0 && act_y <= MINIMAP_HIEGHT)
                        my_mlx_pixel_put(&args->img, mini_x + x, mini_y + y, color);
                }
            }
        }
    }
    // for (int y = -player_size / 2; y < player_size / 2; y++)
    // {
    //     for (int x = -player_size / 2; x < player_size / 2; x++)
    //     {
    //         my_mlx_pixel_put(&args->img, minimap_center.x + x, minimap_center.y + y, 0xFF0000);
    //     }
    // }
}