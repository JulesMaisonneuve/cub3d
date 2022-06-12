/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 04:07:29 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/12 04:33:29 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	draw_weapon(t_vars *vars, int width, int height, char *weapon_img)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	color = 0;
	while (y <= height)
	{
		x = 0;
		while (x <= width)
		{
			color = *((int *)weapon_img + (x + y * width));
			if (get_t(color) != 255)
				draw_pixel_img(vars, color, (x + SCREEN_WIDTH / 2) + width / 2,
					y + SCREEN_HEIGHT - height);
			x++;
		}
		y++;
	}
}

int	weapon_to_window(t_vars *vars)
{
	int		img_width;
	int		img_height;
	int		bits_per_pixel;
	int		endian;
	int		size_line;

	if (vars->is_fire)
		vars->weapon_path = "./textures/uzi_fire2.xpm";
	else
		vars->weapon_path = "./textures/uzi_default4.xpm";
	vars->weapon = mlx_xpm_file_to_image(vars->mlx, vars->weapon_path,
			&img_width, &img_height);
	if (!vars->weapon)
		return (-1);
	vars->weapon_img = mlx_get_data_addr(vars->weapon, &bits_per_pixel,
			&size_line, &endian);
	draw_weapon(vars, img_width, img_height, vars->weapon_img);
	vars->is_fire = false;
	mlx_destroy_image(vars->mlx, vars->weapon);
	return (0);
}
