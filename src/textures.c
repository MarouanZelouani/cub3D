#include "../includes/cub3D.h"

void load_all_textures(t_args *args)
{
    args->w_tex = load_texture(args->mlx, args->p_data->west_textures);
    args->n_tex = load_texture(args->mlx, args->p_data->north_textures);
    args->e_tex = load_texture(args->mlx, args->p_data->east_textures);
    args->s_tex = load_texture(args->mlx, args->p_data->south_textures);
}

t_texture load_texture(void *mlx, char *texture_path)
{
    t_texture texture;

    texture.img = mlx_xpm_file_to_image(mlx, texture_path, &texture.width, &texture.height);
    if (!texture.img)
    {
        perror("Error: can't open file");
        exit(1); 
    }
    texture.addr =  mlx_get_data_addr(texture.img, &texture.bpp, 
        &texture.line_length, &texture.endian);
    return (texture);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + \
	(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int get_texture_pixel(t_texture *texture, int x, int y)
{
    int color;
    char *pixel;

    pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
    color = *(int *)pixel;
    return (color);
}