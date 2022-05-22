#ifndef CUBED_H
# define CUBED_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./mlx_linux/mlx.h"
# include "./getnl/get_next_line.h"

typedef struct s_vars {
	int player;
	char *path;
	char **map;
	int map_height;
	int map_width;
	char c;
	int	actual_col_count;
	int fd;
}				t_vars;

typedef struct s_errors {
	int	error1;
	int	error2;
	int	error3;
	int	error4;
	int	error5;
}				t_errors;

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
}				t_player;


int		ft_strchrr(const char *str, int c);
void	is_valid_map(int fd, t_vars *vars, t_errors *errors);
int		check_error(t_vars *vars, t_errors *errors);
int		print_error(t_errors *errors, t_vars *vars);
int		free_map(t_vars *vars);
int		is_valid_file(t_vars *vars);

#endif
