/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:27:49 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/10 20:34:06 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	key_hook(int keycode, t_vars *vars)
{
	double	angle;
	double	old_x;
	double	old_y;

	old_x = vars->player->dir_x;
	old_y = vars->player->dir_y;
	angle = PI / 10;
	if (keycode == ESC)
	{
		printf("You quit the game\n");
		close_win(vars);
	}
	if (keycode == 'z' || keycode == 's' || keycode == 'q' || keycode == 'd'
		|| keycode == 'a' || keycode == 'e' || keycode == 'p')
	{
		if (keycode == 'a')
		{
			vars->player->dir_x = old_x * cos(angle * 0.095)
				- old_y * sin(angle * 0.095);
			vars->player->dir_y = old_x * sin(angle * 0.095)
				+ old_y * cos(angle * 0.095);
		}
		else if (keycode == 's')
		{
			if ((vars->player->pos_x + -0.055 * vars->player->dir_x) > 1
				&& (vars->player->pos_x + -0.055 * vars->player->dir_x)
				< vars->map_width - 1)
				vars->player->pos_x += -0.055 * vars->player->dir_x;
			if ((vars->player->pos_y + -0.055 * vars->player->dir_y) > 1
				&& (vars->player->pos_y + -0.055 * vars->player->dir_y)
				< vars->map_height - 1)
				vars->player->pos_y += -0.055 * vars->player->dir_y;
		}
		else if (keycode == 'z')
		{
			if ((vars->player->pos_x + 0.055 * vars->player->dir_x) > 1
				&& (vars->player->pos_x + 0.055 * vars->player->dir_x)
				< vars->map_width - 1)
				vars->player->pos_x += 0.055 * vars->player->dir_x;
			if ((vars->player->pos_y + 0.055 * vars->player->dir_y) > 1
				&& (vars->player->pos_y + 0.055 * vars->player->dir_y)
				< vars->map_height - 1)
				vars->player->pos_y += 0.055 * vars->player->dir_y;
		}
		else if (keycode == 'q')
		{
			if ((((vars->player->dir_x * cos(PI / 2) - vars->player->dir_y * sin(PI / 2)) * 0.040) + vars->player->pos_x) > 1
				&& (((vars->player->dir_x * cos(PI / 2) - vars->player->dir_y * sin(PI / 2)) * 0.040) + vars->player->pos_x) < vars->map_width - 1)
				vars->player->pos_x += (vars->player->dir_x * cos(PI / 2) - vars->player->dir_y * sin(PI / 2)) * 0.040;
			if ((((vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * 0.040) + vars->player->pos_y) > 1
				&& (((vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * 0.040) + vars->player->pos_y) < vars->map_height - 1)
				vars->player->pos_y += (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * 0.040;
		}
		else if (keycode == 'd')
		{
			if ((vars->player->pos_x + (vars->player->dir_x * cos(PI / 2) - vars->player->dir_y * sin(PI / 2)) * -0.040) < vars->map_width - 1
				&& (vars->player->pos_x + (vars->player->dir_x * cos(PI / 2) - vars->player->dir_y * sin(PI / 2)) * -0.040) > 1)
					vars->player->pos_x += (vars->player->dir_x * cos(PI / 2) - vars->player->dir_y * sin(PI / 2)) * -0.040;
			if ((vars->player->pos_y + (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * -0.040) < vars->map_height - 1
				&& (vars->player->pos_y + (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * -0.040) > 1)
					vars->player->pos_y += (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * -0.040;
		}
		else if (keycode == 'e')
		{
			vars->player->dir_x = old_x * cos(angle * -0.095) - old_y * sin(angle * -0.095);
			vars->player->dir_y = old_x * sin(angle * -0.095) + old_y * cos(angle * -0.095);
		}
		else if (keycode == 'p')
			vars->is_fire = true;
	}
	return (0);
}
