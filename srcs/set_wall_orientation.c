/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall_orientation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:20:04 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/12 04:20:49 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	check_for_north_orientation(t_vars *vars, t_ray *ray)
{
	double	dist_n;
	double	dist_s;
	double	dist_e;
	double	dist_w;

	dist_n = fmod(vars->actual_pos_y, 1.0);
	dist_s = 1 - fmod(vars->actual_pos_y, 1.0);
	dist_w = fmod(vars->actual_pos_x, 1.0);
	dist_e = 1 - fmod(vars->actual_pos_x, 1.0);
	if (dist_n <= dist_s && dist_n <= dist_w && dist_n <= dist_e)
	{
		ray->wall_orientation = 'N';
		if (vars->map[(int)vars->actual_pos_y - 1][(int)vars->actual_pos_x]
			== '1')
		{
			if (ray->dir_x > 0)
				ray->wall_orientation = 'W';
			else
				ray->wall_orientation = 'E';
		}
	}
}

void	check_for_south_orientation(t_vars *vars, t_ray *ray)
{
	double	dist_n;
	double	dist_s;
	double	dist_e;
	double	dist_w;

	dist_n = fmod(vars->actual_pos_y, 1.0);
	dist_s = 1 - fmod(vars->actual_pos_y, 1.0);
	dist_w = fmod(vars->actual_pos_x, 1.0);
	dist_e = 1 - fmod(vars->actual_pos_x, 1.0);
	if (dist_s <= dist_n && dist_s <= dist_w && dist_s <= dist_e)
	{
		ray->wall_orientation = 'S';
		if (vars->map[(int)vars->actual_pos_y + 1][(int)vars->actual_pos_x]
			== '1')
		{
			if (ray->dir_x > 0)
				ray->wall_orientation = 'W';
			else
				ray->wall_orientation = 'E';
		}
	}
}

void	check_for_east_orientation(t_vars *vars, t_ray *ray)
{
	double	dist_n;
	double	dist_s;
	double	dist_e;
	double	dist_w;

	dist_n = fmod(vars->actual_pos_y, 1.0);
	dist_s = 1 - fmod(vars->actual_pos_y, 1.0);
	dist_w = fmod(vars->actual_pos_x, 1.0);
	dist_e = 1 - fmod(vars->actual_pos_x, 1.0);
	if (dist_e <= dist_s && dist_e <= dist_n && dist_e <= dist_w)
	{
		ray->wall_orientation = 'E';
		if (vars->map[(int)vars->actual_pos_y][(int)vars->actual_pos_x + 1]
			== '1')
		{
			if (ray->dir_y > 0)
				ray->wall_orientation = 'N';
			else
				ray->wall_orientation = 'S';
		}
	}
}

void	check_for_west_orientation(t_vars *vars, t_ray *ray)
{
	double	dist_n;
	double	dist_s;
	double	dist_e;
	double	dist_w;

	dist_n = fmod(vars->actual_pos_y, 1.0);
	dist_s = 1 - fmod(vars->actual_pos_y, 1.0);
	dist_w = fmod(vars->actual_pos_x, 1.0);
	dist_e = 1 - fmod(vars->actual_pos_x, 1.0);
	if (dist_w <= dist_n && dist_w <= dist_s && dist_w <= dist_e)
	{
		ray->wall_orientation = 'W';
		if (vars->map[(int)vars->actual_pos_y][(int)vars->actual_pos_x - 1]
			== '1')
		{
			if (ray->dir_y > 0)
				ray->wall_orientation = 'N';
			else
				ray->wall_orientation = 'S';
		}
	}
}
