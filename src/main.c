#include "../includes/cub3D.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    fill_rectangle(void *img, int x, int y, int color);
void    draw_map(void *img, int map[MAP_HIGHT][MAP_WIDTH]);
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
    {1, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main ()
{
    t_args p_args;
    int player_map_x = 3;
    int player_map_y = 3;

    p_args.mlx = mlx_init();
	p_args.win = mlx_new_window(p_args.mlx, WIDTH, HEIGHT, "ME SI");
	p_args.img.img = mlx_new_image(p_args.mlx, WIDTH, HEIGHT);
	p_args.img.addr = mlx_get_data_addr(p_args.img.img, &p_args.img.bits_per_pixel,
			&p_args.img.line_length, &p_args.img.endian);
    p_args.player.cords.x = player_map_x * TILE_HSIZE;
    p_args.player.cords.y = player_map_y * TILE_HSIZE;
    load_all_textures(&p_args);
    p_args.player.speed = 0.225;
    p_args.player.angle = M_PI / 2;
    project_3d_map(&p_args);
    render_minimap(&p_args);
    draw_rays_minimap(&p_args);
    mlx_hook(p_args.win, 2, 1L << 0, key_press, &p_args);
    mlx_hook(p_args.win, 3, 1L << 1, key_release, &p_args);
    mlx_loop_hook(p_args.mlx, game_loop, &p_args);    
    mlx_put_image_to_window(p_args.mlx, p_args.win, p_args.img.img, 0, 0);
	mlx_loop(p_args.mlx);
    return (0);
}

