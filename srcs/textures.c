/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 01:32:29 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/11 04:14:35 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	parse_texture(t_vars *vars, char *texture_path, char orientation)
{
	int					size_line;
	int					endian;
	int					size;
	int					img_height;
	int					img_width;
	t_texture_details	*texture_details;

	texture_details = malloc(sizeof(t_texture_details));
	texture_details->img_ptr = mlx_xpm_file_to_image(vars->mlx, texture_path,
			&img_width, &img_height);
	if (texture_details->img_ptr == NULL)
		return (-1);
	texture_details->texture_width = img_width;
	texture_details->texture_height = img_height;
	texture_details->texture_data = mlx_get_data_addr(texture_details->img_ptr,
			&size, &size_line, &endian);
	if (orientation == 'N')
		vars->textures->texture_north = texture_details;
	else if (orientation == 'S')
		vars->textures->texture_south = texture_details;
	else if (orientation == 'E')
		vars->textures->texture_east = texture_details;
	else if (orientation == 'W')
		vars->textures->texture_west = texture_details;
	else if (orientation == 'C')
		vars->textures->texture_ceiling = texture_details;
	return (0);
}

int	get_color_from_orientation(char orientation, int x, int y, t_vars *vars)
{
	t_texture_details	*texture;
	int					color;

	texture = NULL;
	if (orientation == 'N')
		texture = vars->textures->texture_north;
	else if (orientation == 'S')
		texture = vars->textures->texture_south;
	else if (orientation == 'E')
		texture = vars->textures->texture_east;
	else if (orientation == 'W')
		texture = vars->textures->texture_west;
	if (orientation == 'C')
		texture = vars->textures->texture_ceiling;
	color = *((int *)texture->texture_data + (x + y * texture->texture_width));
	return (color);
}
