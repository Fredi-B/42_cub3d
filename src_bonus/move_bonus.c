#include "cub3D.h"

static bool	mov_coll(t_data *data, float x, float y)
{
	float	new_x;
	float	new_y;
	int		i;
	int		j;

	new_x = data->p_x + x;
	new_y = data->p_y + y;
	i = new_x / data->subsize;
	j = new_y / data->subsize;
	if (check_for_wall(data, i, j))
		return (true);
	else if (saftey_wall(data, new_x, new_y, 12))
		return (true);
	else if (go_by_pixel(data, new_x, new_y))
		return (true);
	return (false);
}

static void	move_vertical(t_data *data, float x, float y, int sign)
{
	if (!mov_coll(data, x * sign, y * sign))
	{
		data->p_x += x * sign;
		data->p_y += y * sign;
	}
}

void	move_sideways2(t_data *arr, float velocity, int sign)
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

int	move(t_data *data)
{
	data->p_dx = cos(data->p_a) * data->velocity;
	data->p_dy = sin(data->p_a) * data->velocity;
	velocity_ctrl(data);
	lap_time(data);
	if (data->key_flag.up == ON)
		move_vertical(data, data->p_dx, data->p_dy, -1);
	if (data->key_flag.down == ON)
		move_vertical(data, data->p_dx, data->p_dy, 1);
	if (data->key_flag.left == ON)
		move_sideways2(data, data->velocity, -1);
	if (data->key_flag.right == ON)
		move_sideways2(data, data->velocity, 1);
	if (data->key_flag.left_rot == ON)
		turn(data, -1);
	if (data->key_flag.right_rot == ON)
		turn(data, 1);
	return (0);
}
