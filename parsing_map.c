
static void	store_player_pos(t_data *data, char pos, \
								int counter_map, int counter_line);
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
	dsprintf(data->map);
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
