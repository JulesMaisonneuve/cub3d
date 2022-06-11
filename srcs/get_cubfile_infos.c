/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cubfile_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 04:22:32 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/11 04:23:44 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

bool	check_first_char(t_vars *vars, t_utils *utils)
{
	if ((vars->c == 'C' || vars->c == 'F' || vars->c == 'N' || vars->c == 'S'
			|| vars->c == 'E' || vars->c == 'W') && utils->i == 0)
		return (true);
	return (false);
}

char	**read_line_infos(t_vars *vars, int fd, t_utils *utils)
{
	char	str[4096];
	char	**tmp;

	utils->is_info = false;
	utils->i = 0;
	utils->j = 0;
	tmp = NULL;
	while (read(fd, &vars->c, 1) == 1)
	{
		if (vars->c == '\n')
			break ;
		if (utils->i == 0)
			utils->is_info = check_first_char(vars, utils);
		if (vars->c == '1' && utils->i == 0)
		{
			vars->in_map = 1;
			return (NULL);
		}
		if (utils->is_info)
			str[utils->j++] = vars->c;
		utils->i++;
	}
	str[utils->j] = '\0';
	if (*str)
		tmp = ft_split(str, " ,");
	return (tmp);
}

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

bool	get_cubfile_infos(t_vars *vars, int fd, t_utils *utils)
{
	char	**tmp;

	tmp = NULL;
	tmp = read_line_infos(vars, fd, utils);
	if (tmp)
	{
		if ((**tmp == 'F' || **tmp == 'C') && tmp[0][1] == '\0')
			get_floor_ceiling_color(vars, tmp, utils);
		else if ((ft_strncmp(tmp[0], "NO", 2) == 0
				|| ft_strncmp(tmp[0], "SO", 2) == 0
				|| ft_strncmp(tmp[0], "EA", 2) == 0
				|| ft_strncmp(tmp[0], "WE", 2) == 0) && tmp[1])
		{
			if (ft_strncmp(tmp[0], "NO", 2) == 0)
				parse_texture(vars, tmp[1], 'N');
			else if (ft_strncmp(tmp[0], "SO", 2) == 0)
				parse_texture(vars, tmp[1], 'S');
			else if (ft_strncmp(tmp[0], "EA", 2) == 0)
				parse_texture(vars, tmp[1], 'E');
			else
				parse_texture(vars, tmp[1], 'W');
		}
	}
	free_tab(tmp);
	return (0);
}
