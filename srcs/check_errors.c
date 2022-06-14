/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:14:11 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/14 04:35:24 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	line_size_difference(t_vars *vars, t_utils *utils, t_errors *errors)
{
	int	difference;
	bool longer;
	int	i;

	difference = 0;
	longer = true;
	i = 0;
	if (utils->i + 1 != vars->map_height)
		difference = (int)ft_strlen(vars->map[utils->i]) - (int)ft_strlen(vars->map[utils->i + 1]);
	if (difference < 0)
	{
		longer = false;
		difference *= -1;
	}
	if (difference != 0)
	{
		if (longer)
		{
			while (i < difference)
			{
				if (vars->map[utils->i][(int)ft_strlen(vars->map[utils->i + 1]) + i] != '1' && vars->map[utils->i][(int)ft_strlen(vars->map[utils->i + 1]) + i] != ' ')
				{
					errors->error1 = 1;
					return (-1);
				}
				i++;
			}
		}
		else
		{
			while (i < difference)
			{
				if (vars->map[utils->i + 1][(int)ft_strlen(vars->map[utils->i]) + i] != '1' && vars->map[utils->i + 1][(int)ft_strlen(vars->map[utils->i]) + i] != ' ')
				{
					errors->error1 = 1;
					return (-1);
				}
				i++;
			}
		}
	}
	return (0);
}

int	is_map_closed(t_vars *vars, t_utils *utils, t_errors *errors)
{
	int j;

	j = 0;
	utils->i = 0;
	while (utils->i < vars->map_height)
	{
		j = 0;
		while (vars->map[utils->i][j])
		{
			if (vars->map[utils->i][j] == ' ')
			{
				if (utils->i == 0)
				{
					while (vars->map[utils->i][j] && vars->map[utils->i][j] == ' ')
					{
						if (j > 0 && vars->map[utils->i][j - 1] != '1' && vars->map[utils->i][j - 1] != ' ')
						{
							errors->error1 = 1;
							return (0);
						}
						else if (vars->map[utils->i][j + 1] && vars->map[utils->i][j + 1] != '1' && vars->map[utils->i][j + 1] != ' ')
						{
							errors->error1 = 1;
							return (0);
						}
						else if (vars->map[utils->i + 1][j] && vars->map[utils->i + 1][j] != '1' && vars->map[utils->i + 1][j] != ' ')
						{
							errors->error1 = 1;
							return (0);
						}
						j++;
					}
				}
				else if (utils->i + 1 == vars->map_height)
				{
					if (j > 0 && vars->map[utils->i][j - 1] != '1' && vars->map[utils->i][j - 1] != ' ')
					{
						errors->error1 = 1;
						return (0);
					}
					else if (vars->map[utils->i][j + 1] && vars->map[utils->i][j + 1] != '1' && vars->map[utils->i][j + 1] != ' ')
					{
						errors->error1 = 1;
						return (0);
					}
					else if (vars->map[utils->i - 1][j] && vars->map[utils->i - 1][j] != '1' && vars->map[utils->i - 1][j] != ' ')
					{
						errors->error1 = 1;
						return (0);
					}
				}
				else
				{
					if (j > 0 && vars->map[utils->i][j - 1] != '1' && vars->map[utils->i][j - 1] != ' ')
					{
						errors->error1 = 1;
						return (0);
					}
					else if (vars->map[utils->i][j + 1] && vars->map[utils->i][j + 1] != '1' && vars->map[utils->i][j + 1] != ' ')
					{
						errors->error1 = 1;
						return (0);
					}
					else if (vars->map[utils->i + 1][j] && vars->map[utils->i + 1][j] != '1' && vars->map[utils->i + 1][j] != ' ')
					{
						errors->error1 = 1;
						return (0);
					}
					else if (vars->map[utils->i - 1][j] != '1' && vars->map[utils->i - 1][j] != ' ')
					{
						errors->error1 = 1;
						return (0);
					}
				}
			}
			j++;
		}
		remove_white_space(vars->map[utils->i]);
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
		if (vars->map[utils->i][0] == '\0' && utils->i + 1 != vars->map_height)
		{
			printf("Error: newline only accepted at end of file\n");
			return (-1);
		}
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
		errors->error1 = 1;
	if (ft_strchrr(vars->map[0], '1') == 0
		|| ft_strchrr(vars->map[vars->map_height - 1], '1') == 0)
		errors->error1 = 1;
	if (vars->p != 1)
		errors->error3 = 1;
	close(vars->fd);
	return (0);
}
