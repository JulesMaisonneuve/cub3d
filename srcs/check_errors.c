#include "../cubed.h"

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_atoi(const char *str)
{
	int nb;
	int sign;
	int i;

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
	int i;

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

bool get_floor_ceiling_colors(t_vars *vars, int fd)
{
	int i;
	int j;
	int r = 0;
	int g = 0;
	int b = 0;
	int color = 0;
	bool in_map = 0;
	bool is_info = false;
	char str[256];
	char **tmp = NULL;
	i = 0;
	j = 0;
	while (read(fd, &vars->c, 1) == 1)
	{
		if (vars->c == '\n')
		{
			break ;
		}
		else if ((vars->c == 'C' || vars->c == 'F' || vars->c == 'N' || vars->c == 'S' || vars->c == 'E' || vars->c == 'W') && i == 0)
		{
			is_info = true;
		}
		else if (vars->c == '1' && i == 0)
		{
			in_map = 1;
			return (in_map);
		}
		if (is_info)
		{
			str[j++] = vars->c;
		}
		i++;
	}
	str[j] = '\0';
	if (*str)
		tmp = ft_split(str, " ,");
	if (tmp)
	{
		if ((**tmp == 'F' || **tmp == 'C') && tmp[0][1] == '\0')
		{
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
		else if ((ft_strncmp(tmp[0], "NO", 2) == 0 || ft_strncmp(tmp[0], "SO", 2) == 0 || ft_strncmp(tmp[0], "EA", 2) == 0 || ft_strncmp(tmp[0], "WE", 2) == 0) && tmp[1])
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
	// if (tmp)
	// 	free(tmp);
	return (in_map);
}
void	check_comps(t_vars *vars, t_errors *errors)
{
	if (vars->c != '0' && vars->c != '1' && vars->c != 'N' && vars->c != 'S' && vars->c != 'E' && vars->c != 'W' && vars->c != '\n' && vars-> c != ' ')
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

int	is_rectangular(t_vars *vars, t_errors *errors)
{
	int	i;
	int	len_line;

	i = 0;
	while (i < vars->map_height)
	{
		len_line = ft_strlen(vars->map[i]);
		if (len_line == 0)
			break ;
		if (vars->map_width != len_line)
		{
			errors->error4 = 1;
			return (-1);
		}
		else if (vars->map[i][0] != '1'
			|| vars->map[i][vars->map_width - 1] != '1')
			errors->error1 = 1;
		i++;
	}
	return (0);
}

void	is_valid_map(int fd, t_vars *vars, t_errors *errors)
{
	int in_map = 0;
	while (in_map != 1)
	{
		in_map = get_floor_ceiling_colors(vars, fd);
		vars->line_offset++;
	}
	if (in_map == 1)
		vars->actual_col_count++;
	while (read(fd, &vars->c, 1) == 1)
	{
		check_comps(vars, errors);
		if (vars->c == '\n')
		{
			if (vars->actual_col_count == 0)
			{
				errors->error5 = 1;
				printf("Error\nThe map must be rectangular\n");
				break ;
			}
			if (vars->map_width == 0)
				vars->map_width = vars->actual_col_count;
			else if (vars->map_width != vars->actual_col_count)
				errors->error4 = 1;
			vars->actual_col_count = 0;
			vars->map_height++;
		}
		else
		{
			if (vars->c != ' ')
			{
				vars->actual_col_count++;
			}
		}
	}
	// vars->map_height -= 1; // TO DO : Ligne vide
}

void remove_white_space(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			str[j++] = str[i];
		}
		i++;
	}
	str[j] = '\0';
}

int	check_error(t_vars *vars, t_errors *errors, int j)
{
	int	i;
	char *tmp;
	vars->fd = open(vars->path, O_RDONLY);
	if (vars->fd < 0)
		return (-1);
	i = 0;
	vars->map = malloc(vars->map_height * sizeof(char *));
	if (!vars->map)
		return (0);
	while (i < j)
	{
		get_next_line(vars->fd, &tmp);
		i++;
	}
	i = 0;
	while (i < vars->map_height)
	{
		get_next_line(vars->fd, &vars->map[i]);
		remove_white_space(vars->map[i]);
		// printf("vars map[i]: %s\n", vars->map[i]);
		i++;
		j++;
	}
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

int	print_error(t_errors *errors, t_vars *vars)
{
	if (errors->error1 == 1)
	{
		free_map(vars);
		printf("Error\nThe map is not surrounded by walls\n");
		return (-1);
	}
	else if (errors->error2 == 1)
	{
		free_map(vars);
		printf("Error\nInvalid character\n");
		return (-1);
	}
	else if (errors->error3 == 1)
	{
		free_map(vars);
		printf("Error\nMap must contain at least and only one starting position\n");
		return (-1);
	}
	else if (errors->error4 == 1)
	{
		free_map(vars);
		printf("Error\nThe map must be rectangular\n");
		return (-1);
	}
	return (0);
}

