/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cubfile_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 04:22:32 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/15 03:15:17 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	get_floor_ceiling_color(t_vars *vars, char **tmp, t_utils *utils)
{
	int	color;

	utils->r = 0;
	utils->g = 0;
	utils->b = 0;
	if (tmp[1])
	{
		if (is_digit(tmp[1]))
			utils->r = ft_atoi(tmp[1]);
	}
	if (tmp[2])
	{
		if (is_digit(tmp[2]))
			utils->g = ft_atoi(tmp[2]);
	}
	if (tmp[3])
	{
		if (is_digit(tmp[3]))
			utils->b = ft_atoi(tmp[3]);
	}
	color = create_trgb(0, utils->r, utils->g, utils->b);
	if (**tmp == 'F')
		vars->floor_color = color;
	else
		vars->ceiling_color = color;
}

void	fill_texture_infos(t_vars *vars, char **tmp, t_utils *utils,
	t_errors *errors)
{
	if (ft_strncmp(tmp[0], "NO", 3) == 0)
	{
		if (parse_texture(vars, tmp[1], 'N', utils) == -1)
			errors->error4 = 1;
	}
	else if (ft_strncmp(tmp[0], "SO", 3) == 0)
	{
		if (parse_texture(vars, tmp[1], 'S', utils) == -1)
			errors->error4 = 1;
	}
	else if (ft_strncmp(tmp[0], "EA", 3) == 0)
	{
		if (parse_texture(vars, tmp[1], 'E', utils) == -1)
			errors->error4 = 1;
	}
	else
	{
		if (parse_texture(vars, tmp[1], 'W', utils) == -1)
			errors->error4 = 1;
	}
}

bool	get_cubfile_infos(t_vars *vars, int fd, t_utils *utils,
	t_errors *errors)
{
	char	**tmp;

	tmp = NULL;
	tmp = read_line_infos(vars, fd, utils);
	if (tmp)
	{
		if ((**tmp == 'F' || **tmp == 'C') && tmp[0][1] == '\0')
			get_floor_ceiling_color(vars, tmp, utils);
		else if ((ft_strncmp(tmp[0], "NO", 3) == 0
				|| ft_strncmp(tmp[0], "SO", 3) == 0
				|| ft_strncmp(tmp[0], "EA", 3) == 0
				|| ft_strncmp(tmp[0], "WE", 3) == 0) && tmp[1])
			fill_texture_infos(vars, tmp, utils, errors);
	}
	free_tab(tmp);
	return (0);
}
