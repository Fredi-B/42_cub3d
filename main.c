#include "cub3D.h"




int32_t	main(void)
{
	t_array		arr;

	map_init(&arr);
	arr.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!arr.mlx)
		exit(ERROR);
    arr.g_img = mlx_new_image(arr.mlx, WIDTH, HEIGHT);    // Creates a new image.
    mlx_image_to_window(arr.mlx, arr.g_img, 0, 0);   // Adds an image to the render queue.
    mlx_put_pixel(arr.g_img, arr.p_x, arr.p_y, 0xFFFFFFFF); // Single white pixel in the middle.
	mlx_loop_hook(arr.mlx, &hook, &arr);
	
	mlx_loop(arr.mlx);
	mlx_delete_image(arr.mlx, arr.g_img); // Once the application request an exit, cleanup.
	mlx_terminate(arr.mlx);
	return (OK);
}