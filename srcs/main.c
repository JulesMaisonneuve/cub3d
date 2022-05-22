#include "../cubed.h"

void	init_vars(t_vars *vars)
{
	vars->player = 0;
	vars->map_width = 0;
	vars->map_height = 1;
	vars->actual_col_count = 0;
	vars->nb_ray = 6;
}

void	init_errors(t_errors *errors)
{
	errors->error1 = 0;
	errors->error2 = 0;
	errors->error3 = 0;
	errors->error4 = 0;
	errors->error5 = 0;
}

int main(int argc, char **argv)
{
	t_vars vars;
	t_errors errors;
	t_ray ray;

	ray.distance = 5;
	ray.nb = 0;
	if (argc != 2)
		return (-1);
	vars.path = argv[1];
	if (is_valid_file(&vars) == -1)
		return (-1);
	init_vars(&vars);
	init_errors(&errors);
	vars.fd = open(vars.path, O_RDONLY);
	if (vars.fd < 0)
		return (-1);
	is_valid_map(vars.fd, &vars, &errors);
	close(vars.fd);
	if (errors.error5 == 1)
		return (0);
	check_error(&vars, &errors);
	if (errors.error1 == 1 || errors.error2 == 1
		|| errors.error3 == 1 || errors.error4 == 1)
		return (print_error(&errors, &vars));
	parse_player(&vars);
	init_window(&vars, &ray);
	return (0);
}
