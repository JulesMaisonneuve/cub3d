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

// taille rectangle = taille ecran/nb de rayons
void render_column(t_vars *vars, t_ray *ray)
{
	int col_width;
	// int wall_color;
	int col_height;
	if (ray->distance <= 1)
		col_height = SCREEN_HEIGHT;
	else
		col_height = SCREEN_HEIGHT / ray->distance;
	col_width = SCREEN_WIDTH / vars->nb_ray;
	// Ciel
	draw_line(col_width * ray->nb, 0, SCREEN_HEIGHT / 2 - col_height / 2, vars, create_trgb(0, 46, 108, 133));
	// switch (ray->wall_orientation)
	// {
	// 	case 'N':
	// 		wall_color = create_trgb(0, 90, 0, 0);
	// 		break ;
	// 	case 'S':
	// 		wall_color = create_trgb(0, 110, 0, 0);
	// 		break ;
	// 	case 'E':
	// 		wall_color = create_trgb(0, 240, 0, 0);
	// 		break ;
	// 	case 'W':
	// 		wall_color = create_trgb(0, 50, 0, 0);
	// 		break ;
	// }
	// Mur
	draw_texture_strip(ray, vars, col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, SCREEN_HEIGHT / 2 + col_height / 2);
	// Sol
	draw_line(col_width * ray->nb, SCREEN_HEIGHT / 2 + col_height / 2, SCREEN_HEIGHT, vars, create_trgb(0, 82, 133, 46));
}

int get_wall_offset(t_ray *ray)
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
	int wall_x;

	y = y1;
	wall_height = y2 - y1;
	wall_x = get_wall_offset(ray);
	pixel_offset = vars->texture_height / wall_height;
	while (y <= y2)
	{
		// printf("texture_height: %d wall_height: %lf\n", vars->texture_height, wall_height);
		// printf("pixel offset: %f\n", pixel_offset);
		// printf("y: %lf y2: %d\n", y, y2);
		color = get_color_from_orientation(ray->wall_orientation, wall_x, y, vars);
		mlx_pixel_put(vars->mlx, vars->win, x, y, color);
		y += pixel_offset;
	}
}