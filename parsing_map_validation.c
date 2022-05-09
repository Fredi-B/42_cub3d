#include "cub3D.h"

bool	validate_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cols)
	{
		if (data->map[i] == '0')
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
		if (data->map[i] == '0')
			return (false);
		i++;
	}
	return (true);
}