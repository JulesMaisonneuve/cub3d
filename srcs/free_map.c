#include "../cubed.h"

int	free_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map_height)
	{
		free(vars->map[i]);
		i++;
	}
	free(vars->map);
	return (0);
}
