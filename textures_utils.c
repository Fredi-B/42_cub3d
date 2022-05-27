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

bool	pixel_is_inside_image(int x, int y, t_image *img)
{
	if (x < 0 || x > img->width -1) // not sure why -1
		return (false);
	if (y < 0 || y > img->height -1)
		return (false);
	return (true);
}

/* same as pixel_put() but with t_image * instead of t_data * */
void	image_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (pixel_is_inside_image(x, y, img) == false)
		return ;
	dst = img->addr + (y * img->line_length + x \
							* (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
