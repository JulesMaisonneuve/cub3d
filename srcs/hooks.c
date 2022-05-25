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
	if (keycode == 'z' || keycode == 's' || keycode == 'q' || keycode == 'd' || keycode == 'v')
	{
		if (keycode == 'q')
		{
			vars->player->dir_x = oldX * cos(angle * 0.095) - oldY * sin(angle * 0.095); // On multiplie le résultat de player dir_x par 0.095 pour obtenir la vitesse de la caméra
			vars->player->dir_y = oldX * sin(angle * 0.095) + oldY * cos(angle * 0.095);
		}
		else if (keycode == 's')
		{
			vars->player->pos_x += -0.055 * vars->player->dir_x;	// Même chose ici pour obtenir la vitesse de déplacement du joueur
			vars->player->pos_y += -0.055 * vars->player->dir_y;
		}
		else if (keycode == 'z')
		{
			vars->player->pos_x += 0.055 * vars->player->dir_x;		
			vars->player->pos_y += 0.055 * vars->player->dir_y;
		}
		else if (keycode == 'v')
		{
			vars->player->pos_x += -0.055 * vars->player->dir_x; // TO DO : straffer -> cercle trigo
		}
		else if (keycode == 'd')
		{
			vars->player->dir_x = oldX * cos(angle * -0.095) - oldY * sin(angle * -0.095);
			vars->player->dir_y = oldX * sin(angle * -0.095) + oldY * cos(angle * -0.095);
		}
		ray_casting(vars);
	}
	return (0);
}
