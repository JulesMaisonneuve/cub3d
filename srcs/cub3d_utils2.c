/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:49:12 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/14 01:45:52 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	remove_white_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			str[j++] = str[i];
		}
		else
			str[j++] = '1';
		i++;
	}
	str[j] = '\0';
}

double	get_wall_offset(t_ray *ray)
{
	if (ray->wall_orientation == 'N')
		return (1 - fmod(ray->hit_x, 1));
	else if (ray->wall_orientation == 'S')
		return (fmod(ray->hit_x, 1));
	else if (ray->wall_orientation == 'E')
		return (1 - fmod(ray->hit_y, 1));
	else if (ray->wall_orientation == 'W')
		return (fmod(ray->hit_y, 1));
	return (0);
}

t_texture_details	*check_wall_orientation(t_vars *vars, t_ray *ray)
{
	t_texture_details	*texture_details;

	if (ray->wall_orientation == 'N')
		texture_details = vars->textures->texture_north;
	else if (ray->wall_orientation == 'S')
		texture_details = vars->textures->texture_south;
	else if (ray->wall_orientation == 'E')
		texture_details = vars->textures->texture_east;
	else
		texture_details = vars->textures->texture_west;
	return (texture_details);
}
