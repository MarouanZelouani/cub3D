#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>

#define WIDTH 800
#define HEIGHT 600
#define MAP_WIDTH 9
#define MAP_HIGHT 8
#define TILE_WSIZE 50
#define TILE_HSIZE 50
#define PLAYER_X 200
#define PLAYER_Y 200
#define PLAYER_WIDTH 16
#define PLAYER_HIGHT 16
#define FOV (M_PI / 3) 
#define RAY_LENGTH 100
#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)
#define SKY_COLOR	0x34bdeb
#define GROUND_COLOR 0x595E60 

#define MINIMAP_WIDTH 120
#define MINIMAP_HIEGHT 100
#define MINIMAP_X 50
#define MINIMAP_Y 50
#define MINIMAP_SCALE  0.3

#define W_TEX "textures/wolfenstein/color_stone.xpm"
#define S_TEX "textures/wolfenstein/blue_stone.xpm"
#define E_TEX "textures/wolfenstein/grey_stone.xpm"
#define N_TEX "textures/wolfenstein/mossy.xpm"

extern int map[MAP_HIGHT][MAP_WIDTH];

typedef struct s_pair
{
	double x;
	double y;
}	t_pair;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_data;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_length;
    int     endian;
} t_texture;

typedef struct s_player
{
	t_pair cords;
	t_pair tile_cords;
	double speed;
	double rotation_speed;
	double angle;
} t_player;

typedef struct s_args
{
    void		*win;
	void		*mlx;
    t_data      img;
	t_player player;
	t_pair ray_d;
	int keys_pressed[6];
	t_texture w_tex;
	t_texture n_tex;
	t_texture e_tex;
	t_texture s_tex;
} t_args;

typedef struct s_ray
{
	double angle_step;
    double angle;
    t_pair dir;
    t_pair side_dist;
    t_pair delta_dist;
    t_pair step;
    t_pair map_pos;
    t_pair hit_point;
    int side;
	double lenght;
} t_ray;

typedef struct s_wall_slice
{
	int start;
    int end;
    double wall_h;
    int tex_x;
    int tex_y;
    double stepping;
    double tex_yy;
    double	wall_x;
} t_wall_slice;


//texture
t_texture load_texture(void *mlx, char *texture_path);
int get_texture_pixel(t_texture *texture, int x, int y);
void load_all_textures(t_args *args);
void project_3d_map(t_args *args);
// void draw_line(t_args *args, double length, int x, double angle, int side, t_texture *tex, t_pair ray);
void draw_wall_slice(t_args *args, t_ray *ray, t_texture *tex, int x);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void render_minimap(t_args *args);
void draw_rays_minimap(t_args *args);
int game_loop(t_args *args);
int key_press(int keycode, t_args *args);
int key_release(int keycode, t_args *args);
void check_key_pressed(t_args *args);

#endif