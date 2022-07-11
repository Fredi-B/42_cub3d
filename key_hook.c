#include "cub3D.h"

/* Mac keycodes */
#define ESC 53
#define UP 13
#define DOWN 1
#define RIGHT 0
#define LEFT 2
#define LEFT_ROT 123
#define RIGHT_ROT 124
#define MINIMAP 46

static int	key_pressed(int key, t_data *arr);
static int	key_released(int key, t_data *arr);
static int	hook(t_data *arr);

int	red_x_exit(t_data *arr)
{
	mlx_destroy_image(arr->mlx, arr->img);
	mlx_destroy_image(arr->mlx, arr->img_map);
	mlx_destroy_window(arr->mlx, arr->mlx_window);
	free_arr(arr);
	exit(0);
	return (0);
}

void	key_hooks(t_data *arr)
{
	mlx_hook(arr->mlx_window, 2, 0, &key_pressed, arr);
	mlx_hook(arr->mlx_window, 3, 0, &key_released, arr);
	mlx_hook(arr->mlx_window, 17, (1L << 17), &red_x_exit, arr);
	mlx_loop_hook(arr->mlx, &hook, arr);
}

/* sets key_flags to on */
static int	key_pressed(int key, t_data *arr)
{
	if (key == ESC)
		destroy_window(arr);
	if (key == UP)
		arr->key_flag.up = ON;
	if (key == DOWN)
		arr->key_flag.down = ON;
	if (key == LEFT)
		arr->key_flag.left = ON;
	if (key == RIGHT)
		arr->key_flag.right = ON;
	if (key == LEFT_ROT)
		arr->key_flag.left_rot = ON;
	if (key == RIGHT_ROT)
		arr->key_flag.right_rot = ON;
	if (key == MINIMAP)
		arr->draw_map_flag = ON;
	return (0);
}

/* sets key_flags to off */
static int	key_released(int key, t_data *arr)
{
	if (key == UP)
		arr->key_flag.up = OFF;
	if (key == DOWN)
		arr->key_flag.down = OFF;
	if (key == LEFT)
		arr->key_flag.left = OFF;
	if (key == RIGHT)
		arr->key_flag.right = OFF;
	if (key == LEFT_ROT)
		arr->key_flag.left_rot = OFF;
	if (key == RIGHT_ROT)
		arr->key_flag.right_rot = OFF;
	if (key == MINIMAP)
		arr->draw_map_flag = OFF;
	return (0);
}

/* update player position using key_flags */
static int	hook(t_data *arr)
{
	if (arr->key_flag.up == ON)
		move_x(arr, -3);
	if (arr->key_flag.down == ON)
		move_x(arr, 3);
	if (arr->key_flag.left == ON)
		move_sideways(arr, -3);
	if (arr->key_flag.right == ON)
		move_sideways(arr, 3);
	if (arr->key_flag.left_rot == ON)
		turn(arr, -1);
	if (arr->key_flag.right_rot == ON)
		turn(arr, 1);
	map_to_image(arr);
	all_images_to_window(arr);
	return (0);
}
