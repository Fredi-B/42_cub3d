#include "cub3D.h"

unsigned int	get_wall(int direction)
{
	if (direction == NORTH)
		return (WHITE);
	else if (direction == EAST)
		return (GREEN);
	else if (direction == SOUTH)
		return (BLUE);
	else if (direction == WEST)
		return (YELLOW);
	return (ERROR);
}

void	draw_wall_line(int direction, int image_start_x, float lineH, t_data data)
{
return;

}
