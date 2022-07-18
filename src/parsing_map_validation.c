#include "cub3D.h"

static bool	validate_first_row(t_data *data, int i);
static bool	validate_last_row(t_data *data, int i);

bool	validate_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cols)
	{
		if (validate_first_row(data, i) == false)
			return (false);
		i++;
	}
	while (i < (data->rows -1) * data->cols)
	{
		if (data->map[i] == 'X' && (data->map[i - 1] == '0' \
		|| data->map[i - data->cols] == '0' || data->map[i + 1] == '0' \
		|| data->map[i + data->cols] == '0'))
			return (false);
		i++;
	}
	while (i >= (data->rows -1) * data->cols && i < data->rows * data->cols)
	{
		if (validate_last_row(data, i) == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	validate_first_row(t_data *data, int i)
{
	if (data->map[i] == '0')
		return (false);
	if (data->map[i] == 'X' && (data->map[i + data->cols] == '0'))
		return (false);
	return (true);
}

static bool	validate_last_row(t_data *data, int i)
{
	if (data->map[i] == '0')
		return (false);
	if (data->map[i] == 'X' && (data->map[i - data->cols] == '0'))
		return (false);
	return (true);
}
