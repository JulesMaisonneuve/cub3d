#include "../cubed.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// On part du principe que y1 est inférieur à y2
void draw_line(int x, int y1, int y2, t_vars *vars, int color)
{
	while (y1 <= y2)
	{
		mlx_pixel_put(vars->mlx, vars->win, x, y1, color);
		y1++;
	}
}

void draw_ceiling(int x, int y1, int y2, t_vars *vars)
{
	t_texture_details *texture_details;
	int color;
	double pixel_offset;
	double y;
	int height;

	color = 0;
	height = y2 - y1;
	texture_details = vars->textures->texture_ceiling;
	pixel_offset = height / texture_details->texture_height;
	y = 0;
	while (y <= texture_details->texture_height)
	{
		color = get_color_from_orientation('C', x, y, vars);
		mlx_pixel_put(vars->mlx, vars->win, x, y1, color);
		y += pixel_offset;
		y1++;
	}
}
// taille rectangle = taille ecran/nb de rayons
void render_column(t_vars *vars, t_ray *ray)
{
	int col_width;
	int col_height;

	if (ray->distance <= 1)
		col_height = SCREEN_HEIGHT;
	else
		col_height = SCREEN_HEIGHT / ray->distance;
	col_width = SCREEN_WIDTH / vars->nb_ray;

	// Ciel
	draw_line(col_width * ray->nb, 0, SCREEN_HEIGHT / 2 - col_height / 2, vars, vars->ceiling_color);
	// create_trgb(0, 46, 108, 133)
	// Mur
	draw_texture_strip(ray, vars, col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, SCREEN_HEIGHT / 2 + col_height / 2);
	// Sol
	draw_line(col_width * ray->nb, SCREEN_HEIGHT / 2 + col_height / 2, SCREEN_HEIGHT, vars, vars->floor_color);
	// create_trgb(0, 245, 218, 149)
}

double get_wall_offset(t_ray *ray)
{
	switch (ray->wall_orientation)
	{
		case 'N':
			return (1 - fmod(ray->hit_x, 1));
		case 'S':
			return (fmod(ray->hit_x, 1));
		case 'E':
			return (1 - fmod(ray->hit_y, 1));
		case 'W':
			return (fmod(ray->hit_y, 1));
	}
	return (0);
}

void draw_texture_strip(t_ray *ray, t_vars *vars, int x, int y1, int y2)
{
	int color;
	double wall_height;
	double pixel_offset;
	double y;
	double wall_x;
	t_texture_details *texture_details;
	y = 0;
	wall_height = y2 - y1;
	if (ray->wall_orientation == 'N')
		texture_details = vars->textures->texture_north;
	else if (ray->wall_orientation == 'S')
		texture_details = vars->textures->texture_south;
	else if (ray->wall_orientation == 'E')
		texture_details = vars->textures->texture_east;
	else
		texture_details = vars->textures->texture_west;
	wall_x = texture_details->texture_width / ( 1 / get_wall_offset(ray));
	pixel_offset = texture_details->texture_height / wall_height;
	while (y <= texture_details->texture_height)
	{
		color = get_color_from_orientation(ray->wall_orientation, wall_x, y, vars);
		mlx_pixel_put(vars->mlx, vars->win, x, y1, color);
		y += pixel_offset;
		y1++;
	}
}
