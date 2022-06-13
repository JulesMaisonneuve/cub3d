/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 04:27:51 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/13 03:27:19 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_errors	errors;
	t_utils		utils;

	if (argc != 2)
		return (-1);
	vars.path = argv[1];
	if (is_valid_file(&vars) == -1)
		return (-1);
	init_vars(&vars);
	init_errors(&errors);
	if (fd_mlx_init(&vars) == -1)
		return (-1);
	init_default_textures(&vars);
	is_valid_map(vars.fd, &vars, &errors, &utils);
	close(vars.fd);
	if (errors.error5 == 1)
		return(close_win(&vars));
	check_error(&vars, &errors, &utils, vars.line_offset);
	if (errors.error1 == 1 || errors.error2 == 1
		|| errors.error3 == 1 || errors.error4 == 1)
		return (print_error(&errors, &vars));
	get_player_infos(&vars);
	init_window(&vars);
	return (0);
}
