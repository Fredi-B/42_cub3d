#include "cub3D.h"

static int	key_pressed(int key, t_data *arr);
static int	key_released(int key, t_data *arr);
static int	hook(t_data *arr);


/* fct belongs to old approach */
// int	hook(int key, t_data *arr)
// {
// 	if (key == ESC)
// 		{
// 			destroy_window(arr);
// 			//exit (OK);
// 		}
// 	if (key == UP)
// 		move_x(arr, -1);
// 	if (key == DOWN)
// 		move_x(arr, 1);
// 	if (key == LEFT)
// 		turn(arr, -1);
// 	if (key == RIGHT)
// 		turn(arr, 1);
// 	map_to_image(arr);
// 	all_images_to_window(arr);
// 	return (0);
// }

void	key_hooks(t_data *arr)
{
	// mlx_key_hook(arr->mlx_window, hook, arr); // alter Ansatz, bei dem gedrückt halten und 2 keys gleichzeitig nicht funktioniert
	// mlx_hook(arr->mlx_window, 2, 0, &hook, arr);
	mlx_hook(arr->mlx_window, 2, 0, &key_pressed, arr); // neuer Ansatz
	mlx_hook(arr->mlx_window, 3, 0, &key_released, arr);	
	mlx_loop_hook(arr->mlx, &hook, arr); //segfaults: fct nicht in meiner mlx?

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
		arr->key_flag.down = ON;
	if (key == LEFT)
		arr->key_flag.left = ON;
	if (key == RIGHT)
		arr->key_flag.right = ON;
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
	return (0);
}

/* update player position using key_flags */
static int	hook(t_data *arr)
{
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
