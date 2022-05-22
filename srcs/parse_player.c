#include "../cubed.h"

t_player *parse_player(t_vars *vars)
{
	t_player *player;
	int i;
	int j;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		printf("Malloc failed\n");
		return (NULL);
	}
	i = 0;
	while (i < vars->map_height)
	{
		j = 0;
		while (j < vars->map_width)
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S' || vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
			{
				player->pos_x = j;
				player->pos_y = i;
				switch (vars->map[i][j])
				{
					case 'N':
						player->dir_x = 0;
						player->dir_y = -1;
						break ;
					case 'S':
						player->dir_x = 0;
						player->dir_y = 1;
						break ;
					case 'E':
						player->dir_x = 1;
						player->dir_y = 0;
						break ;
					case 'W':
						player->dir_x = -1;
						player->dir_y = 0;
						break ;
				}
				vars->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	printf("pos_x : %lf\n", player->pos_x);
	printf("pos_y : %lf\n", player->pos_y);
	printf("dir_x : %lf\n", player->dir_x);
	printf("dir_y : %lf\n", player->dir_y);
	return (player);
}
