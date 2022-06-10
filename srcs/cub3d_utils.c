/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:21:02 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/10 19:34:46 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;
	int	i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		nb *= 10;
		nb += ((int)str[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

bool	check_first_char(t_vars *vars, int i)
{
	if ((vars->c == 'C' || vars->c == 'F' || vars->c == 'N' || vars->c == 'S'
		|| vars->c == 'E' || vars->c == 'W') && i == 0)
		return (true);
	return (false);
}

char	**read_line_infos(t_vars *vars, int fd)
{
	bool	is_info;
	int		i;
	int		j;
	char str[4096];
	char **tmp = NULL;
	
	is_info = false;
	i = 0;
	j = 0;
	while (read(fd, &vars->c, 1) == 1)
	{
		if (vars->c == '\n')
			break ;
		if (i == 0)
			is_info = check_first_char(vars, i);
		if (vars->c == '1' && i == 0)
		{
			vars->in_map = 1;
			return (NULL);
		}
		if (is_info)
			str[j++] = vars->c;
		i++;
	}
	str[j] = '\0';
	if (*str)
		tmp = ft_split(str, " ,");
	return (tmp);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	get_floor_ceiling_color(t_vars *vars, char **tmp)
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = 0;
	g = 0;
	b = 0;
	if (tmp[1])
	{
		if (is_digit(tmp[1]))
			r = ft_atoi(tmp[1]);
	}
	if (tmp[2])
	{
		if (is_digit(tmp[2]))
			g = ft_atoi(tmp[2]);
	}
	if (tmp[3])
	{
		if (is_digit(tmp[3]))
			b = ft_atoi(tmp[3]);
	}
	color = create_trgb(0, r, g, b);
	if (**tmp == 'F')
		vars->floor_color = color;
	else
		vars->ceiling_color = color;
}

bool	get_cubfile_infos(t_vars *vars, int fd)
{
	bool	is_info;
	char	**tmp = NULL;

	is_info = false;
	tmp = read_line_infos(vars, fd);
	if (tmp)
	{
		if ((**tmp == 'F' || **tmp == 'C') && tmp[0][1] == '\0')
			get_floor_ceiling_color(vars, tmp);
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
