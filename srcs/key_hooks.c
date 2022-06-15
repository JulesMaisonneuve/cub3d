/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:27:49 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/11 01:21:40 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
	{
		printf("You quit the game\n");
		close_win(vars);
	}
	if (keycode == 'w' || keycode == 's' || keycode == 'a' || keycode == 'd'
		|| keycode == 'q' || keycode == 'e' || keycode == 'p')
	{
		if (keycode == 'q')
			camera_rotate_left(vars);
		if (keycode == 'w')
			player_move_forward(vars);
		if (keycode == 's')
			player_move_backward(vars);
		if (keycode == 'a')
			player_move_left(vars);
		if (keycode == 'd')
			player_move_right(vars);
		if (keycode == 'e')
			camera_rotate_right(vars);
		if (keycode == 'p')
			vars->is_fire = true;
	}
	return (0);
}
