#include "cub3D.h"

bool	is_valid_part_of_map(char part)
{
	if (part == '1' || part == '0' || part == 'N' || part == 'S' \
		|| part == 'W' || part == 'E' || part == ' ')
		return (true);
	return (false);
}
