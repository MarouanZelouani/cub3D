#include "../includes/cub3D.h"
#include "string.h"

int map[MAP_HIGHT][MAP_WIDTH] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void start_game(t_parser_data *data)
{
    t_args p_args;
   
    p_args.mlx = mlx_init();
    p_args.win = mlx_new_window(p_args.mlx, WIDTH, HEIGHT, "ME SI");
    p_args.img.img = mlx_new_image(p_args.mlx, WIDTH, HEIGHT);
    p_args.img.addr = mlx_get_data_addr(p_args.img.img, &p_args.img.bits_per_pixel,
            &p_args.img.line_length, &p_args.img.endian);
    p_args.player.cords.x = data->player_map_x * TILE_HSIZE;
    p_args.player.cords.y = data->player_map_y * TILE_HSIZE;
    memset(p_args.keys_pressed, 0, sizeof(int) * 6); // use ft_memset
    load_all_textures(&p_args);
    p_args.player.speed = PLAYER_SPEED;
    p_args.player.angle = MY_PI / 2;
    project_3d_map(&p_args);
    render_minimap(&p_args);
    mlx_hook(p_args.win, 2, 1L << 0, key_press, &p_args);
    mlx_hook(p_args.win, 3, 1L << 1, key_release, &p_args);
    mlx_loop_hook(p_args.mlx, game_loop, &p_args);    
    mlx_put_image_to_window(p_args.mlx, p_args.win, p_args.img.img, 0, 0);
    mlx_loop(p_args.mlx);
}

int main ()
{
    t_parser_data data;

    data.player_map_x = 3;
    data.player_map_y = 3;
    start_game(&data);
    return (0);
}

