#include "../cubed.h"



int parse_texture(t_vars *vars, char *texture_path, char orientation)
{
    int img_height;
    int img_width;
    int size_line;
    int endian;
    int size;
    void *texture = mlx_xpm_file_to_image(vars->mlx, texture_path, &img_width, &img_height);
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

t_color *get_color_from_orientation(char orientation, int x, int y, t_vars *vars)
{
    char *texture;
    t_color *colors;
    int i = 0;
    if (x + (y * IMG_SIZE) >= IMG_SIZE * IMG_SIZE)
    {
        printf("BUG\n");
        return (0);
    }
    colors = malloc(sizeof(t_color));
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
    colors->r = texture[x + y * 256];
    colors->g = texture[(x + y * 256) + 1];
    colors->b = texture[(x + y * 256) + 2];
    while (i < 1000)
    {
        printf("%c", texture[i]);
        i++;
    }
    printf["\n"];
    // printf("texture[index]: %c\n", texture[(x * 4 + y * IMG_SIZE) + 2]);
    printf("text: %s\n", texture);
    printf("texture[256]: %c\n", texture[0]);
    printf("texture[26]: %c\n", texture[1]);
    printf("texture[256]: %c\n", texture[2]);
    printf("texture[256]: %c\n", texture[3]);
    colors->o = texture[(x * 4 + y * IMG_SIZE) + 3];
    printf("r: %d g: %d b: %d o: %d\n", colors->r, colors->g, colors->b, colors->o);
    return (colors);
}