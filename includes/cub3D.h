#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "../libft/libft.h"

typedef struct s_game_data
{
    char **map;
    char *north_texture_path;
    char *south_texture_path;
    char *west_texture_path;
    char *east_texture_path;
    int floor_color;
    int ceiling_color;
} t_game_data;


#endif