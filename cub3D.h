#ifndef CUB3D_H
# define CUB3D_H

/* ----------------------------- Includes ---------------------------------- */
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

/* ----------------------------- Defines ----------------------------------- */
# define ERROR		1
# define OK			0
# define WHITE		16777215
# define BLACK		0
# define YELLOW		0xFFFF00FF
# define ODR		0.01745329252 //one degree in radians

/* ---------------------- Defines for debugging ---------------------------- */
# define dsprintf(expr) printf("\n" #expr ":\n|%s|\n", expr)
# define diprintf(expr) printf("\n" #expr ":\n|%d|\n", expr)
# define dllprintf(expr) printf("\n" #expr ":\n|%lld|\n", expr)
# define dwrite(expr) write(2, "\n" #expr "\n", strlen(#expr) + 2)

/* ----------------------------- Structures -------------------------------- */
typedef struct s_data
{
	/* map variables*/
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	long long	floor_rgb;
	long long	ceiling_rgb;
	char		*map;
	int			subsize;
	/* general variables NEEDS CHECKING!*/
	int			*num;
	int			cols;
	int			rows;
	int			i;
	int			j;
	double		rot_x;
	double		rot_y;
	double		rot_z;
	size_t		sum;
	/* player variables*/
	float		p_x; //player position x+ y
	float		p_y;
	float		p_dx; //player move in x+ y
	float		p_dy;
	float		p_a; //player angle
	/* mlx variables*/
	u_int32_t	width;
	u_int32_t	height;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_data;

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

typedef struct s_input_flags
{
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	ceiling;
	bool	floor;
}				t_input_flags;

/*  ------------------------ Function prototypes --------------------------- */
/*  ------------------------------ main.c ---------------------------------- */

/*  ---------------------------- parsing.c --------------------------------- */
int		parsing(t_data *data, char **argv);

/*  -------------------------- parsing_map.c ------------------------------- */
bool	read_map(t_data *data, int fd);
bool	parse_map(t_data *data);
/*  ---------------------- parsing_map_validation.c ------------------------ */
bool	validate_map(t_data *data);

/*  --------------------------- err_exit.c --------------------------------- */
void	err_exit(t_data *data, char *msg, int len, int exit_status);
void	free_two_d_arr(char **arr);

/* init.c*/
void	init_arr(t_data *arr);
void	free_arr(t_data *arr);
void	init_line(t_line *line);

/* line.c*/
void	set_line(t_line *line, t_data *arr, t_points p0, t_points p1);
void	draw_line(t_line *line, t_data *arr);

/* minimap.c*/
int		map_init(t_data *arr);

/* key_hook.c*/
void	hook(void *param);

/* player.c*/
void	get_player(t_data *arr, t_line *line);
void	get_rays(t_data *arr, t_line *line);

/* window.c*/
void	draw_map(t_data *arr);
void	pixel_put(t_data *arr, int x, int y, int color);
int		destroy_window(t_data *arr);
void	map_to_image(t_data *arr);

#endif
