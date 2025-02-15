#include "../includes/cub3D.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    fill_rectangle(void *img, int x, int y, int color);
void    draw_map(void *img, int map[MAP_HIGHT][MAP_WIDTH]);
void    daw_player(void *img, t_pair player_cords);
int game_loop(t_args *args);
int key_press(int keycode, t_args *args);
int key_release(int keycode, t_args *args);
void    draw_rays(t_args *args);
void    projection(t_args *args);
void    draw_minimap(t_args *args);
void draw_mmap(t_args *args);
void render_minimap(t_args *args);
void draw_rays_minimap(t_args *args);
int ckeck_collisons(t_pair new_cords, t_pair *hitted_wall);


int map[MAP_HIGHT][MAP_WIDTH] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main ()
{
    t_args p_args;

    p_args.mlx = mlx_init();
	p_args.win = mlx_new_window(p_args.mlx, WIDTH, HEIGHT, "fractol");
	p_args.img.img = mlx_new_image(p_args.mlx, WIDTH, HEIGHT);
	p_args.img.addr = mlx_get_data_addr(p_args.img.img, &p_args.img.bits_per_pixel,
			&p_args.img.line_length, &p_args.img.endian);
    p_args.player.cords.x = PLAYER_X;
    p_args.player.cords.y = PLAYER_Y;
    p_args.player.speed = 0.225;
    p_args.player.angle = M_PI / 2;
    projection(&p_args);
    render_minimap(&p_args);
    draw_rays_minimap(&p_args);
    // draw_map(&p_args.img, map);
    // daw_player(&p_args.img, p_args.player.cords);
    // draw_rays(&p_args);
    mlx_hook(p_args.win, 2, 1L << 0, key_press, &p_args);
    mlx_hook(p_args.win, 3, 1L << 1, key_release, &p_args);
    mlx_loop_hook(p_args.mlx, game_loop, &p_args);    
    mlx_put_image_to_window(p_args.mlx, p_args.win, p_args.img.img, 0, 0);
	mlx_loop(p_args.mlx);
    return (0);
}

void draw_rays(t_args *args)
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

            if (ray_x >= 0 && ray_x < MAP_WIDTH * TILE_HSIZE && ray_y >= 0 && ray_y < MAP_HIGHT * TILE_HSIZE)
                my_mlx_pixel_put(&args->img, ray_x, ray_y, 0xFF0000);
        }
    }
}

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


void draw_line(t_args *args, double length, int x, double angle, int side)
{
    int start;
    int end;
    double wall_h;
    int y;
    int base_color;
    
    base_color = 0x6e6870;
    wall_h = HEIGHT / (length * cos(angle - args->player.angle));
    start = (HEIGHT / 2) - (int)wall_h / 2;
    end = (HEIGHT / 2) + (int)wall_h / 2;
    y = 0;
    if (start < 0)
        start = 0;
    if (end > HEIGHT)
        end = HEIGHT - 1;
    double brightness = (side == 0) ? 0.7 : 1.0;
    int shaded_color = ((int)(((base_color >> 16) & 0xFF) * brightness) << 16) |
        ((int)(((base_color >> 8) & 0xFF) * brightness) << 8) | 
        ((int)((base_color & 0xFF) * brightness));   
    while (y < HEIGHT)
    {
        if (y < start)
            my_mlx_pixel_put(&args->img, x, y, SKY_COLOR);
        else if (y > end)
            my_mlx_pixel_put(&args->img, x, y, GROUND_COLOR);
        else
            my_mlx_pixel_put(&args->img, x, y, shaded_color);
        y++;
    }
}

void projection(t_args *args)
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
    int i;

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
        draw_line(args, perp_wall_dist, i, ray_angle, side);
    }
}

int ckeck_collisons(t_pair new_cords, t_pair *hitted_wall)
{   
    int map_x;
    int map_y;

    map_x = (int)((new_cords.x - PLAYER_HIGHT / 2) / TILE_HSIZE);
    map_y = (int)((new_cords.y  - PLAYER_HIGHT / 2) / TILE_HSIZE);
    if (map[map_y][map_x] == 1)
    {
        *hitted_wall = (t_pair){0, 1};
        return 1;
    }
    map_x = (int)((new_cords.x + PLAYER_HIGHT / 2) / TILE_HSIZE);
    map_y = (int)((new_cords.y - PLAYER_HIGHT / 2) / TILE_HSIZE);
    if (map[map_y][map_x] == 1)
    {
        *hitted_wall = (t_pair){-1, 0};
        return 1;
    }
    map_x = (int)((new_cords.x - PLAYER_HIGHT / 2) / TILE_HSIZE);
    map_y = (int)((new_cords.y + PLAYER_HIGHT / 2) / TILE_HSIZE);
    if (map[map_y][map_x] == 1)
    {
        *hitted_wall = (t_pair){0, -1};
        return 1;
    }
    map_x = (int)((new_cords.x + PLAYER_HIGHT / 2) / TILE_HSIZE);
    map_y = (int)((new_cords.y + PLAYER_HIGHT / 2) / TILE_HSIZE);
    if (map[map_y][map_x] == 1)
    {
        *hitted_wall = (t_pair){1, 0};
        return 1;
    }
    return 0;
}

