/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:35:44 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/15 03:37:01 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	check_first_line(t_vars *vars, t_utils *utils, t_errors *errors)
{
	errors->error1 = 1;
	if (vars->map[utils->i][utils->j]
		&& vars->map[utils->i][utils->j] == ' ')
	{
		if (utils->j > 0 && vars->map[utils->i][utils->j - 1]
			!= '1' && vars->map[utils->i][utils->j - 1] != ' ')
			return (-1);
		if (utils->j + 1 <= (int)ft_strlen(vars->map[utils->i]) - 1
			&& vars->map[utils->i][utils->j + 1] != '\n'
			&& vars->map[utils->i][utils->j + 1] != '1'
			&& vars->map[utils->i][utils->j + 1] != ' ')
			return (-1);
		if ((int)ft_strlen(vars->map[utils->i])
			<= (int)ft_strlen(vars->map[utils->i + 1])
			&& vars->map[utils->i + 1][utils->j] != '\n'
			&& vars->map[utils->i + 1][utils->j] != '1'
			&& vars->map[utils->i + 1][utils->j] != ' ')
			return (-1);
	}
	errors->error1 = 0;
	return (0);
}

int	check_last_line(t_vars *vars, t_utils *utils, t_errors *errors)
{
	if (utils->j > 0 && vars->map[utils->i][utils->j - 1] != '1'
		&& vars->map[utils->i][utils->j - 1] != ' ')
	{
		errors->error1 = 1;
		return (-1);
	}
	if (utils->j + 1 <= (int)ft_strlen(vars->map[utils->i])
		&& vars->map[utils->i][utils->j + 1] != '\0'
		&& vars->map[utils->i][utils->j + 1] != '1'
		&& vars->map[utils->i][utils->j + 1] != ' ')
	{
		errors->error1 = 1;
		return (-1);
	}
	if ((int)ft_strlen(vars->map[utils->i - 1]) >= utils->j
		&& vars->map[utils->i - 1][utils->j] != '\0'
		&& vars->map[utils->i - 1][utils->j] != '1'
		&& vars->map[utils->i - 1][utils->j] != ' ')
	{
		errors->error1 = 1;
		return (-1);
	}
	return (0);
}

int	check_in_map_line(t_vars *vars, t_utils *utils, t_errors *errors)
{
	errors->error1 = 1;
	if (utils->j > 0 && vars->map[utils->i][utils->j - 1] != '1'
		&& vars->map[utils->i][utils->j - 1] != ' ')
		return (-1);
	else if (utils->j + 1 < (int)ft_strlen(vars->map[utils->i])
		&& vars->map[utils->i][utils->j + 1] != '\0'
		&& vars->map[utils->i][utils->j + 1] != '1'
		&& vars->map[utils->i][utils->j + 1] != ' ')
		return (-1);
	else if (utils->j < (int)ft_strlen(vars->map[utils->i + 1])
		&& vars->map[utils->i + 1][utils->j] != '\0'
		&& vars->map[utils->i + 1][utils->j] != '1'
		&& vars->map[utils->i + 1][utils->j] != ' ')
		return (-1);
	else if (utils->j < (int)ft_strlen(vars->map[utils->i - 1])
		&& vars->map[utils->i - 1][utils->j] != '\0'
		&& vars->map[utils->i - 1][utils->j] != '1'
		&& vars->map[utils->i - 1][utils->j] != ' ')
		return (-1);
	errors->error1 = 0;
	return (0);
}

int	handle_space(t_vars *vars, t_utils *utils, t_errors *errors)
{
	if (vars->map[utils->i][utils->j] == ' ')
	{
		if (utils->i == 0)
		{
			if (check_first_line(vars, utils, errors) == -1)
				return (-1);
		}
		else if (utils->i + 1 == vars->map_height)
		{
			if (check_last_line(vars, utils, errors) == -1)
			{
				return (-1);
			}
		}
		else
		{
			if (check_in_map_line(vars, utils, errors) == -1)
			{
				return (-1);
			}
		}
	}
	return (0);
}
