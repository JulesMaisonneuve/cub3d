/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:32:41 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/12 03:31:02 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	*create_scene(t_vars *vars)
{
	void	*scene;
	int		bits_per_pixel;
	int		endian;
	int		size_line;

	scene = NULL;
	scene = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!scene)
		return (NULL);
	vars->img_data = mlx_get_data_addr(scene, &bits_per_pixel, &size_line,
			&endian);
	return (scene);
}

int	render_scene(t_vars *vars)
{
	void	*scene;

	scene = create_scene(vars);
	ray_casting(vars);
	weapon_to_window(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, scene, 0, 0);
	mlx_destroy_image(vars->mlx, scene);
	return (0);
}

int	init_window(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!vars->win)
		return (free_map(vars));
	mlx_loop_hook(vars->mlx, render_scene, vars);
	mlx_hook(vars->win, 03, 1L << 1, key_hook, vars);
	mlx_hook(vars->win, 02, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 03, 1L << 1, key_hook, vars);
	mlx_hook(vars->win, 02, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 33, 1L << 17, close_win, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	close_win(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->textures->texture_default->img_ptr);
	if (vars->textures->texture_north->img_ptr != NULL
		&& vars->textures->texture_north->img_ptr
		!= vars->textures->texture_default->img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures->texture_north->img_ptr);
	if (vars->textures->texture_south->img_ptr != NULL
		&& vars->textures->texture_south->img_ptr
		!= vars->textures->texture_default->img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures->texture_south->img_ptr);
	if (vars->textures->texture_east->img_ptr != NULL
		&& vars->textures->texture_east->img_ptr
		!= vars->textures->texture_default->img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures->texture_east->img_ptr);
	if (vars->textures->texture_west->img_ptr != NULL
		&& vars->textures->texture_west->img_ptr
		!= vars->textures->texture_default->img_ptr)
		mlx_destroy_image(vars->mlx, vars->textures->texture_west->img_ptr);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	mlx_loop_end(vars->mlx);
	free(vars->mlx);
	free_map(vars);
	exit(0);
	return (0);
}
