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
#define GROUND_COLOR 0xcca168

#define MINIMAP_WIDTH 120
#define MINIMAP_HIEGHT 100
#define MINIMAP_X 50
#define MINIMAP_Y 50
#define MINIMAP_SCALE  0.3


#define clamp(x, minVal, maxVal) ({ \
    typeof(x) _x = (x); \
    typeof(minVal) _minVal = (minVal); \
    typeof(maxVal) _maxVal = (maxVal); \
    _x < _minVal ? _minVal : (_x > _maxVal ? _maxVal : _x); \
})

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
} t_args;

#endif