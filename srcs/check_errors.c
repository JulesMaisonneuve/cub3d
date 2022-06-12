/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:14:11 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/11 22:04:50 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	store_map(t_vars *vars, t_utils *utils, int line_offset)
{
	char	*tmp;

	tmp = NULL;
	utils->i = 0;
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
		remove_white_space(vars->map[utils->i]);
		utils->i++;
		line_offset++;
	}
}

int	check_error(t_vars *vars, t_errors *errors, t_utils *utils, int line_offset)
{
	vars->fd = open(vars->path, O_RDONLY);
	if (vars->fd < 0)
		return (-1);
	vars->map = malloc(vars->map_height * sizeof(char *));
	if (!vars->map)
		return (0);
	store_map(vars, utils, line_offset);
	if (is_rectangular(vars, errors) == -1)
		return (-1);
	if (ft_strchrr(vars->map[0], '1') == 0
		|| ft_strchrr(vars->map[vars->map_height - 1], '1') == 0)
		errors->error1 = 1;
	if (vars->p != 1)
		errors->error3 = 1;
	close(vars->fd);
	return (0);
}
