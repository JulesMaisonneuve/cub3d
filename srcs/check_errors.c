/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:14:11 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/15 03:39:29 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	walls_only(t_vars *vars, t_utils *utils)
{
	if (utils->i == 0)
	{
		if (ft_strchrr(vars->map[utils->i], '1') == 0)
			return (0);
	}
	else if (utils->i + 1 == vars->map_height)
	{
		if (ft_strchrr(vars->map[utils->i], '1') == 0)
			return (0);
	}
	return (1);
}

int	is_map_closed(t_vars *vars, t_utils *utils, t_errors *errors)
{
	utils->j = 0;
	utils->i = 0;
	while (utils->i < vars->map_height)
	{
		utils->j = 0;
		while (vars->map[utils->i][utils->j])
		{
			if (handle_space(vars, utils, errors) == -1)
				return (0);
			utils->j++;
		}
		remove_white_space(vars->map[utils->i]);
		if (walls_only(vars, utils) != 1)
			return (0);
		if (vars->map[utils->i][(int)ft_strlen(vars->map[utils->i]) - 1] != '1'
			&& vars->map[utils->i][0] != '\0')
			return (0);
		if (line_size_difference(vars, utils, errors) == -1)
			return (0);
		utils->i++;
	}
	return (1);
}

int	store_map(t_vars *vars, t_utils *utils, int line_offset, t_errors *errors)
{
	char	*tmp;
	int		empty;

	tmp = NULL;
	utils->i = 0;
	empty = 0;
	while (utils->i < line_offset)
	{
		get_next_line(vars->fd, &tmp);
		free(tmp);
		tmp = NULL;
		utils->i++;
	}
	utils->i = 0;
	while (utils->i < vars->map_height)
	{
		get_next_line(vars->fd, &vars->map[utils->i]);
		utils->i++;
		line_offset++;
	}
	if (is_map_closed(vars, utils, errors) != 1)
		return (-1);
	return (0);
}

int	check_error(t_vars *vars, t_errors *errors, t_utils *utils, int line_offset)
{
	vars->fd = open(vars->path, O_RDONLY);
	if (vars->fd < 0)
		return (-1);
	vars->map = malloc(vars->map_height * sizeof(char *));
	if (!vars->map)
		return (0);
	if (store_map(vars, utils, line_offset, errors) != 0)
	{
		errors->error1 = 1;
	}
	if (vars->p != 1)
		errors->error3 = 1;
	close(vars->fd);
	return (0);
}
