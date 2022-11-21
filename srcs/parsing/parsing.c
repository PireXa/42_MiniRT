#include "../../inc/minirt.h"

int	sphere_counter(char *file)
{
	int	fd;
	int	count;
	char	*line;
	char 	*path;

	count = 0;
	path = ft_strjoin("./scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	free(line);
	close(fd);
	return (count);
}

int	hex_to_int(char *hex)
{
	int	i;
	int	color;

	i = 0;
	color = 0;
	while (hex[i])
	{
		color *= 16;
		if (hex[i] >= '0' && hex[i] <= '9')
			color += hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			color += hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			color += hex[i] - 'A' + 10;
		i++;
	}
	return (color);
}

void	parser(char *file, t_sphere *sphere)
{
	int		fd;
	int		i;
	char	*line;
	char 	**params;
	char 	*path;

	i = 0;
	path = ft_strjoin("scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);
	while ((line = get_next_line(fd)))
	{
		params = ft_split(line, ' ');
		sphere[i].center.x = ft_atoi(params[0]);
		sphere[i].center.y = ft_atoi(params[1]);
		sphere[i].center.z = ft_atoi(params[2]);
		sphere[i].radius = atof(params[3]);
		sphere[i].color = hex_to_int(params[4]);
		free(line);
		i++;
	}
	free(line);
	close(fd);
}