#include "../../inc/minirt.h"

int    sphere_counter(char *file)
{
	int    fd;
	int    count;
	char   *line;

	count = 0;
	/*path = ft_strjoin("./scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);*/
	fd = open(file, O_RDONLY);
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
	int    fd;
	int    count;
	char   *line;
// char   *path;

	count = 0;
	/*path = ft_strjoin("./scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);*/
	fd = open(file, O_RDONLY);
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
	int    fd;
	int    count;
	char   *line;
// char   *path;

	count = 0;
	/*path = ft_strjoin("./scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);*/
	fd = open(file, O_RDONLY);
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

int    triangle_counter(char *file)
{
	int    fd;
	int    count;
	char   *line;
// char   *path;

	count = 0;
	/*path = ft_strjoin("./scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);*/
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == 't' && line[1] == 'r')
			count++;
		free(line);
	}
	free(line);
	close(fd);
	return (count);
}

int    camera_counter(char *file)
{
	int    fd;
	int    count;
	char   *line;
// char   *path;

	count = 0;
	/*path = ft_strjoin("./scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);*/
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == 'c')
			count++;
		free(line);
	}
	free(line);
	close(fd);
	return (count);
}

int    light_counter(char *file)
{
	int    fd;
	int    count;
	char   *line;
// char   *path;

	count = 0;
	/*path = ft_strjoin("./scenes/", file);
	fd = open(path, O_RDONLY);
	free(path);*/
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == 'l')
			count++;
		free(line);
	}
	free(line);
	close(fd);
	return (count);
}

int    rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void   free_double_array(char **array)
{
	int    i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("array[%d] = %s|\n", i, array[i]);
		i++;
	}
	printf("\n");
}

void	get_to_eof(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)))
		free(line);
	free(line);
}

float	get_material_data(char *mat_ref, int data)
{
	int		fd;
	char	*fds;
	char	**split;
	float	ret;

	fd = open("./materials/materials_data", O_RDONLY);
	fds = get_next_line(fd);
	while (ft_strncmp(fds, mat_ref, ft_strlen(mat_ref) - 1))
	{
		free(fds);
		fds = get_next_line(fd);
	}
	split = tab_space_split(fds);
	ret = ft_atof(split[data]);
	free_double_array(split);
	free(fds);
	get_to_eof(fd);
	close(fd);
	return (ret);
}

