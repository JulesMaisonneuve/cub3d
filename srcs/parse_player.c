#include "../cubed.h"

void parse_player(t_vars *vars)
{
	int i;
	int j;

	vars->player = malloc(sizeof(t_player));
	i = 0;
	while (i < vars->map_height)
	{
		j = 0;
		while (j < vars->map_width)
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S' || vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
			{
				vars->player->pos_x = j;
				vars->player->pos_y = i;
				switch (vars->map[i][j])
				{
					case 'N':
						vars->player->dir_x = 0;
						vars->player->dir_y = -1;
						break ;
					case 'S':
						vars->player->dir_x = 0;
						vars->player->dir_y = 1;
						break ;
					case 'E':
						vars->player->dir_x = 1;
						vars->player->dir_y = 0;
						break ;
					case 'W':
						vars->player->dir_x = -1;
						vars->player->dir_y = 0;
						break ;
				}
				vars->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return ;
}
