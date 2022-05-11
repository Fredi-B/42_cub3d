#include "cub3D.h"

static void	store_player_pos(t_data *data, char pos, \
								int counter_map, int counter_line);

/* reads map into data->map.
skips empty lines in the beginning, checks against them thereafter */
bool	read_map(t_data *data, int fd)
{
	//leaks??
	char	*line;
	char	*tmp;
	int		longest_row;

	line = NULL;
	tmp = NULL;
	longest_row = 0;
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
	while (1)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			break ;
		data->rows++;
		if (ft_strlen(line) - 1 >= data->cols)
		{
			data->cols = ft_strlen(line) - 1;
			longest_row = data->rows;
		}
		tmp = ft_strjoin(data->map, line);
		free(data->map);
		data->map = tmp;
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

bool	parse_map(t_data *data)
{
	char	**tmp_map;
	int		counter_tmp_x;
	int		counter_tmp_y;
	int		counter_map;
	int		counter_line;
	bool	only_one_player_flag;


	tmp_map = ft_split(data->map, '\n');
	free(data->map);
	data->map = malloc(sizeof(char) * ((data->rows * data->cols) + 1));
	if (!data->map)
		return (false);
	ft_memset(data->map, 'X', data->rows * data->cols);
	data->map[(data->rows * data->cols) + 1] = '\0';
	only_one_player_flag = false;
	counter_tmp_x = 0;
	counter_tmp_y = 0;
	counter_map = 0;
	counter_line = 0;
	while (tmp_map[counter_tmp_y])
	{
		while (counter_line <= ft_strlen(tmp_map[counter_tmp_y]) + 1)
		{

			if (tmp_map[counter_tmp_y][counter_tmp_x] == '1')
				data->map[counter_map] = '1';
			else if (tmp_map[counter_tmp_y][counter_tmp_x] == '0')
				data->map[counter_map] = '0';
			else if (tmp_map[counter_tmp_y][counter_tmp_x] == 'N' || tmp_map[counter_tmp_y][counter_tmp_x] == 'S' \
				|| tmp_map[counter_tmp_y][counter_tmp_x] == 'W' || tmp_map[counter_tmp_y][counter_tmp_x] == 'E')
			{
				if (only_one_player_flag == true)
				{
					free_two_d_arr(tmp_map);
					return (false);
				}
				only_one_player_flag = true;
				store_player_pos(data, tmp_map[counter_tmp_y][counter_tmp_x], \
					counter_map, counter_line);
			}
			else if (tmp_map[counter_tmp_y][counter_tmp_x] == ' ')
				data->map[counter_map] = 'X';
			else if (tmp_map[counter_tmp_y][counter_tmp_x] == '\0')
			{
				counter_map += data->cols - counter_line;
				break ;
			}
			else
			{
				free_two_d_arr(tmp_map);
				return (false);
			}
			counter_tmp_x++;
			counter_map++;
			counter_line++;
		}
		counter_line = 0;
		counter_tmp_x = 0;
		counter_tmp_y++;
	}
	free_two_d_arr(tmp_map);
	if (only_one_player_flag == false)
		return (false);
	return (true);
}

static void	store_player_pos(t_data *data, char pos, \
								int counter_map, int counter_line)
{
	//@arno: passt das oder ist das Quatsch?
	data->map[counter_map] = '0';
	if (pos == 'N')
		data->p_a = 1;
	if (pos == 'E')
		data->p_a = 91;
	if (pos == 'S')
		data->p_a = 181;
	if (pos == 'W')
		data->p_a = 271;
	data->p_x = counter_line;
	data->p_y = counter_map / data->rows;
}
