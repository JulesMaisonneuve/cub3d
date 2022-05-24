#ifndef CUBED_H
# define CUBED_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./mlx_linux/mlx.h"
# include "./getnl/get_next_line.h"
# include <math.h>
# include <sys/time.h>

# define SCREEN_HEIGHT 600
# define SCREEN_WIDTH 800
# define PI 3.1415
# define ESC 0xff1b

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
}				t_player;

typedef struct s_vars {
	int p;
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

#endif
