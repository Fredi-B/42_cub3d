#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
#include <memory.h>

#define WIDTH		1024
#define HEIGHT		512
# define ERROR		1
# define OK			0
typedef struct s_array
{
	size_t		cols;
	size_t		rows;
	size_t		sum;
	int			width;
	int			height;
	float		p_x; //player position x+ y
	float		p_y;
	mlx_t		*mlx;
	mlx_image_t	*g_img;
	int			**map;

}	t_array;

extern mlx_image_t *g_img;


/* minimap.c*/
int		map_init(t_array *arr);

/* main.c*/

/* keyhook*/
void	hook(void *param);

#endif
