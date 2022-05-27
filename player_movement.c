#include "cub3D.h"

void	move_y(t_data *arr, int sign)
{
	float	y;
	int		mx;
	int		my;
	int		mp;

	y = arr->p_y + arr->p_dy * sign;
	mx = (int)(arr->p_x) >> 6;
	my = (int)(y) >> 6;
	mp = my * arr->cols + mx;
	if (arr->map[mp] == '0')
		arr->p_y = y;
}

void	move_x(t_data *arr, int sign)
{
	float	x;
	int		mx;
	int		my;
	int		mp;

	x = arr->p_x + arr->p_dx * sign;
	mx = (int)(x) >> 6;
	my = (int)(arr->p_y) >> 6;
	mp = my * arr->cols + mx;
	if (arr->map[mp] == '0')
		arr->p_x = x;
	move_y(arr, sign);
}

void	turn(t_data *arr, int sign)
{
	arr->p_a += 2 * ODR * sign;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
}
