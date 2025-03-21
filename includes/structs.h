#ifndef STRUCTS_H
#define STRUCTS_H

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
    t_parsed_data *p_data;
} t_args;

typedef struct s_ray
{
	double angle_step;
    double angle;
    t_pair dir;
    t_pair side_dist;
    t_pair delta_dist;
    t_pair step;
    // t_pair map_pos;
    int map_pos_x;
    int map_pos_y;
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

#endif