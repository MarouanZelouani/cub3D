#include "../includes/cub3D.h"


int ckeck_collisons(t_pair new_cords, t_pair *hitted_wall)
{
    int collided = 0;
    int left = (int)((new_cords.x ) / TILE_HSIZE);    
    int bottom = (int)((new_cords.y ) / TILE_HSIZE);
    *hitted_wall = (t_pair){0, 0}; 
    if (map[bottom][left] == 1)
    {
        hitted_wall->x = 1;
        collided = 1;
    }
    return collided;
}

void check_key_pressed(t_args *args)
{
    t_pair new_cords;
    double dy;
    double dx;
    double tmp;
    t_pair slide;
    int flag;
    t_pair hitted_wall;
    double dot_product;
    t_pair slide_cords;

    flag = 0;
    hitted_wall = (t_pair){0, 0};
    dx = cos(args->player.angle);
    dy = sin(args->player.angle);
    new_cords = args->player.cords;
    if (args->keys_pressed[0] == 1)
        flag = 1;
    else if (args->keys_pressed[1] == 1)
    {   
        flag = 1;
        dx *= -1;
        dy *= -1;
    }
    else if (args->keys_pressed[2] == 1)
    {
        flag = 1;
        tmp = dy;
        dy = -dx;
        dx = tmp;
    }
    else if (args->keys_pressed[3] == 1)
    {
        flag = 1;
        tmp = dx;
        dx = -dy;
        dy = tmp;
    }
    else if (args->keys_pressed[5] == 1)
        args->player.angle += 0.005;
    else if (args->keys_pressed[4] == 1)
        args->player.angle -= 0.005;
    if (flag)
    {
        new_cords.x += dx * args->player.speed;
        new_cords.y += dy * args->player.speed;
        if (ckeck_collisons(new_cords, &hitted_wall)) 
        {
            dot_product = (dx * hitted_wall.x + dy * hitted_wall.y);
            slide.x = dx - dot_product * hitted_wall.x;
            slide.y = dy - dot_product * hitted_wall.y;
            slide_cords = args->player.cords;
            slide_cords.x += slide.x * args->player.speed;
            slide_cords.y += slide.y * args->player.speed;
            if (!ckeck_collisons(slide_cords, &hitted_wall))
                args->player.cords = slide_cords;
            else 
            {
                t_pair try_x = args->player.cords, try_y = args->player.cords;
                try_x.x += slide.x * args->player.speed;
                try_y.y += slide.y * args->player.speed;
                if (!ckeck_collisons(try_x, &hitted_wall))
                    args->player.cords = try_x;
                else if (!ckeck_collisons(try_y, &hitted_wall))
                    args->player.cords = try_y;
            }
        }
        else 
            args->player.cords = new_cords;
    }
}

int game_loop(t_args *args)
{
    check_key_pressed(args);
    project_3d_map(args);
    render_minimap(args);
    draw_rays_minimap(args);
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
        exit(0);
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