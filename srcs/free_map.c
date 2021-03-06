/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:37:33 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/13 03:04:54 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	free_textures(t_vars *vars)
{
	if (vars->textures != NULL)
	{
		if (vars->textures->texture_default)
			free(vars->textures->texture_default);
		if (vars->textures->texture_north && vars->textures->texture_north
			!= vars->textures->texture_default)
			free(vars->textures->texture_north);
		if (vars->textures->texture_south && vars->textures->texture_south
			!= vars->textures->texture_default)
			free(vars->textures->texture_south);
		if (vars->textures->texture_east && vars->textures->texture_east
			!= vars->textures->texture_default)
			free(vars->textures->texture_east);
		if (vars->textures->texture_west && vars->textures->texture_west
			!= vars->textures->texture_default)
			free(vars->textures->texture_west);
		free(vars->textures);
	}
}

int	free_map(t_vars *vars)
{
	int	i;

	i = -1;
	if (vars->map != NULL)
	{
		while (++i < vars->map_height)
			free(vars->map[i]);
		free(vars->map);
	}
	if (vars->player != NULL)
		free(vars->player);
	free_textures(vars);
	return (-1);
}
