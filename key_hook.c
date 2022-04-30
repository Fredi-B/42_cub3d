#include "cub3D.h"

void	hook(void *param)
{
	t_array		*arr;

	arr = param;
	if (mlx_is_key_down(arr->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(arr->mlx);
	if (mlx_is_key_down(arr->mlx, MLX_KEY_UP))
		arr->g_img->instances[0].y -= 5;
	if (mlx_is_key_down(arr->mlx, MLX_KEY_DOWN))
		arr->g_img->instances[0].y += 5;
	if (mlx_is_key_down(arr->mlx, MLX_KEY_LEFT))
		arr->g_img->instances[0].x -= 5;
	if (mlx_is_key_down(arr->mlx, MLX_KEY_RIGHT))
		arr->g_img->instances[0].x += 5;
}
