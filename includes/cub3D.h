#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "../minilibx-linux/mlx.h"

#define MY_PI 3.14159265359
#define WIDTH 800
#define HEIGHT 600
#define MAP_WIDTH 12
#define MAP_HIGHT 8
#define TILE_HSIZE 50
#define FOV (MY_PI / 3) 
#define SKY_COLOR	0x34bdeb
#define GROUND_COLOR 0x595E60 
#define PLAYER_SPEED 0.4

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

#define W_TEX "textures/wolfenstein/color_stone.xpm"
#define S_TEX "textures/wolfenstein/blue_stone.xpm"
#define E_TEX "textures/wolfenstein/grey_stone.xpm"
#define N_TEX "textures/wolfenstein/mossy.xpm"

extern int map[MAP_HIGHT][MAP_WIDTH];


//texture
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

#endif