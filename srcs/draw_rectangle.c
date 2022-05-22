#include "../cubed.h"

void draw_rectangle(int x1, int y1, int x2, int y2, t_vars *vars)
{
	int x;
	int y;

	x = x1;
	y = y1;
	while (x != x2)
	{
		y = y1;
		while (y != y2)
		{
			mlx_pixel_put(vars->mlx, vars->win, x, y, 'B');
			y++;
		}
		x++;
	}
}

// taille ractangle = taille ecran/nb de rayons
void render_column(t_vars *vars, t_ray *ray)
{
	int col_width;
	int col_height;
	(void)ray;
	col_width = SCREEN_WIDTH / vars->nb_ray;
	col_height = SCREEN_HEIGHT / ray->distance;
	printf("%d\n", col_height);
	printf("%d\n", col_width * ray->nb);
	printf("%d\n", SCREEN_HEIGHT / 2 - col_height / 2);
	printf("%d\n", col_width * ray->nb + col_width);
	printf("%d\n", SCREEN_HEIGHT / 2 + col_height / 2);
	draw_rectangle(col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, col_width * ray->nb + col_width, SCREEN_HEIGHT / 2 + col_height / 2, vars);
}

// void ray_casting(t_ray *ray)
// {

// }
