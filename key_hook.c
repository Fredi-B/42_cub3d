#include "cub3D.h"

static void	move_y(t_data *arr, int sign)
{
	float	y;
	int		mx;
	int		my;
	int		mp;

	y = arr->p_y + arr->p_dy * sign;
	mx = (int) (arr->p_x) >> 6;
	my = (int) (y) >> 6;
	mp = my * arr->cols + mx;
	if (arr->map[mp] == '0')
		arr->p_y = y;
}

static void	move_x(t_data *arr, int sign)
{
	float	x;
	int		mx;
	int		my;
	int		mp;

	x = arr->p_x + arr->p_dx * sign;
	mx = (int) (x) >> 6;
	my = (int) (arr->p_y) >> 6;
	mp = my * arr->cols + mx;
	if (arr->map[mp] == '0')
		arr->p_x = x;
	move_y(arr, sign);
}

static void	turn(t_data *arr, int sign)
{
	arr->p_a += 2 * ODR * sign;
	if (arr->p_a >= 2 * M_PI)
		arr->p_a -= 2 * M_PI;
	if (arr->p_a < 0)
			arr->p_a += 2 * M_PI;
	arr->p_dx = cos(arr->p_a);
	arr->p_dy = sin(arr->p_a);
}

void	hook(void *param)
{
	t_data		*arr;

	arr = param;
	if (mlx_is_key_down(arr->mlx, MLX_KEY_ESCAPE))
		{
			destroy_window(arr);
			//exit (OK);
		}
	if (mlx_is_key_down(arr->mlx, MLX_KEY_UP))
		move_x(arr, -1);
	if (mlx_is_key_down(arr->mlx, MLX_KEY_DOWN))
		move_x(arr, 1);
	if (mlx_is_key_down(arr->mlx, MLX_KEY_LEFT))
		turn(arr, -1);
	if (mlx_is_key_down(arr->mlx, MLX_KEY_RIGHT))
			turn(arr, 1);
	map_to_image(arr);
}