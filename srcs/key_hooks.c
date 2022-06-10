/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:27:49 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/11 00:16:36 by jumaison         ###   ########.fr       */
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
	if (keycode == 'z' || keycode == 's' || keycode == 'q' || keycode == 'd'
		|| keycode == 'a' || keycode == 'e' || keycode == 'p')
	{
		if (keycode == 'a')
			camera_rotate_left(vars);
		else if (keycode == 'z')
			player_move_forward(vars);
		else if (keycode == 's')
			player_move_backward(vars);
		else if (keycode == 'q')
			player_move_left(vars);
		else if (keycode == 'd')
			player_move_right(vars);
		else if (keycode == 'e')
			camera_rotate_right(vars);
		else if (keycode == 'p')
			vars->is_fire = true;
	}
	return (0);
}
