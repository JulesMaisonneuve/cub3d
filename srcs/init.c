/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:43:52 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/15 02:54:25 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	init_vars(t_vars *vars)
{
	vars->p = 0;
	vars->map_width = 0;
	vars->map_height = 1;
	vars->actual_col_count = 0;
	vars->nb_ray = SCREEN_WIDTH;
	vars->line_offset = -1;
	vars->player = NULL;
	vars->is_fire = false;
	vars->in_map = 0;
	vars->base_angle = PI / 6;
	vars->angle = (PI / 3 / SCREEN_WIDTH) * -1;
	vars->map = NULL;
	vars->textures = NULL;
	vars->win = NULL;
}

void	init_errors(t_errors *errors)
{
	errors->error1 = 0;
	errors->error2 = 0;
	errors->error3 = 0;
	errors->error4 = 0;
}

int	init_default_textures(t_vars *vars)
{
	int	size_line;
	int	endian;
	int	size;
	int	height;
	int	width;

	vars->textures = malloc(sizeof(t_textures));
	vars->textures->texture_default = malloc(sizeof(t_texture_details));
	vars->textures->texture_default->path_to_texture
		= "./textures/metal264px.xpm";
	vars->textures->texture_default->img_ptr
		= mlx_xpm_file_to_image(vars->mlx,
			vars->textures->texture_default->path_to_texture, &width, &height);
	if (vars->textures->texture_default->img_ptr == NULL)
		return (-1);
	vars->textures->texture_default->texture_width = width;
	vars->textures->texture_default->texture_height = height;
	vars->textures->texture_default->texture_data
		= mlx_get_data_addr(vars->textures->texture_default->img_ptr, &size,
			&size_line, &endian);
	vars->textures->texture_north = vars->textures->texture_default;
	vars->textures->texture_south = vars->textures->texture_default;
	vars->textures->texture_east = vars->textures->texture_default;
	vars->textures->texture_west = vars->textures->texture_default;
	return (0);
}

int	fd_mlx_init(t_vars *vars)
{
	vars->fd = open(vars->path, O_RDONLY);
	if (vars->fd < 0)
		return (-1);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (free_map(vars));
	return (0);
}
