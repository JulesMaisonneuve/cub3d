#include "../cubed.h"

void	init_vars(t_vars *vars)
{
	vars->player = 0;
	vars->map_width = 0;
	vars->map_height = 1;
	vars->actual_col_count = 0;
}

void	init_errors(t_errors *errors)
{
	errors->error1 = 0;
	errors->error2 = 0;
	errors->error3 = 0;
	errors->error4 = 0;
	errors->error5 = 0;
}

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


int main(int argc, char **argv)
{
	t_vars vars;
	t_errors errors;

	if (argc != 2)
		return (-1);
	vars.path = argv[1];
	if (is_valid_file(&vars) == -1)
		return (-1);
	init_vars(&vars);
	init_errors(&errors);
	vars.fd = open(vars.path, O_RDONLY);
	if (vars.fd < 0)
		return (-1);
	is_valid_map(vars.fd, &vars, &errors);
	close(vars.fd);
	if (errors.error5 == 1)
		return (0);
	check_error(&vars, &errors);
	if (errors.error1 == 1 || errors.error2 == 1
		|| errors.error3 == 1 || errors.error4 == 1)
		return (print_error(&errors, &vars));
	parse_player(&vars);
	return (0);
}
