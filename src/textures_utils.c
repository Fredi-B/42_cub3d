#include "cub3D.h"

void	*my_new_image(void *mlx, int width, int height, t_image *copy)
{
	copy->img = mlx_new_image(mlx, width, height);
	if (copy->img == NULL)
		return (NULL);
	copy->addr = mlx_get_data_addr(copy->img, &copy->bits_per_pixel, \
									&copy->line_length, &copy->endian);
	copy->width = width;
	copy->height = height;
	return (copy->img);
}
