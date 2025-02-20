#include "../includes/cub3D.h"

void perform_dda(t_ray *ray, t_args *args)
{
    while (1)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map_pos.x += ray->step.x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map_pos.y += ray->step.y;
            ray->side = 1;
        }
        if (map[(int)ray->map_pos.y][(int)ray->map_pos.x] == 1)
            break;
    }
}

void init_ray_data(t_args *args, t_ray *ray, int ray_number)
{
    ray->angle = args->player.angle - (FOV / 2) + ray_number * ray->angle_step;
    ray->dir.x = cos(ray->angle);
    ray->dir.y = sin(ray->angle);
    ray->map_pos.x = (int)args->player.cords.x / TILE_HSIZE;
    ray->map_pos.y = (int)args->player.cords.y / TILE_HSIZE;
    ray->delta_dist.x = fabs(1 / ray->dir.x);
    ray->delta_dist.y = fabs(1 / ray->dir.y);
}

void get_ray_lenght(t_args *args, t_ray *ray, int ray_number)
{
    init_ray_data(args, ray, ray_number);
    if (ray->dir.x < 0)
    {
        ray->step.x = -1;
        ray->side_dist.x = (args->player.cords.x / TILE_HSIZE - ray->map_pos.x) * ray->delta_dist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->side_dist.x = (ray->map_pos.x + 1.0 - args->player.cords.x / TILE_HSIZE) * ray->delta_dist.x;
    }  
    if (ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = (args->player.cords.y / TILE_HSIZE - ray->map_pos.y) * ray->delta_dist.y;
    }
    else
    {
        ray->step.y = 1;
        ray->side_dist.y = (ray->map_pos.y + 1.0 - args->player.cords.y / TILE_HSIZE) * ray->delta_dist.y;
    }
    perform_dda(ray, args);
    if (ray->side == 0)
        ray->lenght = (ray->map_pos.x - (args->player.cords.x / TILE_HSIZE) + (1 - ray->step.x) / 2) / ray->dir.x;
    else
        ray->lenght = (ray->map_pos.y - (args->player.cords.y / TILE_HSIZE) + (1 - ray->step.y) / 2) / ray->dir.y;
}

void project_3d_map(t_args *args)
{
    t_ray ray;
    t_texture *tex;
    int i;

    i = -1;
    ray.side = 0;
    ray.angle_step = FOV / WIDTH;
    while (++i < WIDTH)
    {
        get_ray_lenght(args, &ray, i);
        if (ray.side == 0)
        {
            if (ray.step.x > 0)
                tex = &args->e_tex;
            else
                tex = &args->w_tex;
        }
        else
        {
            if (ray.step.y > 0)
                tex = &args->s_tex;
            else
                tex = &args->n_tex;
        }
        // printf("1==== %d, %d\n", (int)ray.map_pos.x, (int)ray.map_pos.y);
        draw_wall_slice(args, &ray, tex, i);
    }
}

