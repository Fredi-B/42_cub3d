#include "cub3D.h"

static bool	fill_map(t_data *data, t_counter *i, char **tmp_map, \
						bool *only_one_player_flag);
static void	store_player_pos(t_data *data, char pos, \
								int counter_map, int counter_line);

bool	malloc_map(t_data *data)
{
	free(data->map);
	data->map = malloc(sizeof(char) * ((data->rows * data->cols) + 1));
	if (!data->map)
		return (false);
	ft_memset(data->map, 'X', data->rows * data->cols);
	data->map[(data->rows * data->cols)] = '\0';
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

bool	parse_tmp_map_into_map(t_data *data, t_counter *i, \
						char **tmp_map, bool *only_one_player_flag)
{
	while (i->line <= (int)ft_strlen(tmp_map[i->tmp_y]) + 1)
	{
		if (is_valid_part_of_map(tmp_map[i->tmp_y][i->tmp_x]) == true)
		{
			if (fill_map(data, i, tmp_map, only_one_player_flag) == false)
				return (false);
		}
		else if (tmp_map[i->tmp_y][i->tmp_x] == '\0')
		{
			i->map += data->cols - i->line;
			break ;
		}
		else
		{
			ft_free_two_d_arr(tmp_map);
			return (false);
		}
		i->tmp_x++;
		i->map++;
		i->line++;
	}
	return (true);
}

static bool	fill_map(t_data *data, t_counter *i, char **tmp_map, \
					bool *only_one_player_flag)
{
	if (tmp_map[i->tmp_y][i->tmp_x] == '1')
		data->map[i->map] = '1';
	else if (tmp_map[i->tmp_y][i->tmp_x] == '0')
		data->map[i->map] = '0';
	else if (tmp_map[i->tmp_y][i->tmp_x] == 'N' \
			|| tmp_map[i->tmp_y][i->tmp_x] == 'S' \
			|| tmp_map[i->tmp_y][i->tmp_x] == 'W' \
			|| tmp_map[i->tmp_y][i->tmp_x] == 'E')
	{
		if (*only_one_player_flag == true)
		{
			ft_free_two_d_arr(tmp_map);
			return (false);
		}
		*only_one_player_flag = true;
		store_player_pos(data, tmp_map[i->tmp_y][i->tmp_x], \
			i->map, i->line);
	}
	else if (tmp_map[i->tmp_y][i->tmp_x] == ' ')
		data->map[i->map] = 'X';
	return (true);
}

static void	store_player_pos(t_data *data, char pos, \
								int counter_map, int counter_line)
{
	data->map[counter_map] = '0';
	if (pos == 'W')
		data->p_a = 0 * ODR;
	if (pos == 'N')
		data->p_a = 90 * ODR;
	if (pos == 'E')
		data->p_a = 180 * ODR;
	if (pos == 'S')
		data->p_a = 270 * ODR;
	data->p_x = counter_line;
	data->p_y = counter_map / data->cols;
}
