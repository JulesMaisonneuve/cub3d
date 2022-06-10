/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:53:18 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/10 20:41:13 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	draw_pixel_img(t_vars *vars, int color, int x, int y)
{
	*((int *)vars->img_data + (x + y * SCREEN_WIDTH)) = color;
}

void	draw_line(int x, int y1, int y2, t_vars *vars, int color)
{
	while (y1 <= y2)
	{
		draw_pixel_img(vars, color, x, y1);
		y1++;
	}
}

double	get_wall_offset(t_ray *ray)
{
	if (ray->wall_orientation == 'N')
		return (1 - fmod(ray->hit_x, 1));
	else if (ray->wall_orientation == 'S')
		return (fmod(ray->hit_x, 1));
	else if (ray->wall_orientation == 'E')
		return (1 - fmod(ray->hit_y, 1));
	else if (ray->wall_orientation == 'W')
		return (fmod(ray->hit_y, 1));
	return (0);
}

void	draw_texture_strip(t_ray *ray, t_vars *vars, int x, int y1, int y2)
{
	int					color;
	double				wall_height;
	double				pixel_offset;
	double				y;
	double				wall_x;
	t_texture_details	*texture_details;

	y = 0;
	wall_height = y2 - y1;
	if (ray->wall_orientation == 'N')
		texture_details = vars->textures->texture_north;
	else if (ray->wall_orientation == 'S')
		texture_details = vars->textures->texture_south;
	else if (ray->wall_orientation == 'E')
		texture_details = vars->textures->texture_east;
	else
		texture_details = vars->textures->texture_west;
	wall_x = texture_details->texture_width / (1 / get_wall_offset(ray));
	pixel_offset = texture_details->texture_height / wall_height;
	while (y <= texture_details->texture_height)
	{
		if (y1 > 0 && y1 < SCREEN_HEIGHT)
		{
			color = get_color_from_orientation(ray->wall_orientation,
					wall_x, y, vars);
			draw_pixel_img(vars, color, x, y1);
		}
		y += pixel_offset;
		y1++;
	}
}

void	render_column(t_vars *vars, t_ray *ray)
{
	int	col_width;
	int	col_height;

	if (ray->distance == 0)
		col_height = 0;
	else
		col_height = SCREEN_HEIGHT / ray->distance;
	col_width = SCREEN_WIDTH / vars->nb_ray;
	draw_line(col_width * ray->nb, 0, SCREEN_HEIGHT / 2 - col_height / 2,
		vars, vars->ceiling_color);
	draw_texture_strip(ray, vars, col_width * ray->nb,
		SCREEN_HEIGHT / 2 - col_height / 2, SCREEN_HEIGHT / 2 + col_height / 2);
	draw_line(col_width * ray->nb, SCREEN_HEIGHT / 2 + col_height / 2,
		SCREEN_HEIGHT, vars, vars->floor_color);
}
