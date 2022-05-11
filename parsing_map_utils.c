#include "cub3D.h"

bool	malloc_map(t_data *data)
{
	free(data->map);
	data->map = malloc(sizeof(char) * ((data->rows * data->cols) + 1));
	if (!data->map)
		return (false);
	ft_memset(data->map, 'X', data->rows * data->cols);
	data->map[(data->rows * data->cols) + 1] = '\0';
	return (true);
}

void	init_counter_and_flag(t_counter *i, bool *only_one_player_flag)
{
	*only_one_player_flag = false;
	i->tmp_x = 0;
	i->tmp_y = 0;
	i->map = 0;
	i->line = 0;
}
