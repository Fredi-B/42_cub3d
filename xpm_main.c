#include "./MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 1024
#define HEIGHT 1024

mlx_image_t *img_deer;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		img_deer->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		img_deer->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		img_deer->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		img_deer->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t			*mlx;
	xpm_t			*xpm_deer;
	mlx_image_t		*custom_deer;
	unsigned int	x;
	unsigned int	y;


	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);

	xpm_deer = mlx_load_xpm42("./deer.xpm42");
	img_deer = mlx_texture_to_image(mlx, &xpm_deer->texture);
	custom_deer = mlx_new_image(mlx, img_deer->width * 2, img_deer->height * 2);
	memset(custom_deer->pixels, 255, img_deer->width * 2 * img_deer->height * 2 * sizeof(int));
	y = 0;
	while (y < img_deer->height)
	{
		x = 0;
		while (x < img_deer->width)
		{
			mlx_put_pixel(custom_deer, x, y, img_deer->pixels[(y * custom_deer->width) + x]);
			// custom_deer->pixels[(y * 2 * custom_deer->width) + x * 2] = img_deer->pixels[(y * custom_deer->width) + x];
			x++;
		}
		y++;

	}
	mlx_image_to_window(mlx, img_deer, 100, 100);
	mlx_image_to_window(mlx, custom_deer, 500, 500);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}