/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:32:16 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/14 05:10:49 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	ray_casting(t_vars *vars)
{
	t_ray	ray;
	int		i;
	double	old_x;
	double	old_y;

	i = 0;
	old_x = vars->player->dir_x * cos(vars->base_angle)
		- vars->player->dir_y * sin(vars->base_angle);
	old_y = vars->player->dir_x * sin(vars->base_angle)
		+ vars->player->dir_y * cos(vars->base_angle);
	while (i < SCREEN_WIDTH)
	{
		ray.nb = i;
		ray.dir_x = old_x * cos(vars->angle) - old_y * sin(vars->angle);
		ray.dir_y = old_x * sin(vars->angle) + old_y * cos(vars->angle);
		ray.pos_x = vars->player->pos_x;
		ray.pos_y = vars->player->pos_y;
		impact_distance(&ray, vars, vars->base_angle + vars->angle * ray.nb);
		old_x = ray.dir_x;
		old_y = ray.dir_y;
		render_column(vars, &ray);
		i++;
	}
	return (1);
}

int	is_in_map(t_vars *vars, double pos_x, double pos_y)
{
	return (pos_x >= 0 && pos_y >= 0 && pos_x
		< (int)ft_strlen(vars->map[(int)pos_y])
		&& pos_y < vars->map_height);
}

void	increase_ray_distance(t_ray *ray, t_vars *vars)
{
	vars->actual_pos_x += ray->dir_x * 0.005;
	vars->actual_pos_y += ray->dir_y * 0.005;
	ray->hit_x = vars->actual_pos_x;
	ray->hit_y = vars->actual_pos_y;
}

void	impact_distance(t_ray *ray, t_vars *vars, double angle)
{
	vars->actual_pos_x = ray->pos_x;
	vars->actual_pos_y = ray->pos_y;
	while (is_in_map(vars, vars->actual_pos_x, vars->actual_pos_y))
	{
		ray->hit_x = vars->actual_pos_x;
		ray->hit_y = vars->actual_pos_y;
		if (vars->map[(int)vars->actual_pos_y][(int)vars->actual_pos_x] == '1')
		{
			check_for_north_orientation(vars, ray);
			check_for_south_orientation(vars, ray);
			check_for_east_orientation(vars, ray);
			check_for_west_orientation(vars, ray);
			ray->distance = sqrt(fabs(vars->actual_pos_x - ray->pos_x)
					* fabs(vars->actual_pos_x - ray->pos_x)
					+ fabs(vars->actual_pos_y - ray->pos_y)
					* fabs(vars->actual_pos_y - ray->pos_y)) * cos(angle);
			return ;
		}
		else
			increase_ray_distance(ray, vars);
	}
}
