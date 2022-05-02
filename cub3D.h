#ifndef CUB3D_H
# define CUB3D_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./MLX42/include/MLX42/MLX42_Input.h"
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
# include <memory.h>

# define ERROR		1
# define OK			0
# define WHITE		16777215
# define BLACK		0
# define YELLOW		0xFFFF00FF
# define ODR		0.01745329252 //one degree in radians


typedef struct s_array
{
	int			*num;
	int			cols;
	int			rows;
	int			i;
	int			j;
	double		rot_x;
	double		rot_y;
	double		rot_z;
	int			subsize;
	size_t		sum;
	u_int32_t	width;
	u_int32_t	height;
	float		p_x; //player position x+ y
	float		p_y;
	float		p_dx; //player move in x+ y
	float		p_dy;
	float		p_a; //player angle
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		*map;
}	t_array;

typedef struct s_line
{
	int				err;
	int				e2;
	int				sx;
	int				sy;
	int				dx;
	int				dy;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	unsigned int	color0;
	unsigned int	color1;
}	t_line;

typedef struct s_points
{
	int				x;
	int				y;
	unsigned int	color;
}				t_points;

/* init.c*/
void	init_arr(t_array *arr);
void	free_arr(t_array *arr);
void	init_line(t_line *line);

/* line.c*/
void	set_line(t_line *line, t_array *arr, t_points p0, t_points p1);
void	draw_line(t_line *line, t_array *arr);

/* minimap.c*/
int		map_init(t_array *arr);

/* key_hook.c*/
void	hook(void *param);

/* player.c*/
void	get_player(t_array *arr, t_line *line);
void	get_rays(t_array *arr, t_line *line);

/* window.c*/
void	draw_map(t_array *arr);
void	pixel_put(t_array *arr, int x, int y, int color);
int		destroy_window(t_array *arr);
void	map_to_image(t_array *arr);

#endif
