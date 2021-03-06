/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumaison <jumaison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:44:08 by jumaison          #+#    #+#             */
/*   Updated: 2022/06/15 03:39:44 by jumaison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./mlx_linux/mlx.h"
# include "./getnl/get_next_line.h"
# include <math.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

# define SCREEN_HEIGHT 600
# define SCREEN_WIDTH  800
# define PI 3.1415
# define ESC 0xff1b

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}				t_player;
typedef struct s_texture_details
{
	char	*texture_data;
	int		texture_height;
	int		texture_width;
	char	*path_to_texture;
	void	*img_ptr;
}				t_texture_details;

typedef struct s_textures {
	t_texture_details	*texture_north;
	t_texture_details	*texture_south;
	t_texture_details	*texture_east;
	t_texture_details	*texture_west;
	t_texture_details	*texture_ceiling;
	t_texture_details	*texture_default;
}				t_textures;

typedef struct s_utils {
	int		color;
	int		i;
	int		j;
	bool	is_info;
	int		r;
	int		g;
	int		b;
	int		bits_per_pixel;
	int		endian;
	int		size_line;
	double	dist_n;
	double	dist_s;
	double	dist_e;
	double	dist_w;
}				t_utils;
typedef struct s_vars {
	int			p;
	t_textures	*textures;
	char		*path;
	char		**map;
	int			map_height;
	int			map_width;
	char		c;
	int			actual_col_count;
	int			fd;
	void		*mlx;
	void		*win;
	int			nb_ray;
	int			ceiling_color;
	int			floor_color;
	int			line_offset;
	t_player	*player;
	int			weapon_height;
	int			weapon_width;
	char		*weapon_img;
	char		*weapon_path;
	void		*weapon;
	int			in_map;
	char		*img_data;
	bool		is_fire;
	int			col_height;
	int			color;
	double		angle;
	double		base_angle;
	double		actual_pos_y;
	double		actual_pos_x;
}				t_vars;

typedef struct s_errors {
	int	error1;
	int	error2;
	int	error3;
	int	error4;
}				t_errors;

typedef struct s_ray {
	int		nb;
	double	distance;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	hit_x;
	double	hit_y;
	char	wall_orientation;
}				t_ray;

int					ft_atoi(const char *str);
int					is_digit(char *str);
void				free_tab(char **tab);
int					ft_strchrr(const char *str, int c);
void				init_vars(t_vars *vars);
void				init_errors(t_errors *errors);
int					init_default_textures(t_vars *vars);
int					fd_mlx_init(t_vars *vars);
void				remove_white_space(char *str);
int					is_valid_map(int fd, t_vars *vars, t_errors *errors,
						t_utils *utils);
int					is_rectangular(t_vars *vars, t_errors *errors);
int					check_error(t_vars *vars, t_errors *errors, t_utils *utils,
						int line_offset);
int					print_error(t_errors *errors, t_vars *vars);
int					handle_space(t_vars *vars, t_utils *utils,
						t_errors *errors);
int					line_size_difference(t_vars *vars, t_utils *utils,
						t_errors *errors);
int					free_map(t_vars *vars);
void				free_textures(t_vars *vars);
char				**read_line_infos(t_vars *vars, int fd, t_utils *utils);
int					is_valid_file(t_vars *vars);
void				get_player_infos(t_vars *vars);
void				check_for_north_orientation(t_vars *vars, t_ray *ray);
void				check_for_south_orientation(t_vars *vars, t_ray *ray);
void				check_for_west_orientation(t_vars *vars, t_ray *ray);
void				check_for_east_orientation(t_vars *vars, t_ray *ray);
int					get_t(int trgb);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					close_win(t_vars *vars);
int					init_window(t_vars *vars);
t_texture_details	*check_wall_orientation(t_vars *vars, t_ray *ray);
double				get_wall_offset(t_ray *ray);
int					weapon_to_window(t_vars *vars);
int					create_trgb(int t, int r, int g, int b);
void				render_column(t_vars *vars, t_ray *ray);
int					ray_casting(t_vars *vars);
void				impact_distance(t_ray *ray, t_vars *vars, double angle);
int					key_hook(int keycode, t_vars *vars);
int					parse_texture(t_vars *vars, char *texture_path,
						char orientation, t_utils *utils);
int					get_color_from_orientation(char orientation, int x, int y,
						t_vars *vars);
void				draw_texture_strip(t_ray *ray, t_vars *vars, int x, int y1);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				**ft_free_words(char **tab);
char				**ft_split(char const *s, char *separators);
int					weapon_to_window(t_vars *vars);
bool				get_cubfile_infos(t_vars *vars, int fd, t_utils *utils,
						t_errors *errors);
void				draw_pixel_img(t_vars *vars, int color, int x, int y);
void				player_move_forward(t_vars *vars);
void				player_move_backward(t_vars *vars);
void				player_move_left(t_vars *vars);
void				player_move_right(t_vars *vars);
void				camera_rotate_left(t_vars *vars);
void				camera_rotate_right(t_vars *vars);

#endif
