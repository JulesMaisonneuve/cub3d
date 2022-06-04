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
	if (keycode == 'z' || keycode == 's' || keycode == 'q' || keycode == 'd' || keycode == 'a' || keycode == 'e' || keycode == 'p')
	{
		if (keycode == 'a')
		{
			vars->player->dir_x = oldX * cos(angle * 0.095) - oldY * sin(angle * 0.095); // On multiplie le résultat de player dir_x par 0.095 pour obtenir la vitesse de la caméra
			vars->player->dir_y = oldX * sin(angle * 0.095) + oldY * cos(angle * 0.095);
		}
		else if (keycode == 's')
		{
			if ((vars->player->pos_x + -0.055 * vars->player->dir_x) > 1 && (vars->player->pos_x + -0.055 * vars->player->dir_x) < vars->map_width - 1)
				vars->player->pos_x += -0.055 * vars->player->dir_x;	// Même chose ici pour obtenir la vitesse de déplacement du joueur
			if ((vars->player->pos_y + -0.055 * vars->player->dir_y) > 1 && (vars->player->pos_y + -0.055 * vars->player->dir_y) < vars->map_height - 1)
				vars->player->pos_y += -0.055 * vars->player->dir_y;
		}
		else if (keycode == 'z')
		{
			if ((vars->player->pos_x + 0.055 * vars->player->dir_x) > 1 && (vars->player->pos_x + 0.055 * vars->player->dir_x) < vars->map_width - 1)
				vars->player->pos_x += 0.055 * vars->player->dir_x;
			if ((vars->player->pos_y + 0.055 * vars->player->dir_y) > 1 && (vars->player->pos_y + 0.055 * vars->player->dir_y) < vars->map_height - 1)
				vars->player->pos_y += 0.055 * vars->player->dir_y;
		}
		else if (keycode == 'q')
		{
			if ((((vars->player->dir_x * cos(PI / 2 ) - vars->player->dir_y * sin(PI / 2)) * 0.040) + vars->player->pos_x) > 1
				&& (((vars->player->dir_x * cos(PI / 2 ) - vars->player->dir_y * sin(PI / 2)) * 0.040) + vars->player->pos_x) < vars->map_width - 1)
				vars->player->pos_x += (vars->player->dir_x * cos(PI / 2 ) - vars->player->dir_y * sin(PI / 2)) * 0.040;
			if ((((vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * 0.040) + vars->player->pos_y) > 1
				&& (((vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * 0.040) + vars->player->pos_y) < vars->map_height - 1)
				vars->player->pos_y += (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * 0.040;
		}
		else if (keycode == 'd')
		{
			if ((vars->player->pos_x + (vars->player->dir_x * cos(PI / 2 ) - vars->player->dir_y * sin(PI / 2)) * -0.040) < vars->map_width - 1
				&& (vars->player->pos_x + (vars->player->dir_x * cos(PI / 2 ) - vars->player->dir_y * sin(PI / 2)) * -0.040) > 1)
				vars->player->pos_x += (vars->player->dir_x * cos(PI / 2 ) - vars->player->dir_y * sin(PI / 2)) * -0.040;
			if ((vars->player->pos_y + (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * -0.040) < vars->map_height - 1
				&& (vars->player->pos_y += (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * -0.040) > 1)
				vars->player->pos_y += (vars->player->dir_x * sin(PI / 2) + vars->player->dir_y * cos(PI / 2)) * -0.040;
		}
		else if (keycode == 'e')
		{
			vars->player->dir_x = oldX * cos(angle * -0.095) - oldY * sin(angle * -0.095);
			vars->player->dir_y = oldX * sin(angle * -0.095) + oldY * cos(angle * -0.095);
		}
		else if (keycode == 'p')
		{
			vars->is_fire = true;
		}
	}
	return (0);
}
