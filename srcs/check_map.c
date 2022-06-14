/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:05:04 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/14 03:54:38 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	check_comps(t_vars *vars, t_errors *errors)
{
	if (vars->c != '0' && vars->c != '1' && vars->c != 'N' && vars->c != 'S'
		&& vars->c != 'E' && vars->c != 'W'
		&& vars->c != '\n' && vars-> c != ' ')
		errors->error2 = 1;
	else if (vars->c == 'N')
		vars->p += 1;
	else if (vars->c == 'S')
		vars->p += 1;
	else if (vars->c == 'E')
		vars->p += 1;
	else if (vars->c == 'W')
		vars->p += 1;
}

int	check_current_line(t_vars *vars)
{
	if (vars->c == '\n')
	{
		if (vars->map_width == 0)
			vars->map_width = vars->actual_col_count;
		vars->actual_col_count = 0;
		vars->map_height++;
	}
	else
	{
		if (vars->c != ' ')
			vars->actual_col_count++;
	}
	return (0);
}

void	is_valid_map(int fd, t_vars *vars, t_errors *errors, t_utils *utils)
{
	int	error;

	error = 0;
	vars->in_map = 0;
	while (vars->in_map != 1)
	{
		get_cubfile_infos(vars, fd, utils);
		vars->line_offset++;
	}
	if (vars->in_map == 1)
		vars->actual_col_count++;
	while (read(fd, &vars->c, 1) == 1)
	{
		check_comps(vars, errors);
		error = check_current_line(vars);
		if (error == 1)
			break ;
	}
}