void   parser(char *file, t_scene *scene)
{
	int       fd;
	int       i;
	int    j;
	int    k;
	int    l;
	int    m;
	int    n;
	char   *line;
	char   **params;
	char   **sub_params;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	m = 0;
	n = 0;
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
//    params = ft_split(line, ' ');
		params = tab_space_split(line);
		if (params[0][0] == 's' && params[0][1] == 'p')
		{
			sub_params = ft_split(params[1], ',');
			scene->spheres[i].center.x = ft_atof(sub_params[0]);
			scene->spheres[i].center.y = ft_atof(sub_params[1]);
			scene->spheres[i].center.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			scene->spheres[i].diameter = ft_atof(params[2]);
			/*if (params[4])
			{
				scene->spheres[i].light_absorb_ratio = ft_atof(params[3]);
				sub_params = ft_split(params[4], ',');
			}
			else
			{
				scene->spheres[i].light_absorb_ratio = 1;
				sub_params = ft_split(params[3], ',');
			}*/
			sub_params = ft_split(params[3], ',');
			scene->spheres[i].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
			free_double_array(sub_params);
			if (params[4])
			{
				scene->spheres[i].light_absorb_ratio = get_material_data(params[4], 1);
				scene->spheres[i].refraction_index = get_material_data(params[4], 2);
				scene->spheres[i].light_absorb_distance = get_material_data(params[4], 3);
				scene->spheres[i].ks = get_material_data(params[4], 4);
				scene->spheres[i].kd = get_material_data(params[4], 5);
				scene->spheres[i].roughness = get_material_data(params[4], 6);
			}
			else
			{
				scene->spheres[i].light_absorb_ratio = 1;
				scene->spheres[i].refraction_index = 1.2f;
				scene->spheres[i].light_absorb_distance = 1.0f;
				scene->spheres[i].ks = 0.4f;
				scene->spheres[i].kd = 0.3f;
				scene->spheres[i].roughness = 0.0f;
			}
			if (params[5])
				scene->spheres[i].texture = ft_atoi(params[5]);
			else
				scene->planes[i].texture = 0;
//			printf("sphere[%d] = {center = (%f, %f, %f)\ndiameter = %f\ncolor = %d\nlight_absorb_ratio = %f\nrefraction_index = %f\nlight_absorb_distance = %f}\n", i, scene->spheres[i].center.x, scene->spheres[i].center.y, scene->spheres[i].center.z, scene->spheres[i].diameter, scene->spheres[i].color, scene->spheres[i].light_absorb_ratio, scene->spheres[i].refraction_index, scene->spheres[i].light_absorb_distance);
			i++;
		}
		else if (params[0][0] == 'p' && params[0][1] == 'l')
		{
			sub_params = ft_split(params[1], ',');
			scene->planes[j].point.x = ft_atof(sub_params[0]);
			scene->planes[j].point.y = ft_atof(sub_params[1]);
			scene->planes[j].point.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[2], ',');
			scene->planes[j].normal.x = ft_atof(sub_params[0]);
			scene->planes[j].normal.y = ft_atof(sub_params[1]);
			scene->planes[j].normal.z = ft_atof(sub_params[2]);
			normalize_vector(&scene->planes[j].normal);
			free_double_array(sub_params);
			/*if (params[4])
			{
				scene->planes[j].light_absorb_ratio = ft_atof(params[3]);
				sub_params = ft_split(params[4], ',');
			}
			else
			{
				scene->planes[j].light_absorb_ratio = 0.3f;
				sub_params = ft_split(params[3], ',');
			}*/
			sub_params = ft_split(params[3], ',');
			scene->planes[j].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
			free_double_array(sub_params);
			if (params[4])
			{
				scene->planes[j].light_absorb_ratio = get_material_data(params[4], 1);
				scene->planes[j].refraction_index = get_material_data(params[4], 2);
				scene->planes[j].light_absorb_distance = get_material_data(params[4], 3);
				scene->planes[j].ks = get_material_data(params[4], 4);
				scene->planes[j].kd = get_material_data(params[4], 5);
				scene->planes[j].roughness = get_material_data(params[4], 6);
			}
			else
			{
				scene->planes[j].light_absorb_ratio = 0.3f;
				scene->planes[j].refraction_index = 1.2f;
				scene->planes[j].light_absorb_distance = 50.0f;
				scene->planes[j].ks = 0.4f;
				scene->planes[j].kd = 0.3f;
				scene->planes[j].roughness = 0.0f;
			}
			if (params[5])
				scene->planes[j].texture = ft_atoi(params[5]);
			else
				scene->planes[j].texture = 0;
//			printf("plane[%d] = {point = (%f, %f, %f)\nnormal = (%f, %f, %f)\ncolor = %d\nlight_absorb_ratio = %f\nrefraction_index = %f\nlight_absorb_distance = %f}\n", j, scene->planes[j].point.x, scene->planes[j].point.y, scene->planes[j].point.z, scene->planes[j].normal.x, scene->planes[j].normal.y, scene->planes[j].normal.z, scene->planes[j].color, scene->planes[j].light_absorb_ratio, scene->planes[j].refraction_index, scene->planes[j].light_absorb_distance);
			j++;
		}
		else if (params[0][0] == 'c' && params[0][1] == 'y')
		{
			t_vector v1;

			sub_params = ft_split(params[1], ',');
			scene->cylinders[k].base_center.x = ft_atof(sub_params[0]);
			scene->cylinders[k].base_center.y = ft_atof(sub_params[1]);
			scene->cylinders[k].base_center.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[2], ',');
			v1.x = ft_atof(sub_params[0]);
			v1.y = ft_atof(sub_params[1]);
			v1.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			normalize_vector(&v1);
			scene->cylinders[k].normal = v1;
			scene->cylinders[k].diameter = ft_atof(params[3]);
			scene->cylinders[k].height = ft_atof(params[4]);
			/*if (params[6])
			{
				scene->cylinders[k].light_absorb_ratio = ft_atof(params[5]);
				sub_params = ft_split(params[6], ',');
			}
			else
			{
				scene->cylinders[k].light_absorb_ratio = 1;
				sub_params = ft_split(params[5], ',');
			}*/
			sub_params = ft_split(params[5], ',');
			scene->cylinders[k].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
			free_double_array(sub_params);
			if (params[6])
			{
				scene->cylinders[k].light_absorb_ratio = get_material_data(params[6], 1);
				scene->cylinders[k].refraction_index = get_material_data(params[6], 2);
				scene->cylinders[k].light_absorb_distance = get_material_data(params[6], 3);
				scene->cylinders[k].ks = get_material_data(params[6], 4);
				scene->cylinders[k].kd = get_material_data(params[6], 5);
				scene->cylinders[k].roughness = get_material_data(params[6], 6);
			}
			else
			{
				scene->cylinders[k].light_absorb_ratio = 1;
				scene->cylinders[k].refraction_index = 1.2f;
				scene->cylinders[k].light_absorb_distance = 1.0f;
				scene->cylinders[k].ks = 0.4f;
				scene->cylinders[k].kd = 0.3f;
				scene->cylinders[k].roughness = 0.0f;
			}
			k++;
		}
		else if (params[0][0] == 't' && params[0][1] == 'r')
		{
			sub_params = ft_split(params[1], ',');
			scene->triangles[l].p1.x = ft_atof(sub_params[0]);
			scene->triangles[l].p1.y = ft_atof(sub_params[1]);
			scene->triangles[l].p1.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[2], ',');
			scene->triangles[l].p2.x = ft_atof(sub_params[0]);
			scene->triangles[l].p2.y = ft_atof(sub_params[1]);
			scene->triangles[l].p2.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[3], ',');
			scene->triangles[l].p3.x = ft_atof(sub_params[0]);
			scene->triangles[l].p3.y = ft_atof(sub_params[1]);
			scene->triangles[l].p3.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			/*if (params[4])
			{
				scene->triangles[l].light_absorb_ratio = ft_atof(params[3]);
				sub_params = ft_split(params[4], ',');
			}
			else
			{
				scene->triangles[l].light_absorb_ratio = 0.3f;
				sub_params = ft_split(params[3], ',');
			}*/
			sub_params = ft_split(params[4], ',');
