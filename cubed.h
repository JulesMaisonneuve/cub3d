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

# define SCREEN_HEIGHT 400
# define SCREEN_WIDTH  600
# define PI 3.1415
# define ESC 0xff1b

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
}				t_player;
typedef struct s_texture_details
{
	char *texture_data;
	int texture_height;
	int texture_width;
}				t_texture_details;

typedef struct s_textures {
	t_texture_details *texture_north;
	t_texture_details *texture_south;
	t_texture_details *texture_east;
	t_texture_details *texture_west;
}				t_textures;
typedef struct s_vars {
	int p;
	t_textures *textures;
	char *path;
	char **map;
	int map_height;
	int map_width;
	char c;
	int	actual_col_count;
	int fd;
	void	*mlx;
	void	*win;
	int nb_ray;
	t_player *player;
}				t_vars;

typedef struct s_errors {
	int	error1;
	int	error2;
	int	error3;
	int	error4;
	int	error5;
}				t_errors;


typedef struct s_ray {
	int nb;			// Numero du rayon
	double distance;   // -1 si le rayon n'a jamais tapé
	double dir_x;
	double dir_y;
	double pos_x;
	double pos_y;
	double hit_x;
	double hit_y;
	char wall_orientation;
}				t_ray;

int		ft_strchrr(const char *str, int c);
void	is_valid_map(int fd, t_vars *vars, t_errors *errors);
int		check_error(t_vars *vars, t_errors *errors);
int		print_error(t_errors *errors, t_vars *vars);
int		free_map(t_vars *vars);
int		is_valid_file(t_vars *vars);
void	parse_player(t_vars *vars);
int		close_win(t_vars *vars);
int		init_window(t_vars *vars);
void	render_column(t_vars *vars, t_ray *ray);
int		ray_casting(t_vars *vars);
void	impact_distance(t_ray *ray, t_vars *vars, double angle);
int		key_hook(int keycode, t_vars *vars);
int		parse_texture(t_vars *vars, char *texture_path, char orientation);
int		get_color_from_orientation(char orientation, int x, int y, t_vars *vars);
void draw_texture_strip(t_ray *ray, t_vars *vars, int x, int y1, int y2);
void draw_line(int x, int y1, int y2, t_vars *vars, int color);

#endif
