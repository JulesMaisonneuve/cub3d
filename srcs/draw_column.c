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
	int wall_color;
	int col_height;
	if (ray->distance <= 1)
		col_height = SCREEN_HEIGHT;
	else
		col_height = SCREEN_HEIGHT / ray->distance;
	col_width = SCREEN_WIDTH / vars->nb_ray;
	// Ciel
	draw_line(col_width * ray->nb, 0, SCREEN_HEIGHT / 2 - col_height / 2, vars, create_trgb(0, 46, 108, 133));
	switch (ray->wall_orientation)
	{
		case 'N':
			wall_color = create_trgb(0, 90, 0, 0);
			break ;
		case 'S':
			wall_color = create_trgb(0, 110, 0, 0);
			break ;
		case 'E':
			wall_color = create_trgb(0, 240, 0, 0);
			break ;
		case 'W':
			wall_color = create_trgb(0, 50, 0, 0);
			break ;
	}
	// Mur
	draw_line(
		col_width * ray->nb,
		SCREEN_HEIGHT / 2 - col_height / 2,
		SCREEN_HEIGHT / 2 + col_height / 2,
		vars, wall_color
	);
	// Sol
	draw_line(col_width * ray->nb, SCREEN_HEIGHT / 2 + col_height / 2, SCREEN_HEIGHT, vars, create_trgb(0, 82, 133, 46));
}
