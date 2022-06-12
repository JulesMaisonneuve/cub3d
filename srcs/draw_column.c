/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:53:18 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/12 03:26:47 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	draw_pixel_img(t_vars *vars, int color, int x, int y)
{
	*((int *)vars->img_data + (x + y * SCREEN_WIDTH)) = color;
}

void	draw_ceiling(int x, int y1, t_vars *vars, int color)
{
	while (y1 <= (SCREEN_HEIGHT / 2 - vars->col_height / 2))
	{
		draw_pixel_img(vars, color, x, y1);
		y1++;
	}
}

void	draw_floor(int x, int y1, t_vars *vars, int color)
{
	while (y1 <= SCREEN_HEIGHT)
	{
		draw_pixel_img(vars, color, x, y1);
		y1++;
	}
}

void	draw_texture_strip(t_ray *ray, t_vars *vars, int x, int y1)
{
	double				wall_height;
	double				pixel_offset;
	double				y;
	double				wall_x;
	t_texture_details	*texture_details;

	y = 0;
	wall_height = (SCREEN_HEIGHT / 2 + vars->col_height / 2) - y1;
	texture_details = check_wall_orientation(vars, ray);
	wall_x = texture_details->texture_width / (1 / get_wall_offset(ray));
	pixel_offset = texture_details->texture_height / wall_height;
	while (y <= texture_details->texture_height)
	{
		if (y1 > 0 && y1 < SCREEN_HEIGHT)
		{
			vars->color = get_color_from_orientation(ray->wall_orientation,
					wall_x, y, vars);
			draw_pixel_img(vars, vars->color, x, y1);
		}
		y += pixel_offset;
		y1++;
	}
}

void	render_column(t_vars *vars, t_ray *ray)
{
	int	col_width;

	if (ray->distance == 0)
		vars->col_height = 0;
	else
		vars->col_height = SCREEN_HEIGHT / ray->distance;
	col_width = SCREEN_WIDTH / vars->nb_ray;
	draw_ceiling(col_width * ray->nb, 0,
		vars, vars->ceiling_color);
	draw_texture_strip(ray, vars, col_width * ray->nb,
		SCREEN_HEIGHT / 2 - vars->col_height / 2);
	draw_floor(col_width * ray->nb, SCREEN_HEIGHT / 2 + vars->col_height / 2,
		vars, vars->floor_color);
}
