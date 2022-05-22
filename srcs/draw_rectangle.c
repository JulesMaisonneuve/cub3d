#include "../cubed.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void draw_rectangle(int x1, int y1, int x2, int y2, t_vars *vars, int color)
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
			mlx_pixel_put(vars->mlx, vars->win, x, y, color);
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
	// Mur
	switch (ray->wall_orientation)
	{
		case 'N':
			draw_rectangle(col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, col_width * ray->nb + col_width, SCREEN_HEIGHT / 2 + col_height / 2, vars, create_trgb(0, 100, 0, 0));
			break ;
		case 'S':
			draw_rectangle(col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, col_width * ray->nb + col_width, SCREEN_HEIGHT / 2 + col_height / 2, vars, create_trgb(0, 90, 0, 0));
			break ;
		case 'E':
			draw_rectangle(col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, col_width * ray->nb + col_width, SCREEN_HEIGHT / 2 + col_height / 2, vars, create_trgb(0, 240, 0, 0));
			break ;
		case 'W':
			draw_rectangle(col_width * ray->nb, SCREEN_HEIGHT / 2 - col_height / 2, col_width * ray->nb + col_width, SCREEN_HEIGHT / 2 + col_height / 2, vars, create_trgb(0, 30, 0, 0));
			break ;
	}
}

int ray_casting(t_vars *vars)
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
	oldX = vars->player->dir_x;
	oldY = vars->player->dir_y;
	// Plafond
	draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2, vars, create_trgb(0, 50, 121, 168));
	// Sol
	draw_rectangle(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, vars, create_trgb(0, 50, 168, 50));
	while (i >= 0)
	{
		ray = malloc(sizeof(t_ray));
		if (!ray)
			return (0);
		ray->nb = i;
		ray->dir_x = oldX * cos(angle) - oldY * sin(angle);
		ray->dir_y = oldX * sin(angle) + oldY * cos(angle);
		ray->pos_x = vars->player->pos_x;
		ray->pos_y = vars->player->pos_y;
		impact_distance(ray, vars);
		oldX = ray->dir_x;
		oldY = ray->dir_y;
		render_column(vars, ray);
		free(ray);
		i--;
	}
	oldX = vars->player->dir_x;
	oldY = vars->player->dir_y;
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
		ray->pos_x = vars->player->pos_x;
		ray->pos_y = vars->player->pos_y;
		impact_distance(ray, vars);
		oldX = ray->dir_x;
		oldY = ray->dir_y;
		render_column(vars, ray);
		free(ray);
		i++;
	}
	return (1);
}

int is_in_map(t_vars *vars, double pos_x, double pos_y)
{
	return (pos_x >= 0 && pos_y >= 0 && pos_x < vars->map_width && pos_y < vars->map_height);
}

// Renvoie -1 si ça n'a pas touché de mur
void impact_distance(t_ray *ray, t_vars *vars)
{
	double actual_pos_x;
	double actual_pos_y;

	actual_pos_x = ray->pos_x;
	actual_pos_y = ray->pos_y;
	while (is_in_map(vars, actual_pos_x, actual_pos_y))
	{
		if (vars->map[(int)actual_pos_y][(int)actual_pos_x] == '1')
		{
			if (actual_pos_x <= 0.5 && actual_pos_y <= 0.5)
			{
				// Soit Nord soit Ouest
				if (actual_pos_x - floor(actual_pos_x) > actual_pos_y - floor(actual_pos_y))
					ray->wall_orientation = 'N';
				else
					ray->wall_orientation = 'W';
			}
			else if (actual_pos_x <= 0.5 && actual_pos_y >= 0.5)
			{
				// Soit Sud soit Ouest
				if (ceil(actual_pos_x) - actual_pos_x > actual_pos_y - floor(actual_pos_y))
					ray->wall_orientation = 'W';
				else
					ray->wall_orientation = 'S';
			}
			else if (actual_pos_x >= 0.5 && actual_pos_y <= 0.5)
			{
				// Soit Nord soit Est
				if (ceil(actual_pos_x) - actual_pos_x > actual_pos_y - floor(actual_pos_y))
					ray->wall_orientation = 'E';
				else
					ray->wall_orientation = 'N';
			}
			else
			{
				// Soit Sud soit Est
				ray->wall_orientation = 'S';
			}
			ray->distance = sqrt(fabs(actual_pos_x - ray->pos_x) * fabs(actual_pos_x - ray->pos_x) + fabs(actual_pos_y - ray->pos_y) * fabs(actual_pos_y - ray->pos_y));
			return ;
		}
		else
		{
			actual_pos_x += ray->dir_x * 0.1;
			actual_pos_y += ray->dir_y * 0.1;
		}
	}

}
