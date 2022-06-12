/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:08:59 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/11 22:09:01 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

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
		printf("Error\nMap must contain at least and only \
			one starting position\n");
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
