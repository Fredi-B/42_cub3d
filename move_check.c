#include "cub3D.h"

bool	check_if_is_wall(t_data *arr, int x, int y)
{
	int		mx;
	int		my;
	int		mp;

	mx = (int)(x);
	my = (int)(y);
	mp = my * arr->cols + mx;
	if (arr->map[mp] != '0')
		return (true);
	return (false);
}

bool	search_wall_x(t_data *data, int *old_x, int old_y, int new_x)
{
	float	tile;

	tile = data->subsize;
	if ((*old_x) < new_x)
			(*old_x)++;
	else
		(*old_x)--;
	if (check_if_is_wall(data, (*old_x) / tile, old_y / tile))
		return (true);
	return (false);
}

bool	search_wall_y(t_data *data, int old_x_copy, int *old_y, int new_y)
{
	float	tile;

	tile = data->subsize;
	if ((*old_y) < (int)new_y)
		(*old_y)++;
	else
		(*old_y)--;
	if (check_if_is_wall(data, old_x_copy / tile, (*old_y) / tile))
		return (true);
	return (false);
}

bool	going_across(t_data *data, float new_x, float new_y)
{
	int		old_x;
	int		old_y;
	int		old_x_copy;

	old_x = (int)data->p_x;
	old_y = (int)data->p_y;
	old_x_copy = old_x;
	while (old_x != (int)new_x)
	{
		if (search_wall_x(data, &old_x, old_y, (int)new_x) == true)
			return (true);
	}
	while (old_y != (int)new_y)
	{
		if (search_wall_y(data, old_x_copy, &old_y, (int)new_y) == true)
			return (true);
	}
	return (false);
}

bool	less_than_x_pixels(t_data *data, float new_x, float new_y, int p)
{
	float	tile;

	tile = data->subsize;
	if (check_if_is_wall(data, (new_x + p) / tile, (new_y - p) / tile))
		return (true);
	if (check_if_is_wall(data, new_x / tile, (new_y - p) / tile))
		return (true);
	if (check_if_is_wall(data, (new_x - p) / tile, (new_y - p) / tile))
		return (true);
	if (check_if_is_wall(data, (new_x + p) / tile, new_y / tile))
		return (true);
	if (check_if_is_wall(data, new_x / tile, new_y / tile))
		return (true);
	if (check_if_is_wall(data, (new_x - p) / tile, new_y / tile))
		return (true);
	if (check_if_is_wall(data, (new_x + p) / tile, (new_y + p) / tile))
		return (true);
	if (check_if_is_wall(data, new_x / tile, (new_y + p) / tile))
		return (true);
	if (check_if_is_wall(data, (new_x - p) / tile, (new_y + p) / tile))
		return (true);
	return (false);
}
