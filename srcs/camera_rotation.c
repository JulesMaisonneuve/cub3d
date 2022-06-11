/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:32:53 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/11 01:35:17 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	camera_rotate_left(t_vars *vars)
{
	double	angle;
	double	old_x;
	double	old_y;

	old_x = vars->player->dir_x;
	old_y = vars->player->dir_y;
	angle = PI / 10;
	vars->player->dir_x = old_x * cos(angle * 0.095)
		- old_y * sin(angle * 0.095);
	vars->player->dir_y = old_x * sin(angle * 0.095)
		+ old_y * cos(angle * 0.095);
}

void	camera_rotate_right(t_vars *vars)
{
	double	angle;
	double	old_x;
	double	old_y;

	old_x = vars->player->dir_x;
	old_y = vars->player->dir_y;
	angle = PI / 10;
	vars->player->dir_x = old_x * cos(angle * -0.095)
		- old_y * sin(angle * -0.095);
	vars->player->dir_y = old_x * sin(angle * -0.095)
		+ old_y * cos(angle * -0.095);
}
