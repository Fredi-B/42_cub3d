#include "cub3D.h"

static bool	get_first_line(t_data *data, int fd);
static void	join_lines(t_data *data, char *line, int *longest_row);

/* reads map into data->map.
skips empty lines in the beginning, checks against them thereafter */
bool	read_map(t_data *data, int fd)
{
	//leaks??
	char	*line;
	int		longest_row;

	longest_row = 0;
	if (get_first_line(data, fd) == false)
		return (false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			break ;
		join_lines(data, line, &longest_row);
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
		return (false);
	}
	if (longest_row == data->rows)
		data->cols += 1;
	return (true);
}

/* skips empty lines and stores data from first line with data */
static bool	get_first_line(t_data *data, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		if (line[0] != '\n')
		{
			data->map = line;
			data->rows = 1;
			data->cols = ft_strlen(line) - 1;
			break ;
		}
	}
	return (true);
}

static void	join_lines(t_data *data, char *line, int *longest_row)
{
	char	*tmp;

	data->rows++;
	if ((int)ft_strlen(line) - 1 >= data->cols)
	{
		data->cols = ft_strlen(line) - 1;
		*longest_row = data->rows;
	}
	tmp = ft_strjoin(data->map, line);
	free(data->map);
	data->map = tmp;
}

bool	parse_map(t_data *data)
{
	char		**tmp_map;
	t_counter	i;
	bool		only_one_player_flag;

	tmp_map = ft_split(data->map, '\n');
	if (malloc_map(data) == false)
		return (false);
	init_counter_and_flag(&i, &only_one_player_flag);
	while (tmp_map[i.tmp_y])
	{
		if (parse_tmp_map_into_map(data, &i, tmp_map, &only_one_player_flag) == false)
			return (false);
		i.line = 0;
		i.tmp_x = 0;
		i.tmp_y++;
	}
	free_two_d_arr(tmp_map);
	if (only_one_player_flag == false)
		return (false);
	return (true);
}
