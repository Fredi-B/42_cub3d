#include "cub3D.h"

static int		key_pressed(int key, t_data *arr);
static int		key_released(int key, t_data *arr);
static void		move_y(t_data *arr, int sign);
static void		move_x(t_data *arr, int sign);
static void		turn(t_data *arr, int sign);

void	key_hooks(t_data *arr)
{
	mlx_hook(arr->mlx_window, 2, 0, &key_pressed, arr);
	mlx_hook(arr->mlx_window, 3, 0, &key_released, arr);
	// mlx_loop_hook(arr->mlx, &hook, 0); //segfaults: fct nicht in meiner mlx?
}

/* sets key_flags to on */
static int	key_pressed(int key, t_data *arr)
{
	if (key == ESC)
	{
		destroy_window(arr);
		exit (OK);
	}
	if (key == UP)
		arr->key_flag.up = ON;
	if (key == DOWN)
		arr->key_flag.up = ON;
	if (key == LEFT)
		arr->key_flag.up = ON;
	if (key == RIGHT)
		arr->key_flag.up = ON;
	return (0);
}

/* sets key_flags to off */
static int	key_released(int key, t_data *arr)
{
	if (key == UP)
		arr->key_flag.up = OFF;
	if (key == DOWN)
		arr->key_flag.up = OFF;
	if (key == LEFT)
		arr->key_flag.up = OFF;
	if (key == RIGHT)
		arr->key_flag.up = OFF;
	map_to_image(arr);			//
	all_images_to_window(arr); // die zwei Zeilen müssten ans Ende von hook(), aber da segfaults 
	return (0);
}

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
	// if (arr->map[mp] == '0') //hier stimmt gerade was nicht: if nie true
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
	// if (arr->map[mp] == '0') //hier stimmt gerade was nicht: if nie true
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

/* supposed to update player position using key_flags */
int	hook(t_data *arr)
{
	// dwrite(test);
	// diprintf(arr->key_flag.up);
	if (arr->key_flag.up == ON)
		move_x(arr, -1);
	if (arr->key_flag.down == ON)
		move_x(arr, 1);
	if (arr->key_flag.left == ON)
		turn(arr, -1);
	if (arr->key_flag.right == ON)
		turn(arr, 1);
	map_to_image(arr);
	all_images_to_window(arr);
	return (0);
}