int check_collision(t_args *args, t_pair new_cords)
{
    if (map[(int)(args->player.cords.y / TILE_HSIZE)][(int)(new_cords.x / TILE_HSIZE)] == 1)
        new_cords.x = args->player.cords.x;
    else if (map[(int)(new_cords.y / TILE_HSIZE)][(int)(args->player.cords.x / TILE_HSIZE)] == 1)
        new_cords.x = args->player.cords.x;
    else if (map[(int)(args->player.cords.y / TILE_HSIZE)][(int)(new_cords.x / TILE_HSIZE)] == 1 \
     && map[(int)(new_cords.y / TILE_HSIZE)][(int)(args->player.cords.x / TILE_HSIZE)] == 1 \
      && map[(int)(new_cords.y / TILE_HSIZE)][(int)(new_cords.x / TILE_HSIZE)] != 1)
      {
        new_cords.x = args->player.cords.x;
        new_cords.x = args->player.cords.x;
      }
      else if (map[(int)(args->player.cords.y / TILE_HSIZE)][(int)(new_cords.x / TILE_HSIZE)] != 1 \
     && map[(int)(new_cords.y / TILE_HSIZE)][(int)(args->player.cords.x / TILE_HSIZE)] != 1 \
      && map[(int)(new_cords.y / TILE_HSIZE)][(int)(new_cords.x / TILE_HSIZE)] == 1)
      {
        new_cords.x = args->player.cords.x;
        new_cords.x = args->player.cords.x;
      }
      else if (map[(int)(args->player.cords.y / TILE_HSIZE)][(int)(new_cords.x / TILE_HSIZE)] == 1 \
     && map[(int)(new_cords.y / TILE_HSIZE)][(int)(args->player.cords.x / TILE_HSIZE)] == 1 \
      && map[(int)(new_cords.y / TILE_HSIZE)][(int)(new_cords.x / TILE_HSIZE)] == 1)
      {
        new_cords.x = args->player.cords.x;
        new_cords.x = args->player.cords.x;
      }
}

// doesn't slide in some vertical walls ?
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
        new_cords.x = new_cords.x + dx * args->player.speed;
        new_cords.y = new_cords.y + dy * args->player.speed;  
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
        }
        else 
            args->player.cords = new_cords;
    }
}

int game_loop(t_args *args)
{
    check_key_pressed(args);
    projection(args);
    render_minimap(args);
    draw_rays_minimap(args);
    // draw_map(&args->img, map);
    // daw_player(&args->img, args->player.cords);
    // draw_rays(args);
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

void daw_player(void *img, t_pair player_cords)
{
    int start_x;
    int start_y;
    int player_h;
    int player_w;

    player_w = PLAYER_WIDTH;
    player_h = PLAYER_HIGHT;
    start_y = player_cords.y - PLAYER_HIGHT / 2;
    while (start_y < (player_h + player_cords.y - PLAYER_HIGHT / 2))
    {
        start_x = player_cords.x - PLAYER_HIGHT / 2;  
        while (start_x < (player_w + player_cords.x - PLAYER_HIGHT / 2))
        {
            my_mlx_pixel_put(img, start_x, start_y, 0xFFFF00);
            start_x++;
        }
        start_y++;
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
    for (int y = -player_size / 2; y < player_size / 2; y++)
    {
        for (int x = -player_size / 2; x < player_size / 2; x++)
        {
            my_mlx_pixel_put(&args->img, minimap_center.x + x, minimap_center.y + y, 0xFF0000);
        }
    }
}

void draw_map(void *img, int map[MAP_HIGHT][MAP_WIDTH])
{
    int x;
    int y;

    y = -1;
    while (++y < MAP_HIGHT)
    {
        x = -1;
        while (++x < MAP_WIDTH)
        {
            int color = map[y][x] == 1 ? 0x808080 : 0x00ff00;
            fill_rectangle(img, x, y, color);
        }
    }
}

void fill_rectangle(void *img, int x, int y, int color)
{
    int i;
    int j;
    
    i = y * TILE_WSIZE;
    while (i < ((TILE_WSIZE * y) + TILE_WSIZE))
    {
        j = x * TILE_WSIZE;
        while (j < ((TILE_WSIZE * x) + TILE_WSIZE))
        {
            my_mlx_pixel_put(img, j, i, color);
            j++;
        }
        i++;
    }
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + \
	(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}