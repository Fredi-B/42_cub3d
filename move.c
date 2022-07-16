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

static bool	search_wall_x(t_data *data, int *old_x, int old_y, int new_x)
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

static bool	search_wall_y(t_data *data, int old_x_copy, int *old_y, int new_y)
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

static bool	going_across(t_data *data, float new_x, float new_y)
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

static bool	less_than_x_pixels(t_data *data, float new_x, float new_y, int p)
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

bool	movement_collision(t_data *data, float x, float y)
{
	float	new_x;
	float	new_y;
	int		i;
	int		j;

	new_x = data->p_x + x;
	new_y = data->p_y + y;
	i = new_x /  data->subsize;
	j = new_y / data->subsize;
	if (check_if_is_wall(data, i, j))
		return (true);
 	else if (less_than_x_pixels(data, new_x, new_y, 12))
		return (true);
	else if (going_across(data, new_x, new_y))
		return (true);
	return (false);
}

static void	move_vertical(t_data *data, float x, float y, int sign)
{
	if (!movement_collision(data, x * sign, y * sign))
	{
		data->p_x += x * sign;
		data->p_y += y * sign;
	}
}

void	move_sideways2(t_data *arr, float	velocity, int sign)
{
	arr->p_a += 0.5 * M_PI;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
	arr->p_dx = cos(arr->p_a) * velocity;
	arr->p_dy = sin(arr->p_a) * velocity;
	move_vertical(arr, arr->p_dx, arr->p_dy, sign);
	arr->p_a -= 0.5 * M_PI;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
}

void	turn(t_data *arr, int sign)
{
	arr->p_a += 2 * ODR * sign;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
}

int	hook(t_data *data)
{
	float	velocity;
	int		rotation_speed;

	velocity = 0.15 * data->subsize;
	rotation_speed = 5;
	data->p_dx = cos(data->p_a) * velocity;
	data->p_dy = sin(data->p_a) * velocity;
	if (data->key_flag.up == ON)
		move_vertical(data, data->p_dx, data->p_dy, -1);
	if (data->key_flag.down == ON)
		move_vertical(data, data->p_dx, data->p_dy, 1);
	if (data->key_flag.left == ON)
        move_sideways2(data, velocity, -1);
	if (data->key_flag.right == ON)
        move_sideways2(data, velocity, 1);
	if (data->key_flag.left_rot == ON)
		turn(data, -1);
	if (data->key_flag.right_rot == ON)
		turn(data, 1);
	map_to_image(data);
	all_images_to_window(data);
	return (0);
}

