#include "../includes/cub3D.h"

static void init_data(t_args *args, t_wall_slice *data, t_ray *ray, t_texture *tex)
{
    data->wall_h = HEIGHT / ray->lenght;
    data->start = (HEIGHT / 2) - (int)data->wall_h / 2;
    data->end = (HEIGHT / 2) + (int)data->wall_h / 2;
    if (data->start < 0)
        data->start = 0;
    if (data->end > HEIGHT)
        data->end = HEIGHT - 1;
    if (ray->side == 1)
        data->wall_x = ((args->player.cords.x / TILE_HSIZE) + ray->lenght * ray->dir.x) - ray->map_pos.x;
    else
        data->wall_x = ((args->player.cords.y / TILE_HSIZE) + ray->lenght * ray->dir.y) - ray->map_pos.y;
    data->wall_x -= floor(data->wall_x);
    data->tex_x = (int)(data->wall_x * (double)tex->width) % tex->width;
    if (data->tex_x < 0) 
        data->tex_x = 0;
    if (data->tex_x >= tex->width) 
        data->tex_x = tex->width - 1;
    data->stepping = (double)tex->height / data->wall_h;
    data->tex_yy = (data->start - HEIGHT / 2 + data->wall_h / 2) * data->stepping;
}

void draw_wall_slice(t_args *args, t_ray *ray, t_texture *tex, int x)
{
    t_wall_slice data;
    int color;
    int y;
    
    y = 0;
    ray->lenght *= cos(ray->angle - args->player.angle);
    init_data(args, &data, ray, tex);
    while (y < HEIGHT)
    {
        if (y < data.start)
            my_mlx_pixel_put(&args->img, x, y, SKY_COLOR);
        else if (y > data.end)
            my_mlx_pixel_put(&args->img, x, y, GROUND_COLOR);
        else 
        {
            data.tex_y = (int)data.tex_yy % tex->height;
            color =  get_texture_pixel(tex, data.tex_x, data.tex_y);
            my_mlx_pixel_put(&args->img, x, y, color);
            data.tex_yy += data.stepping;
        }
        y++;
    }
}
