/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 04:39:28 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/13 16:16:35 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	player_move_forward(t_vars *vars)
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

void	player_move_backward(t_vars *vars)
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

void	player_move_left(t_vars *vars)
{
	if ((((vars->player->dir_x * cos(PI / 2)
					- vars->player->dir_y * sin(PI / 2)) * 0.040)
			+ vars->player->pos_x) > 1
		&& (((vars->player->dir_x * cos(PI / 2)
					- vars->player->dir_y * sin(PI / 2)) * 0.040)
			+ vars->player->pos_x) < vars->map_width - 1)
			vars->player->pos_x += (vars->player->dir_x * cos(PI / 2)
				- vars->player->dir_y * sin(PI / 2)) * 0.040;
	if ((((vars->player->dir_x * sin(PI / 2)
					+ vars->player->dir_y * cos(PI / 2)) * 0.040)
			+ vars->player->pos_y) > 1
		&& (((vars->player->dir_x * sin(PI / 2)
					+ vars->player->dir_y * cos(PI / 2)) * 0.040)
			+ vars->player->pos_y) < vars->map_height - 1)
			vars->player->pos_y += (vars->player->dir_x * sin(PI / 2)
				+ vars->player->dir_y * cos(PI / 2)) * 0.040;
}

void	player_move_right(t_vars *vars)
{
	if ((vars->player->pos_x + (vars->player->dir_x * cos(PI / 2)
				- vars->player->dir_y * sin(PI / 2)) * -0.040)
		< vars->map_width - 1
		&& (vars->player->pos_x + (vars->player->dir_x * cos(PI / 2)
				- vars->player->dir_y * sin(PI / 2)) * -0.040) > 1)
			vars->player->pos_x += (vars->player->dir_x * cos(PI / 2)
				- vars->player->dir_y * sin(PI / 2)) * -0.040;
	if ((vars->player->pos_y + (vars->player->dir_x * sin(PI / 2)
				+ vars->player->dir_y * cos(PI / 2)) * -0.040)
		< vars->map_height - 1
		&& (vars->player->pos_y + (vars->player->dir_x * sin(PI / 2)
				+ vars->player->dir_y * cos(PI / 2)) * -0.040) > 1)
			vars->player->pos_y += (vars->player->dir_x * sin(PI / 2)
				+ vars->player->dir_y * cos(PI / 2)) * -0.040;
}
