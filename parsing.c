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
	if (get_map(data, fd) == false)
		err_exit(data, "Could not get map", 17, 1);
	return (0);
}

/* reads map into data->map.
skips empty lines in the beginning, checks against them thereafter */
bool	get_map(t_data *data, int fd)
{
	//leaks??
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		if (line[0] != '\n')
		{
			data->map = line;
			break ;
		}
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			break ;
		tmp = ft_strjoin(data->map, line);
		free(data->map);
		data->map = ft_strdup(tmp);
		free(tmp);
		free(line);
	}
	line = get_next_line(fd);
	if (line)
		return (false);
	return (true);
}
{
	t_input_flags	flag;
	int				fd;
	char			*line;
	char			*trimmed_line;
	char			**splitted_line;

	init_flag(&flag);
	while (flag.no != true || flag.so != true || flag.we != true \
			|| flag.ea != true || flag.ceiling != true || flag.floor != true)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
			continue ;
		trimmed_line = ft_strtrim(line, " 	\n");
		splitted_line = ft_split(trimmed_line, ' ');
		if (splitted_line[0] == NULL)
			continue ;
		if (splitted_line[2] != NULL)
			return (false);
		if (store_data(data, &flag, splitted_line) == false)
			return (false);
		free(line);
		free(trimmed_line);
		//free_2d(splitted_line); //auch bei return (false);
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

long long	convert_rgb_to_hex(char *rgb)
{
	long long	hex;
	int			r;
	int			g;
	int			b;

	if (check_rgb_format(rgb, &r, &g, &b) == false)
		return (-1);
	hex = ((r << 16) + (g << 8) + b);
	return (hex);
}

bool	check_rgb_format(char *rgb, int *r, int *g, int *b)
{
	int	count_comma;
	int	i;
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
	//free2d(splitted_rgb);
		return (false);
	}
	*r = ft_atoll(splitted_rgb[0]);
	*g = ft_atoll(splitted_rgb[1]);
	*b = ft_atoll(splitted_rgb[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		//free2d(splitted_rgb);
		return (false);
	}
	//free2d(splitted_rgb);
	return (true);
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