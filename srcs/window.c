#include "../cubed.h"

int	init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (free_map(vars));
	vars->win = mlx_new_window(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!vars->win)
		return (free_map(vars));
	ray_casting(vars);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_hook(vars->win, 33, 1L << 17, close_win, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	mlx_loop_end(vars->mlx);
	free(vars->mlx);
	free_map(vars);
	exit(0);
	return (0);
}