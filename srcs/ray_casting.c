#include "../cubed.h"

int ray_casting(t_vars *vars)
{
	t_ray ray;
	int i;
	double oldX;
	double oldY;
	double angle;
	double base_angle = PI / 6;

	// On part du principe que le FOV est de PI / 3 (60°)
	angle = (PI / 3 / SCREEN_WIDTH) * -1;
	i = 0;
	oldX = vars->player->dir_x * cos(base_angle) - vars->player->dir_y * sin(base_angle);
	oldY = vars->player->dir_x * sin(base_angle) + vars->player->dir_y * cos(base_angle);
	while (i < SCREEN_WIDTH)
	{
		ray.nb = i;
		ray.dir_x = oldX * cos(angle) - oldY * sin(angle);
		ray.dir_y = oldX * sin(angle) + oldY * cos(angle);
		ray.pos_x = vars->player->pos_x;
		ray.pos_y = vars->player->pos_y;
		impact_distance(&ray, vars, base_angle + angle * ray.nb);
		oldX = ray.dir_x;
		oldY = ray.dir_y;
		render_column(vars, &ray);
		i++;
	}
	return (1);
}

int is_in_map(t_vars *vars, double pos_x, double pos_y)
{
	return (pos_x >= 0 && pos_y >= 0 && pos_x < vars->map_width && pos_y < vars->map_height);
}

void impact_distance(t_ray *ray, t_vars *vars, double angle)
{
	double actual_pos_x;
	double actual_pos_y;
	double dist_n;
	double dist_s;
	double dist_e;
	double dist_w;
	
	actual_pos_x = ray->pos_x;
	actual_pos_y = ray->pos_y;
	while (is_in_map(vars, actual_pos_x, actual_pos_y))
	{
		if (vars->map[(int)actual_pos_y][(int)actual_pos_x] == '1')
		{
			dist_n = fmod(actual_pos_y, 1.0);
			dist_s = 1 - fmod(actual_pos_y, 1.0);
			dist_w = fmod(actual_pos_x, 1.0);
			dist_e = 1 - fmod(actual_pos_x, 1.0);
			if (dist_n <= dist_s && dist_n <= dist_w && dist_n <= dist_e)
				ray->wall_orientation = 'N';
			else if (dist_s <= dist_n && dist_s <= dist_w && dist_s <= dist_e)
				ray->wall_orientation = 'S';
			else if (dist_e <= dist_s && dist_e <= dist_n && dist_e <= dist_w)
				ray->wall_orientation = 'E';
			else
				ray->wall_orientation = 'W';
			ray->distance = sqrt(fabs(actual_pos_x - ray->pos_x) * fabs(actual_pos_x - ray->pos_x) + fabs(actual_pos_y - ray->pos_y) * fabs(actual_pos_y - ray->pos_y)) * cos(angle);
			return ;
		}
		else
		{
			actual_pos_x += ray->dir_x * 0.005;
			actual_pos_y += ray->dir_y * 0.005;
		}
	}

}
