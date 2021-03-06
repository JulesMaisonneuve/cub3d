/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:32:10 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/14 04:23:28 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	fill_player_infos(t_vars *vars, int i, int j)
{
	if (vars->map[i][j] == 'N')
	{
		vars->player->dir_x = 0;
		vars->player->dir_y = -1;
	}
	else if (vars->map[i][j] == 'S')
	{
		vars->player->dir_x = 0;
		vars->player->dir_y = 1;
	}
	else if (vars->map[i][j] == 'E')
	{
		vars->player->dir_x = 1;
		vars->player->dir_y = 0;
	}
	else if (vars->map[i][j] == 'W')
	{
		vars->player->dir_x = -1;
		vars->player->dir_y = 0;
	}
}

void	get_player_infos(t_vars *vars)
{
	int	i;
	int	j;

	vars->player = malloc(sizeof(t_player));
	i = 0;
	while (i < vars->map_height)
	{
		j = 0;
		while (j < (int)ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S'
				|| vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
			{
				vars->player->pos_x = j;
				printf("vars player pos x: %lf\n", vars->player->pos_x);
				vars->player->pos_y = i;
				fill_player_infos(vars, i, j);
				vars->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return ;
}
