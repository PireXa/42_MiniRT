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
		if (line[0] == 's' && line[1] == 'p')
			count++;
		free(line);
	}
	free(line);
	close(fd);
	return (count);
}

int plane_counter(char *file)
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
		if (line[0] == 'p' && line[1] == 'l')
			count++;
		free(line);
	}
	free(line);
	close(fd);
	return (count);
}

int cylinder_counter(char *file)
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
		if (line[0] == 'c' && line[1] == 'y')
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

void	free_double_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	parser(char *file, t_scene *scene)
{
	int		fd;
	int		i;
	int 	j;
	int 	k;
	char	*line;
	char 	**params;
	char 	*path;

	i = 0;
	j = 0;
	k = 0;
	path = ft_strjoin("scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);
	while ((line = get_next_line(fd)))
	{
		params = ft_split(line, ' ');
		if (params[0][0] == 's' && params[0][1] == 'p')
		{
			scene->spheres[i].center.x = ft_atoi(params[1]);
			scene->spheres[i].center.y = ft_atoi(params[2]);
			scene->spheres[i].center.z = ft_atoi(params[3]);
			scene->spheres[i].radius = atof(params[4]);
			scene->spheres[i].color = hex_to_int(params[5]);
			i++;
		}
		else if (params[0][0] == 'p' && params[0][1] == 'l')
		{
			scene->planes[j].point.x = ft_atoi(params[1]);
			scene->planes[j].point.y = ft_atoi(params[2]);
			scene->planes[j].point.z = ft_atoi(params[3]);
			scene->planes[j].normal.x = ft_atoi(params[4]);
			scene->planes[j].normal.y = ft_atoi(params[5]);
			scene->planes[j].normal.z = ft_atoi(params[6]);
			scene->planes[j].color = hex_to_int(params[7]);
			j++;
		}
		else if (params[0][0] == 'c' && params[0][1] == 'y')
		{
			scene->cylinders[j].center.x = ft_atoi(params[1]);
			scene->cylinders[j].center.y = ft_atoi(params[2]);
			scene->cylinders[j].center.z = ft_atoi(params[3]);
			scene->cylinders[j].normal.x = ft_atoi(params[4]);
			scene->cylinders[j].normal.y = ft_atoi(params[5]);
			scene->cylinders[j].normal.z = ft_atoi(params[6]);
			scene->cylinders[j].diameter = atof(params[7]);
			scene->cylinders[j].height = atof(params[8]);
			scene->cylinders[j].color = hex_to_int(params[9]);
			k++;
		}
		free_double_array(params);
		free(line);
	}
	free(line);
	close(fd);
}