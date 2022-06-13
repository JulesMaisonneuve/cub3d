/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:08:59 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/13 03:24:31 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	print_error(t_errors *errors, t_vars *vars)
{
	if (errors->error1 == 1)
	{
		printf("Error\nThe map is not surrounded by walls\n");
		close_win(vars);
		return (-1);
	}
	else if (errors->error2 == 1)
	{
		printf("Error\nInvalid character\n");
		close_win(vars);
		return (-1);
	}
	else if (errors->error3 == 1)
	{
		printf("Error\nMap must contain at least and only \
			one starting position\n");
		close_win(vars);
		return (-1);
	}
	else if (errors->error4 == 1)
	{
		printf("Error\nThe map must be rectangular\n");
		close_win(vars);
		return (-1);
	}
	return (0);
}
