#include "cub3D.h"

void	hook(void *param)
{
	t_array		*arr;

	arr = param;
	if (mlx_is_key_down(arr->mlx, MLX_KEY_ESCAPE))
		{
			destroy_window(arr);
			exit (OK);
		}
	if (mlx_is_key_down(arr->mlx, MLX_KEY_UP))
	{
		arr->p_x -= arr->p_dx;
		arr->p_y -= arr->p_dy;
	}
	if (mlx_is_key_down(arr->mlx, MLX_KEY_DOWN))
	{
		arr->p_x += arr->p_dx;
		arr->p_y += arr->p_dy;
	}
	if (mlx_is_key_down(arr->mlx, MLX_KEY_LEFT))
	{
		arr->p_a -= 2*ODR; //0.01; 
		if (arr->p_a < 0)
			arr->p_a += 2* M_PI;
		arr->p_dx = cos(arr->p_a);
		arr->p_dy = sin(arr->p_a);
	}
	if (mlx_is_key_down(arr->mlx, MLX_KEY_RIGHT))
		{
		arr->p_a += 2*ODR; //0.01;  
		if (arr->p_a > 2* M_PI)
			arr->p_a -= 2* M_PI;
		arr->p_dx = cos(arr->p_a);
		arr->p_dy = sin(arr->p_a);
		}
	map_to_image(arr);
}
