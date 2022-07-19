#include "cub3D.h"

static bool	get_walls_and_rgb(t_data *data, int fd);
static char	*get_next_trimmed_line(int fd, t_input_flags *flag);
bool		check_textures_extensions(t_data *data);
static void	init_flag(t_input_flags *flag);

int	parsing(t_data *data, char **argv)
{
	int	fd;

	if (ft_cmp_file_extension(argv[1], ".cub", 4) == false)
		err_exit(data, "Wrong file extension", 21, 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		err_exit(data, "Could not open file", 19, 1);
	if (get_walls_and_rgb(data, fd) == false)
		err_exit(data, "Misconfiguration in file", 24, 1);
	if (read_map(data, fd) == false)
		err_exit(data, "Misconfiguration in map", 23, 1);
	if (parse_map(data) == false)
		err_exit(data, "allowed chars in map: 1, 0, space \
and one and only one of the following: N E S W. Max map-size 500x500", 102, 1);
	if (validate_map(data) == false)
		err_exit(data, "Map not surrounded by walls", 27, 1);
	close(fd);
	return (0);
}

/* reads file till all six data points are stored or an error occured.
calls store_data() to store them */
static bool	get_walls_and_rgb(t_data *data, int fd)
{
	t_input_flags	flag;
	char			*trimmed_line;

	init_flag(&flag);
	while ((flag.no != true || flag.so != true || flag.we != true || flag.ea \
	!= true || flag.ceiling != true || flag.floor != true) && flag.eof != true)
	{
		trimmed_line = get_next_trimmed_line(fd, &flag);
		if (trimmed_line == NULL || trimmed_line[0] == '\0')
			continue ;
		if (store_data(data, &flag, trimmed_line) == false)
		{
			free(trimmed_line);
			return (false);
		}
		free(trimmed_line);
	}
	if (check_textures_extensions(data) == false)
		return (false);
	return (true);
}

static char	*get_next_trimmed_line(int fd, t_input_flags *flag)
{
	char	*line;
	char	*trimmed_line;

	line = get_next_line(fd);
	if (!line || line[0] == '\n')
	{
		if (!line)
			flag->eof = true;
		free(line);
		line = NULL;
		return (NULL);
	}
	trimmed_line = ft_strtrim(line, " 	\n");
	free(line);
	line = NULL;
	return (trimmed_line);
}

bool	check_textures_extensions(t_data *data)
{
	if (ft_cmp_file_extension(data->north, ".xpm", 4) == false \
		|| ft_cmp_file_extension(data->south, ".xpm", 4) == false \
		|| ft_cmp_file_extension(data->west, ".xpm", 4) == false \
		|| ft_cmp_file_extension(data->east, ".xpm", 4) == false)
		return (false);
	return (true);
}

static void	init_flag(t_input_flags *flag)
{
	flag->no = false;
	flag->so = false;
	flag->we = false;
	flag->ea = false;
	flag->ceiling = false;
	flag->floor = false;
	flag->eof = false;
}
