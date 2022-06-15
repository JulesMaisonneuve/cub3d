/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_size_difference.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:39:16 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/15 03:39:16 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	handle_longer(t_vars *vars, t_utils *utils, t_errors *errors,
	int difference)
{
	int	i;

	i = 0;
	while (i < difference)
	{
		if (vars->map[utils->i][(int)ft_strlen(vars->map[utils->i + 1])
			+ i] != '1' && vars->map[utils->i]
			[(int)ft_strlen(vars->map[utils->i + 1]) + i] != ' ')
		{
			errors->error1 = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	handle_shorter(t_vars *vars, t_utils *utils, t_errors *errors,
	int difference)
{
	int	i;

	i = 0;
	while (i < difference)
	{
		if (vars->map[utils->i + 1][(int)ft_strlen(vars->map[utils->i])
			+ i] != '1' && vars->map[utils->i + 1]
		[(int)ft_strlen(vars->map[utils->i]) + i] != ' ')
		{
			errors->error1 = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	line_size_difference(t_vars *vars, t_utils *utils, t_errors *errors)
{
	int		difference;
	bool	longer;
	int		i;

	difference = 0;
	longer = true;
	i = 0;
	if (utils->i + 1 != vars->map_height)
		difference = (int)ft_strlen(vars->map[utils->i])
			- (int)ft_strlen(vars->map[utils->i + 1]);
	if (difference < 0)
	{
		longer = false;
		difference *= -1;
	}
	if (difference != 0)
	{
		if (longer)
			return (handle_longer(vars, utils, errors, difference));
		else
			return (handle_shorter(vars, utils, errors, difference));
	}
	return (0);
}
