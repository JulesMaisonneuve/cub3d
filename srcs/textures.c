#include "../cubed.h"

int    get_t(int trgb)
{
    return ((trgb >> 24) & 0xFF);
}

int    get_r(int trgb)
{
    return ((trgb >> 16) & 0xFF);
}

int    get_g(int trgb)
{
    return ((trgb >> 8) & 0xFF);
}

int    get_b(int trgb)
{
    return (trgb & 0xFF);
}

int parse_texture(t_vars *vars, char *texture_path, char orientation)
{
    int size_line;
    int endian;
    int size;
    void *texture = mlx_xpm_file_to_image(vars->mlx, texture_path, &vars->texture_width, &vars->texture_height);
    char *img_data;
    img_data = mlx_get_data_addr(texture, &size, &size_line, &endian);
    if (texture == NULL)
        return (-1);
    switch (orientation)
    {
        case 'N':
            vars->textures->texture_north = img_data;
            break;
        case 'S':
            vars->textures->texture_south = img_data;
            break;
        case 'E':
            vars->textures->texture_east = img_data;
            break;
        case 'W':
            vars->textures->texture_west = img_data;
            break;
    }
    return (0);
}

int get_color_from_orientation(char orientation, int x, int y, t_vars *vars)
{
    char *texture;
    int color;
    // if (x + (y * IMG_SIZE) >= IMG_SIZE * IMG_SIZE)
    // {
    //     printf("BUG\n");
    //     return (0);
    // }
    switch (orientation)
    {
        case 'N':
            texture = vars->textures->texture_north;
            break;
        case 'S':
            texture = vars->textures->texture_south;
            break;
        case 'E':
            texture = vars->textures->texture_east;
            break;
        case 'W':
            texture = vars->textures->texture_west;
            break;
    }
    color = *((int *)texture + (x * 4 + y * IMG_SIZE));
    return (color);
}