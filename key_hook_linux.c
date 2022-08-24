#include "cub3D.h"

/* Linux keycodes */
#define ESC 65307
#define LEFT 65361
#define RIGHT 65363
#define DOWN 65364
#define UP 65362



/* fct belongs to old approach */
static int	hook(int key, t_data *arr)
{
	if (key == ESC)
		{
			destroy_window(arr);
			//exit (OK);
		}
	if (key == UP)
		move_x(arr, -1);
	if (key == DOWN)
		move_x(arr, 1);
	if (key == LEFT)
		turn(arr, -1);
	if (key == RIGHT)
		turn(arr, 1);
	map_to_image(arr);
	all_images_to_window(arr);
	return (0);
}

void	key_hooks(t_data *arr)
{
	 mlx_key_hook(arr->mlx_window, hook, arr); // alter Ansatz, bei dem gedrückt halten und 2 keys gleichzeitig nicht funktioniert
	// mlx_hook(arr->mlx_window, 2, 0, &hook, arr);
	//mlx_hook(arr->mlx_window, 2, 0, &key_pressed, arr); // neuer Ansatz
	//mlx_hook(arr->mlx_window, 3, 0, &key_released, arr);	
	//mlx_loop_hook(arr->mlx, &hook, arr);

}
