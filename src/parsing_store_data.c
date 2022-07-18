#include "cub3D.h"

static bool			store_data_part_two(t_data *data, \
						t_input_flags *flag, char *trimmed_line);
static bool			store_data_part_three(t_data *data, \
						t_input_flags *flag, char *trimmed_line);
static unsigned int	convert_rgb_to_int(char *rgb);
static bool			check_rgb_format(char *rgb, int *r, int *g, int *b);

bool	store_data(t_data *data, t_input_flags *flag, char *trimmed_line)
{
	if (*trimmed_line == 'N' && *(trimmed_line + 1) == 'O' \
			&& *(trimmed_line + 2) == ' ')
	{
		if (flag->no == true)
			return (false);
		flag->no = true;
		data->north = ft_strtrim(trimmed_line + 2, " 	");
		if (access(data->north, R_OK) != 0)
			return (false);
	}
	else if (*trimmed_line == 'S' && *(trimmed_line + 1) == 'O' \
				&& *(trimmed_line + 2) == ' ')
	{
		if (flag->so == true)
			return (false);
		flag->so = true;
		data->south = ft_strtrim(trimmed_line + 2, " 	");
		if (access(data->south, R_OK) != 0)
			return (false);
	}
	else
		if (store_data_part_two(data, flag, trimmed_line) == false)
			return (false);
	return (true);
}

static bool	store_data_part_two(t_data *data, t_input_flags *flag, \
								char *trimmed_line)
{
	if (*trimmed_line == 'W' && *(trimmed_line + 1) == 'E' \
			&& *(trimmed_line + 2) == ' ')
	{
		if (flag->we == true)
			return (false);
		flag->we = true;
		data->west = ft_strtrim(trimmed_line + 2, " 	");
		if (access(data->west, R_OK) != 0)
			return (false);
	}
	else if (*trimmed_line == 'E' && *(trimmed_line + 1) == 'A' \
			&& *(trimmed_line + 2) == ' ')
	{
		if (flag->ea == true)
			return (false);
		flag->ea = true;
		data->east = ft_strtrim(trimmed_line + 2, " 	");
		if (access(data->east, R_OK) != 0)
			return (false);
	}
	else
		if (store_data_part_three(data, flag, trimmed_line) == false)
			return (false);
	return (true);
}

static bool	store_data_part_three(t_data *data, t_input_flags *flag, \
								char *trimmed_line)
{
	if (*trimmed_line == 'F' && *(trimmed_line + 1) == ' ')
	{
		if (flag->floor == true)
			return (false);
		flag->floor = true;
		data->floor_rgb = convert_rgb_to_int(trimmed_line + 2);
		if (data->floor_rgb == UINT_MAX)
			return (false);
	}
	else if (*trimmed_line == 'C' && *(trimmed_line + 1) == ' ')
	{
		if (flag->ceiling == true)
			return (false);
		flag->ceiling = true;
		data->ceiling_rgb = convert_rgb_to_int(trimmed_line + 2);
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
	char	**splitted_rgb;
	char	*trimmed_rgb[3];

	if (check_commas_in_rgb(rgb) == false)
		return (false);
	splitted_rgb = ft_split(rgb, ',');
	if (splitted_rgb[3] != NULL)
	{
		ft_free_two_d_arr(splitted_rgb);
		return (false);
	}
	trimmed_rgb[0] = ft_strtrim(splitted_rgb[0], " 	");
	trimmed_rgb[1] = ft_strtrim(splitted_rgb[1], " 	");
	trimmed_rgb[2] = ft_strtrim(splitted_rgb[2], " 	");
	*r = ft_atoi(trimmed_rgb[0]);
	*g = ft_atoi(trimmed_rgb[1]);
	*b = ft_atoi(trimmed_rgb[2]);
	ft_free_two_d_arr(splitted_rgb);
	free(trimmed_rgb[0]);
	free(trimmed_rgb[1]);
	free(trimmed_rgb[2]);
	return (true);
}
