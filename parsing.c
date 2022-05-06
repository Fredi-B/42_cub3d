#include "cub3D.h"

bool			get_walls_and_rgb(t_data *data, char **argv);
void			init_flag(t_input_flags *flag);
bool			store_data(t_data *data, t_input_flags *flag, char **splitted_line);
unsigned int	convert_rgb_to_hex(char *rgb);

int	parsing(t_data *data, char **argv)
{
	if (ft_cmp_file_extension(argv[1], ".cub", 4) == false)
		err_exit(data, "Wrong file extension", 21, 1);
	if (get_walls_and_rgb(data, argv) == false)
		err_exit(data, "Misconfiguration in file", 24, 1);
	return (0);
}

bool	get_walls_and_rgb(t_data *data, char **argv)
{
	t_input_flags	flag;
	int				fd;
	char			*line;
	char			**splitted_line;

	init_flag(&flag);
	fd = open(argv[1], O_RDONLY);
	while (flag.no != true || flag.so != true || flag.we != true \
			|| flag.ea != true || flag.ceiling != true || flag.floor != true)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			continue ;
		splitted_line = ft_split(line, ' ');
		if (splitted_line[0] == NULL)
			continue ;
		if (splitted_line[2] != NULL)
			return (false);
		if (store_data(data, &flag, splitted_line) == false)
			return (false);
		free(line);
		//free_2d(splitted_line);
	}
	return (true);
}

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
	else if (ft_strncmp(splitted_line[0], "WE\0", 3) == 0)
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
		//muss ich die new line trimmen? mit nem tmp string?
	}
	else if (ft_strncmp(splitted_line[0], "F\0", 2) == 0)
	{
		if (flag->floor == true)
			return (false);
		flag->floor = true;
		data->floor_rgb = convert_rgb_to_hex(splitted_line[1]);
		if (data->floor_rgb == -1)
			return (false);
	}
	else if (ft_strncmp(splitted_line[0], "C\0", 2) == 0)
	{
		if (flag->ceiling == true)
			return (false);
		flag->ceiling = true;
		data->ceiling_rgb = convert_rgb_to_hex(splitted_line[1]);
		if (data->ceiling_rgb == -1)
			return (false);
	}
	else
		return (false);
	return (true);
}

unsigned int	convert_rgb_to_hex(char *rgb)
{
	unsigned int	hex;
	char			**splitted_rgb;
	char			*trimmed_b;

	// check misconfiguration, i.e. mehr als 3 Werte mehr kommata etc.
	splitted_rgb = ft_split(rgb, ',');
	trimmed_b = ft_strtrim(splitted_rgb[2], " \n");
	// check if between 0 - 255
	hex = ((ft_atoll(splitted_rgb[0]) << 16) + (ft_atoll(splitted_rgb[1]) << 8) \
				+ ft_atoll(trimmed_b));
	free(trimmed_b);
	//free2d(splitted_rgb);
	return (hex);
}

void	init_flag(t_input_flags *flag)
{
	flag->no = false;
	flag->so = false;
	flag->we = false;
	flag->ea = false;
	flag->ceiling = false;
	flag->floor = false;
}