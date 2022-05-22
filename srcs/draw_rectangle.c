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
	draw_rectangle(col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, col_width * ray->nb + col_width, SCREEN_HEIGHT / 2 + col_height / 2, vars);
}

int ray_casting(t_player *player, t_vars *vars)
{
	t_ray *ray;
	int i;
	double oldX;
	double oldY;
	double angle;
	// On part du principe que le FOV est de PI / 2 (90°)
	angle = PI / 2 / SCREEN_WIDTH;
	// On calcule la premiere moitié des rayons
	i = (SCREEN_WIDTH / 2) - 1;
	oldX = player->dir_x;
	oldY = player->dir_y;
	while (i >= 0)
	{
		ray = malloc(sizeof(t_ray));
		if (!ray)
			return (0);
		ray->nb = i;
		ray->dir_x = oldX * cos(angle) - oldY * sin(angle);
		ray->dir_y = oldX * sin(angle) + oldY * cos(angle);
		ray->distance = 10;
		oldX = ray->dir_x;
		oldY = ray->dir_y;
		render_column(vars, ray);
		i--;
	}
	oldX = player->dir_x;
	oldY = player->dir_y;
	// On calcule la seconde moitié des rayons
	i = SCREEN_WIDTH / 2;
	while (i < SCREEN_WIDTH)
	{
		ray = malloc(sizeof(t_ray));
		if (!ray)
			return (0);
		ray->nb = i;
		ray->dir_x = oldX * cos(angle * -1) - oldY * sin(angle * -1);
		ray->dir_y = oldX * sin(angle * -1) + oldY * cos(angle * -1);
		ray->distance = 10;
		oldX = ray->dir_x;
		oldY = ray->dir_y;
		render_column(vars, ray);
		i++;
	}
	return (1);
}

// Renvoie -1 si ça n'a pas touché
int impact_distance(t_ray *ray, t_vars *vars)
{
	
}
