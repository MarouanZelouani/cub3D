#include <cub3D.h>

int main (int ac, char **av)
{
    t_game_data data;

    if (ac != 2 || parser(av[1], &data))
        return (EXIT_FAILURE);
}