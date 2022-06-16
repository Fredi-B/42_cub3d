#ifndef CUB3D_H
# define CUB3D_H

/* ----------------------------- Includes ---------------------------------- */
//# include "./MLX42/include/MLX42/MLX42.h"
//# include "./MLX42/include/MLX42/MLX42_Input.h"
# include "./minilibX/mlx.h"
# include "libft/libft.h"
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <memory.h>

/* ----------------------------- Defines ----------------------------------- */
# define ERROR		1
# define OK			0
# define WHITE		16777215
# define BLACK		0
# define GREEN		0x00FF00
# define BLUE		0x00BEFF
# define YELLOW		0xFFFF00FF
# define ODR		0.01745329252 //one degree in radians
# define ODR01		0.001745329252 //0.1 degree in radia
# define NORTH		0
# define EAST		1
# define SOUTH		2
# define WEST		3
# define ON			1
# define OFF		0




/* ---------------------- Defines for debugging ---------------------------- */
# define dsprintf(expr) printf("\n" #expr ":\n|%s|\n", expr)
# define diprintf(expr) printf("\n" #expr ":\n|%d|\n", expr)
# define dwrite(expr) write(2, "\n" #expr "\n", strlen(#expr) + 2)

/* ----------------------------- Structures -------------------------------- */

typedef struct s_key_flags
{
	int	up;
	int	down;
	int	left;
	int	right;
}				t_key_flags;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		size_line; //ist das das gleiche wie line_length?
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_data
{
	/* map variables*/
	char			*north;
	char			*east;
	char			*south;
	char			*west;
	unsigned int	floor_rgb;
	unsigned int	ceiling_rgb;
	char			*map;
	int				subsize;
	int				sub_bit;
	int				scale_map;
	int				map_flag;
	/* general variables NEEDS CHECKING!*/
	int			*num;
	int			cols;
	int			rows;
	int			dof;
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

	/* mlx variables OLDMLXLIB*/
	void		*mlx;
	void		*mlx_window;
	void		*img;
	void		*img_map;
	char		*addr;
	char		*addr_map;
	int			bits_per_pixel;
	int			line_length;
	int			size_line;
	int			size_line_map;
	int			endian;
	int			width;
	int			height;
	/* mlx variables OLDMLXLIB in eigenem struct für mehrere images */
	t_image		xpm_file[4];
	t_image		wall[4];
	t_image		first_person_view;
	t_image		minimap;
	// t_image		player_in_minimap;
	
	/* mlx variables NEWMLXLIB*/
	// u_int32_t	width;
	// u_int32_t	height;
	// mlx_t		*mlx;
	// mlx_image_t	*img;

	/* key hook variables */
	t_key_flags	key_flag;
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
	bool	eof;
}				t_input_flags;

typedef struct s_counter
{
	int	tmp_x;
	int	tmp_y;
	int	map;
	int	line;
}				t_counter;

/*  ------------------------ Function prototypes --------------------------- */
/*  ------------------------------ main.c ---------------------------------- */

/*  ---------------------------- parsing.c --------------------------------- */
int		parsing(t_data *data, char **argv);
/*  ----------------------- parsing_store_data.c ---------------------------- */
bool	store_data(t_data *data, t_input_flags *flag, char *trimmed_line);
/*  -------------------- parsing_store_data_utils.c ------------------------- */
bool	check_commas_in_rgb(char *rgb);
/*  -------------------------- parsing_map.c ------------------------------- */
bool	read_map(t_data *data, int fd);
bool	parse_map(t_data *data);
/*  ----------------------- parsing_map_utils.c ---------------------------- */
bool	malloc_map(t_data *data);
void	init_counter_and_flag(t_counter *i, bool *only_one_player_flag);
bool	parse_tmp_map_into_map(t_data *data, t_counter *i, char **tmp_map, bool *only_one_player_flag);
/*  ----------------------- parsing_map_utils.c ---------------------------- */
bool	is_valid_part_of_map(char part);

/*  ---------------------- parsing_map_validation.c ------------------------ */
bool	validate_map(t_data *data);

/*  --------------------------- err_exit.c --------------------------------- */
void	err_exit(t_data *data, char *msg, int len, int exit_status);
void	free_data(t_data *data);

/*  --------------------------- textures.c --------------------------------- */
bool	put_walls_in_images(t_data *arr);

/*  ------------------------ textures_utils.c ------------------------------ */
void	*my_new_image(void *mlx, int width, int height, t_image *copy);
bool	pixel_is_inside_image(int x, int y, t_image *img);
void	image_pixel_put(t_image *img, int x, int y, int color);

/* init.c*/
void	init_arr(t_data *arr);
void	free_arr(t_data *arr);
void	init_line(t_line *line);

/* line.c*/
void	set_line(t_line *line, t_data *arr, t_points p0, t_points p1);
void	draw_line(t_line *line, t_data *arr);

/* minimap.c*/
int		map_init(t_data *arr);

/* minimap_ray.c*/
void	inside_360(float *ra);
float	draw_ray_minimap(int *image_start_x, int *direction, t_data *arr, t_line *line, float ra);
void	draw_wall(int *image_start_x, int *direction, t_data *arr, t_line *line, float ra, int r, float dist_t);
float	dist_vec(t_data *arr, float x, float y);

/* key_hook.c*/
//void	hook(void *param); NEWMINILIB
void	key_hooks(t_data *arr);

/* player_movement.c */
void	move_y(t_data *arr, int sign);
void	move_x(t_data *arr, int sign);
void	turn(t_data *arr, int sign);

//int		deal_key(int key, t_array *fdf_win);


/* player.c*/
void	get_player(t_data *arr, t_line *line);
void	get_rays(t_data *arr, t_line *line);

/* walls.c*/
unsigned int	get_wall(int direction, float line_h);
void	draw_wall_line(int *direction, int *image_start_x, float line_h, t_data *data, int r);

/* window.c*/
void	draw_map(t_data *arr);
void	pixel_put(t_data *arr, int x, int y, int color);
void	destroy_window(t_data *arr);
void	map_to_image(t_data *arr);
void	all_images_to_window(t_data *arr);
bool	pixel_is_inside_window(int x, int y, t_data *arr);

#endif
