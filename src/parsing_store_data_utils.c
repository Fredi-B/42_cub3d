#include "cub3D.h"

bool	check_commas_in_rgb(char *rgb)
{
	int	count_comma;
	int	i;

	count_comma = 0;
	i = 0;
	while (rgb[i])
	{
		if (rgb[i] == ',')
			count_comma++;
		i++;
	}
	if (count_comma != 2)
		return (false);
	return (true);
}
