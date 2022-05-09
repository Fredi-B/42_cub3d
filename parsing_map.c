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

	line = NULL;
	tmp = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		if (line[0] != '\n')
		{
			data->map = line;
			data->rows = 1;
			data->cols = ft_strlen(line);
			break ;
		}
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			break ;
		data->rows++;
		if (ft_strlen(line) > data->cols)
			data->cols = ft_strlen(line);
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
	return (true);
}

bool	parse_map(t_data *data)
{
	char	*tmp_map;
	int		counter_tmp;
	int		counter_map;
	int		counter_line;
	bool	only_one_player_flag;


	tmp_map = ft_strdup(data->map);
	free(data->map);
	data->map = malloc(sizeof(char) * ((data->rows * (data->cols)) + 1));
	if (!data->map)
		return (false);
	ft_memset(data->map, 'X', data->rows * data->cols);
	data->map[(data->rows * data->cols) + 1] = '\0';
	only_one_player_flag = false;
	counter_tmp = 0;
	counter_map = 0;
	counter_line = 0;
	while(tmp_map[counter_tmp])
	{
		if (tmp_map[counter_tmp] == '1')
			data->map[counter_map] = '1';
		else if (tmp_map[counter_tmp] == '0')
			data->map[counter_map] = '0';
		else if (tmp_map[counter_tmp] == 'N' || tmp_map[counter_tmp] == 'S' \
			|| tmp_map[counter_tmp] == 'W' || tmp_map[counter_tmp] == 'E')
		{
			if (only_one_player_flag == true)
				return (false);
			only_one_player_flag = true;
			store_player_pos(data, tmp_map[counter_tmp], \
				counter_map, counter_line);
		}
		else if (tmp_map[counter_tmp] == ' ')
			data->map[counter_map] = 'X';
		else if (tmp_map[counter_tmp] == '\n')
		{
			data->map[counter_map] = 'X';
			//-1 damit ich unten in jedem Fall inkrementieren kann
			counter_map += data->cols - counter_line - 1;
			counter_line = -1;
		}
		else
			return (false);
		counter_tmp++;
		counter_map++;
		counter_line++;

	}
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
