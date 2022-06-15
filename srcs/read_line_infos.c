/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_infos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:13:58 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/15 03:14:03 by jumaison         ###   ########.fr       */
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

int	check_in_map(t_vars *vars, t_utils *utils)
{
	if (vars->c == '1' && utils->i == 0)
	{
		vars->in_map = 1;
		return (1);
	}
	return (0);
}

char	**read_line_infos(t_vars *vars, int fd, t_utils *utils)
{
	char	str[4096];
	char	**tmp;
	int		ret;

	utils->is_info = false;
	utils->i = 0;
	utils->j = 0;
	tmp = NULL;
	while (1)
	{
		ret = read(fd, &vars->c, 1);
		if (ret == 0 && vars->in_map == 0)
		{
			vars->in_map = 2;
			printf("Error: reached EOF\n");
			break ;
		}
		else if (ret == -1)
			break ;
		if (vars->c == '\n')
			break ;
		else if (vars->c == ' ' && utils->is_info != true)
			continue ;
		if (utils->i == 0)
			utils->is_info = check_first_char(vars, utils);
		if (check_in_map(vars, utils) == 1)
			return (NULL);
		if (utils->is_info)
			str[utils->j++] = vars->c;
		utils->i++;
	}
	str[utils->j] = '\0';
	if (*str)
		tmp = ft_split(str, " ,");
	return (tmp);
}
