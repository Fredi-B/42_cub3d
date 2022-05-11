#include "cub3D.h"

static bool			store_data_part_two(t_data *data, \
						t_input_flags *flag, char **splitted_line);
static bool			store_data_part_three(t_data *data, \
						t_input_flags *flag, char **splitted_line);
static unsigned int	convert_rgb_to_int(char *rgb);
static bool			check_rgb_format(char *rgb, int *r, int *g, int *b);


bool	store_data(t_data *data, t_input_flags *flag, char **splitted_line)
{
	if (ft_strncmp(splitted_line[0], "NO\0", 3) == 0)
	{
		if (flag->no == true)
			return (false);
		flag->no = true;
		data->north = ft_strdup(splitted_line[1]);
	}
	else if (ft_strncmp(splitted_line[0], "SO\0", 3) == 0)
	{
		if (flag->so == true)
			return (false);
		flag->so = true;
		data->south = ft_strdup(splitted_line[1]);
	}
	else
		if (store_data_part_two(data, flag, splitted_line) == false)
			return (false);
	return (true);
}

bool	store_data_part_two(t_data *data, t_input_flags *flag, char **splitted_line)
{
	if (ft_strncmp(splitted_line[0], "WE\0", 3) == 0)
	{
		if (flag->we == true)
			return (false);
		flag->we = true;
		data->west = ft_strdup(splitted_line[1]);
	}
	else if (ft_strncmp(splitted_line[0], "EA\0", 3) == 0)
	{
		if (flag->ea == true)
			return (false);
		flag->ea = true;
		data->east = ft_strdup(splitted_line[1]);
	}
	else
		if (store_data_part_three(data, flag, splitted_line) == false)
			return (false);
	return (true);
}

bool	store_data_part_three(t_data *data, t_input_flags *flag, char **splitted_line)
{
	if (ft_strncmp(splitted_line[0], "F\0", 2) == 0)
	{
		if (flag->floor == true)
			return (false);
		flag->floor = true;
		data->floor_rgb = convert_rgb_to_int(splitted_line[1]);
		if (data->floor_rgb == UINT_MAX)
			return (false);
	}
	else if (ft_strncmp(splitted_line[0], "C\0", 2) == 0)
	{
		if (flag->ceiling == true)
			return (false);
		flag->ceiling = true;
		data->ceiling_rgb = convert_rgb_to_int(splitted_line[1]);
		if (data->ceiling_rgb == UINT_MAX)
			return (false);
	}
	else
		return (false);
	return (true);
}

static unsigned int	convert_rgb_to_int(char *rgb)
{
	int				r;
	int				g;
	int				b;

	if (check_rgb_format(rgb, &r, &g, &b) == false)
		return (UINT_MAX);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (UINT_MAX);
	return ((r << 16) + (g << 8) + b);
}

static bool	check_rgb_format(char *rgb, int *r, int *g, int *b)
{
	int		count_comma;
	int		i;
	char	**splitted_rgb;

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
	splitted_rgb = ft_split(rgb, ',');
	if (splitted_rgb[3] != NULL)
	{
		free_two_d_arr(splitted_rgb);
		return (false);
	}
	*r = ft_atoi(splitted_rgb[0]);
	*g = ft_atoi(splitted_rgb[1]);
	*b = ft_atoi(splitted_rgb[2]);
	free_two_d_arr(splitted_rgb);
	return (true);
}
