#include "../cubed.h"

void	init_vars(t_vars *vars)
{
	vars->p = 0;
	vars->map_width = 0;
	vars->map_height = 1;
	vars->actual_col_count = 0;
	vars->nb_ray = SCREEN_WIDTH;
	vars->line_offset = -1;
	vars->player = NULL;
	vars->is_fire = false;
}

void	init_errors(t_errors *errors)
{
	errors->error1 = 0;
	errors->error2 = 0;
	errors->error3 = 0;
	errors->error4 = 0;
	errors->error5 = 0;
}

int init_default_textures(t_vars *vars)
{
	void *texture;
	int size_line = 0;
    int endian = 0;
    int size = 0;
    int img_height = 0;
    int img_width = 0;
	vars->textures = malloc(sizeof(t_textures));
	vars->textures->texture_default = malloc(sizeof(t_texture_details));
	vars->textures->texture_default->path_to_texture = "./textures/metal264px.xpm";
	texture = mlx_xpm_file_to_image(vars->mlx, vars->textures->texture_default->path_to_texture, &img_width, &img_height);
	if (texture == NULL)
        return (-1);
    vars->textures->texture_default->texture_width = img_width;
    vars->textures->texture_default->texture_height = img_height;
    vars->textures->texture_default->texture_data = mlx_get_data_addr(texture, &size, &size_line, &endian);
	vars->textures->texture_north = vars->textures->texture_default;
	vars->textures->texture_south = vars->textures->texture_default;
	vars->textures->texture_east = vars->textures->texture_default;
	vars->textures->texture_west = vars->textures->texture_default;
	return (0);
}


int main(int argc, char **argv)
{
	t_vars vars;
	t_errors errors;

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
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (free_map(&vars));
	init_default_textures(&vars);
	is_valid_map(vars.fd, &vars, &errors);
	close(vars.fd);
	if (errors.error5 == 1)
		return (0);
	check_error(&vars, &errors, vars.line_offset);
	if (errors.error1 == 1 || errors.error2 == 1
		|| errors.error3 == 1 || errors.error4 == 1)
		return (print_error(&errors, &vars));
	parse_player(&vars);
	init_window(&vars);
	return (0);
}
