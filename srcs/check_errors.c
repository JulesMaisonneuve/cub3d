#include "../cubed.h"

void	check_comps(t_vars *vars, t_errors *errors)
{
	if (vars->c != '0' && vars->c != '1' && vars->c != 'N' && vars->c != 'S' && vars->c != 'E' && vars->c != 'W' && vars->c != '\n')
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
			vars->actual_col_count++;
	}
	vars->map_height -= 1; // TO DO : Ligne vide
}

int	check_error(t_vars *vars, t_errors *errors)
{
	int	i;

	vars->fd = open(vars->path, O_RDONLY);
	if (vars->fd < 0)
		return (-1);
	i = 0;
	vars->map = malloc(vars->map_height * sizeof(char *));
	vars->textures = malloc(sizeof(t_textures));
	if (!vars->map)
		return (0);
	while (i < vars->map_height)
	{
		get_next_line(vars->fd, &vars->map[i]);
		i++;
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
