#include "cub3D.h"

bool	pixel_is_inside_window(int x, int y, t_data *arr)
{
	if (x < 0 || x > arr->width -1)
		return (false);
	if (y < 0 || y > arr->height -1)
		return (false);
	return (true);
}

void	pixel_put(t_data *arr, int x, int y, int color)
{
	char	*dst;

	if (pixel_is_inside_window(x, y, arr) == true)
	{
		dst = arr->addr + (y * arr->size_line + x * \
								(arr->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/* same as pixel_is_inside_image() but with t_image * as argument. */
bool	pixel_is_inside_image(int x, int y, t_image *img)
{
	if (x < 0 || x > img->width -1)
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