//			scene->triangles[l].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
			scene->triangles[l].color = 0x920092;
			free_double_array(sub_params);
			if (params[5])
			{
				scene->triangles[l].light_absorb_ratio = get_material_data(params[5], 1);
				scene->triangles[l].refraction_index = get_material_data(params[5], 2);
				scene->triangles[l].light_absorb_distance = get_material_data(params[5], 3);
				scene->triangles[l].ks = get_material_data(params[5], 4);
				scene->triangles[l].kd = get_material_data(params[5], 5);
				scene->triangles[l].roughness = get_material_data(params[5], 6);
			}
			else
			{
				scene->triangles[l].light_absorb_ratio = 0.9f;
				scene->triangles[l].refraction_index = 1.2f;
				scene->triangles[l].light_absorb_distance = 1000.0f;
				scene->triangles[l].ks = 0.4f;
				scene->triangles[l].kd = 0.3f;
				scene->triangles[l].roughness = 0.0f;
			}
			l++;
		}
		else if (params[0][0] == 'c')
		{
			sub_params = ft_split(params[1], ',');
			scene->cameras[m].origin.x = ft_atof(sub_params[0]);
			scene->cameras[m].origin.y = ft_atof(sub_params[1]);
			scene->cameras[m].origin.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[2], ',');
			scene->cameras[m].normal.x = ft_atof(sub_params[0]);
			scene->cameras[m].normal.y = ft_atof(sub_params[1]);
			scene->cameras[m].normal.z = ft_atof(sub_params[2]);
			normalize_vector(&scene->cameras[m].normal);
			free_double_array(sub_params);
			scene->cameras[m].view_matrix = set_camera_to_world_transformation_matrix(scene->cameras[m], (t_vector){0, 1, 0});
			m++;
		}
		else if (params[0][0] == 'l')
		{
			sub_params = ft_split(params[1], ',');
			scene->lights[n].origin.x = ft_atof(sub_params[0]);
			scene->lights[n].origin.y = ft_atof(sub_params[1]);
			scene->lights[n].origin.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			scene->lights[n].intensity = ft_atof(params[2]);
			sub_params = ft_split(params[3], ',');
			scene->lights[n].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
			free_double_array(sub_params);
			n++;
		}
		free_double_array(params);
		free(line);
	}
	free(line);
	close(fd);
}
