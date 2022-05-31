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
    int img_height;
    int img_width;
    t_texture_details *texture_details;
    texture_details = malloc(sizeof(t_texture_details));
    void *texture = mlx_xpm_file_to_image(vars->mlx, texture_path, &img_width, &img_height);
    texture_details->texture_width = img_width;
    texture_details->texture_height = img_height;
    texture_details->texture_data = mlx_get_data_addr(texture, &size, &size_line, &endian);
    if (texture == NULL)
        return (-1);
    switch (orientation)
    {
        case 'N':
            vars->textures->texture_north = texture_details;
            break;
        case 'S':
            vars->textures->texture_south = texture_details;
            break;
        case 'E':
            vars->textures->texture_east = texture_details;
            break;
        case 'W':
            vars->textures->texture_west = texture_details;
            break;
    }
    return (0);
}

int get_color_from_orientation(char orientation, int x, int y, t_vars *vars)
{
    t_texture_details *texture;
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
    color = *((int *)texture->texture_data + (x + y * texture->texture_height));
    return (color);
}