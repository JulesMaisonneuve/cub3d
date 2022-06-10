#include "../cubed.h"

int weapon_to_window(t_vars *vars)
{
	int img_width;
	int img_height;
	char *weapon_img;
	int bits_per_pixel;
	int endian;
	int size_line;
	int color;
	int x = 0;
	int y = 0;

	if (vars->is_fire)
		vars->weapon_path = "./textures/uzi_fire2.xpm";
	else
		vars->weapon_path = "./textures/uzi_default4.xpm";
	vars->weapon = mlx_xpm_file_to_image(vars->mlx, vars->weapon_path, &img_width, &img_height);
	if (!vars->weapon)
		return (-1);
	weapon_img = mlx_get_data_addr(vars->weapon, &bits_per_pixel, &size_line, &endian);
	while (y <= img_height)
	{
		x = 0;
		while (x <= img_width)
		{
			color = *((int *)weapon_img + (x + y * img_width));
			if (get_t(color) != 255)
				draw_pixel_img(vars, color, (x + SCREEN_WIDTH / 2) + img_width / 2, y + SCREEN_HEIGHT - img_height);
			x++; 
		}
		y++;
	}
	vars->is_fire = false;
	mlx_destroy_image(vars->mlx, vars->weapon);
	return (0);
}

void *create_scene(t_vars *vars)
{
	void *scene = NULL;
	int bits_per_pixel;
	int endian;
	int size_line;

	scene = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	vars->img_data = mlx_get_data_addr(scene, &bits_per_pixel, &size_line, &endian);
	return (scene);
}

int render_scene(t_vars *vars)
{
	void *scene;
	
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
	mlx_hook(vars->win, 03, 1L<<1, key_hook, vars);
	mlx_hook(vars->win, 02, 1L<<0, key_hook, vars);
	mlx_hook(vars->win, 03, 1L<<1, key_hook, vars);
	mlx_hook(vars->win, 02, 1L<<0, key_hook, vars);
	mlx_hook(vars->win, 33, 1L << 17, close_win, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	close_win(t_vars *vars)
{
	// mlx_destroy_image(vars->mlx, vars->weapon);
	// mlx_destroy_image(vars->mlx, vars->textures->texture_default->img_ptr);
	mlx_destroy_image(vars->mlx, vars->textures->texture_north->img_ptr);
	mlx_destroy_image(vars->mlx, vars->textures->texture_south->img_ptr);
	mlx_destroy_image(vars->mlx, vars->textures->texture_east->img_ptr);
	mlx_destroy_image(vars->mlx, vars->textures->texture_west->img_ptr);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	mlx_loop_end(vars->mlx);
	free(vars->mlx);
	free_map(vars);
	exit(0);
	return (0);
}
