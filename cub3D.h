#ifndef CUB3D_H
# define CUB3D_H

/* ----------------------------- Includes ---------------------------------- */

# include "MLX42/include/MLX42/MLX42.h"
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

/* ----------------------------- Structures -------------------------------- */

typedef struct s_map
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	unsigned int	floor_rgb;
	unsigned int	ceiling_rgb;
}				t_map;

typedef struct s_player
{
	int		position;
	char	orientation;
}				t_player;

typedef struct s_data
{
	t_map		map;
	t_player	player;
}				t_data;

/*  ------------------------ Function prototypes --------------------------- */

/*  ------------------------------ main.c----------------------------------- */

#endif
