#include "../cubed.h"

int	key_hook(int keycode, t_vars *vars)
{
	double angle;
	double oldX;
	double oldY;

	oldX = vars->player->dir_x;
	oldY = vars->player->dir_y;
	angle = PI / 10;
	if (keycode == ESC)
	{
		printf("You quit the game\n");
		close_win(vars);
	}
	if (keycode == 'z' || keycode == 's' || keycode == 'q' || keycode == 'd')
	{
		if (keycode == 'q')
		{
			vars->player->dir_x = oldX * cos(angle) - oldY * sin(angle);
			vars->player->dir_y = oldX * sin(angle) + oldY * cos(angle);
		}
		else if (keycode == 's')
		{
			vars->player->pos_x += -0.5 * vars->player->dir_x;
			vars->player->pos_y += -0.5 * vars->player->dir_y;
		}
		else if (keycode == 'z')
		{
			vars->player->pos_x += 0.5 * vars->player->dir_x;
			vars->player->pos_y += 0.5 * vars->player->dir_y;
		}
		else if (keycode == 'd')
		{
			vars->player->dir_x = oldX * cos(angle * -1) - oldY * sin(angle * -1);
			vars->player->dir_y = oldX * sin(angle * -1) + oldY * cos(angle * -1);
		}
		ray_casting(vars);
	}
	return (0);
}
