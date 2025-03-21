#ifndef CUB3D_H
#define CUB3D_H

#include "./parsing.h"
#include "./structs.h"

#define MY_PI 3.14159265359
#define WIDTH 800
#define HEIGHT 600
#define TILE_HSIZE 40
#define FOV (MY_PI / 3)
#define PLAYER_SPEED 0.5

// minimap params
#define RAYS_COLOR 0xFF0000
#define MAP_BOX_COLOR 0x000000
#define MINIMAP_WIDTH 120
#define MINIMAP_HIEGHT 100
#define MINIMAP_X 50
#define MINIMAP_Y 50
#define MINIMAP_SCALE  0.3
#define MAP_TILE_SIZE (int)(TILE_HSIZE * MINIMAP_SCALE)
#define MAP_TILE_COLOR 0xFFFFFF
#define STAR_COUNT 100
#define STAR_COLOR 0xFFFFFF



typedef struct s_star
{
    int x;
    int y;
} t_star;
 
extern t_star stars[STAR_COUNT];
void generate_stars();

t_texture load_texture(void *mlx, char *texture_path);
int get_texture_pixel(t_texture *texture, int x, int y);
void load_all_textures(t_args *args);
void project_3d_map(t_args *args);
void draw_wall_slice(t_args *args, t_ray *ray, t_texture *tex, int x);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
int game_loop(t_args *args);
int key_press(int keycode, t_args *args);
int key_release(int keycode, t_args *args);
void check_key_pressed(t_args *args);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
int game_loop(t_args *args);
int key_press(int keycode, t_args *args);
int key_release(int keycode, t_args *args);
void render_minimap(t_args *args);
void get_ray_lenght(t_args *args, t_ray *ray, int ray_number);
int	close_window(t_args *args);

#endif