#include "../includes/cub3D.h"

static void draw_rays_minimap(t_args *args);
static void render_map_box(t_args *args);
static void render_map_tile(t_args *args, int mini_x, int mini_y, int flag);

void render_minimap(t_args *args)
{
    t_pair rel;
    int mini_x;
    int mini_y;
    int map_x;
    int map_y;

    map_y = -1;
    render_map_box(args);
    while (++map_y < MAP_HIGHT)
    {
        map_x = -1;
        while (++map_x < MAP_WIDTH)
        {
            rel.x = (map_x * TILE_HSIZE - args->player.cords.x) * MINIMAP_SCALE;
            rel.y = (map_y * TILE_HSIZE - args->player.cords.y) * MINIMAP_SCALE;
            mini_x = (MINIMAP_WIDTH / 2) + (int)rel.x;
            mini_y = (MINIMAP_HIEGHT / 2) + (int)rel.y;
            if (map[map_y][map_x] == 1) 
                render_map_tile(args, mini_x, mini_y, 1);    
            else 
                render_map_tile(args, mini_x, mini_y, 0);
        }
    }
    draw_rays_minimap(args);
}

static void draw_rays_minimap(t_args *args)
{
    t_ray ray;
    int t;
    int index;
    int ray_x;
    int ray_y;
    int mini_x;
    int mini_y;

    index = -1;
    ray.angle_step = FOV / WIDTH;
    while (++index < WIDTH)
    {
        get_ray_lenght(args, &ray, index);
        ray.lenght *= TILE_HSIZE;
        t = -1;
        while (++t < ray.lenght)
        {
            ray_x = (int)((args->player.cords.x) + t * ray.dir.x);
            ray_y = (int)((args->player.cords.y) + t * ray.dir.y);
            mini_x = (MINIMAP_WIDTH / 2) + (int)((ray_x - args->player.cords.x) * MINIMAP_SCALE);
            mini_y = (MINIMAP_HIEGHT / 2) + (int)((ray_y - args->player.cords.y) * MINIMAP_SCALE);
            if (mini_x >= 0 && mini_x < MINIMAP_WIDTH && mini_y >= 0 && mini_y < MINIMAP_HIEGHT)
                my_mlx_pixel_put(&args->img, mini_x, mini_y, RAYS_COLOR);
        }
    }
}

static void render_map_box(t_args *args)
{
    int x;
    int y;

    y = 0;
    while (y < MINIMAP_HIEGHT)
    {
        x = 0;
        while (x < MINIMAP_WIDTH)
        {
            if (x >= 0 || x < WIDTH || y >= 0 || y < HEIGHT)
                my_mlx_pixel_put(&args->img, x,  y, MAP_BOX_COLOR);
            x++;
        }
        y++;
    }
}

static void render_map_tile(t_args *args, int mini_x, int mini_y, int flag)
{
    int act_x;
    int act_y;
    int x;
    int y;

    y = 0;
    while (y < MAP_TILE_SIZE)
    {
        x = 0;
        while (x < MAP_TILE_SIZE)
        {
            act_x = mini_x + x;
            act_y = mini_y + y;
            if (act_x >= 0 && act_x <= MINIMAP_WIDTH && act_y >= 0 && act_y <= MINIMAP_HIEGHT)
            {
                if (flag == 1)
                    my_mlx_pixel_put(&args->img, mini_x + x, mini_y + y, MAP_TILE_COLOR);
                else 
                    my_mlx_pixel_put(&args->img, mini_x + x, mini_y + y, MAP_BOX_COLOR);
            }
            x++;
        }
        y++;
    }
}
