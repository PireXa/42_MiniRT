/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MINIRT                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void   parser(char *file, t_scene *scene)
{
	int       fd;
	int		i;
	int    j;
	int    k;
	int    l;
	int    m;
	int    n;
	int		line_count;
	char   *line;
	char   **params;
	char   **sub_params;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	m = 0;
	n = 0;
	line_count = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31mError\nFile not found\n");
		exit(0);
	}
	while ((line = get_next_line(fd)))
	{
		params = tab_space_split(line);
		if (params[0][0] == 's' && params[0][1] == 'p')
			i += sphere_parser(params, scene, i, line_count);
		else if (params[0][0] == 'p' && params[0][1] == 'l')
			j += plane_parser(params, scene, j, line_count);
		else if (params[0][0] == 'c' && params[0][1] == 'y')
			k += cylinder_parser(params, scene, k, line_count);
		else if (params[0][0] == 't' && params[0][1] == 'r')
		{
			sub_params = ft_split(params[1], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : triangle point 1 not valid\n", line_count);
				exit(0);
			}
			scene->triangles[l].p1.x = ft_atof(sub_params[0]);
			scene->triangles[l].p1.y = ft_atof(sub_params[1]);
			scene->triangles[l].p1.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[2], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : triangle point 2 not valid\n", line_count);
				exit(0);
			}
			scene->triangles[l].p2.x = ft_atof(sub_params[0]);
			scene->triangles[l].p2.y = ft_atof(sub_params[1]);
			scene->triangles[l].p2.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[3], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : triangle point 3 not valid\n", line_count);
				exit(0);
			}
			scene->triangles[l].p3.x = ft_atof(sub_params[0]);
			scene->triangles[l].p3.y = ft_atof(sub_params[1]);
			scene->triangles[l].p3.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[4], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : triangle color not valid\n", line_count);
				exit(0);
			}
			scene->triangles[l].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
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
		else if (params[0][0] == 'C' && !params[0][1])
		{
			sub_params = ft_split(params[1], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : camera origin not valid\n", line_count);
				exit(0);
			}
			scene->cameras[m].origin.x = ft_atof(sub_params[0]);
			scene->cameras[m].origin.y = ft_atof(sub_params[1]);
			scene->cameras[m].origin.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			sub_params = ft_split(params[2], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : camera normal not valid\n", line_count);
				exit(0);
			}
			scene->cameras[m].normal.x = ft_atof(sub_params[0]);
			scene->cameras[m].normal.y = ft_atof(sub_params[1]);
			scene->cameras[m].normal.z = ft_atof(sub_params[2]);
			normalize_vector(&scene->cameras[m].normal);
			free_double_array(sub_params);
			scene->cameras[m].fov = ft_atof(params[3]);
			scene->cameras[m].view_matrix = set_cam_wrld_mtrx(scene->cameras[m],
													   (t_vector) {0, 1, 0});
			m++;
		}
		else if (params[0][0] == 'L' && !params[0][1])
		{
			sub_params = ft_split(params[1], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : light origin not valid\n", line_count);
				exit(0);
			}
			scene->lights[n].origin.x = ft_atof(sub_params[0]);
			scene->lights[n].origin.y = ft_atof(sub_params[1]);
			scene->lights[n].origin.z = ft_atof(sub_params[2]);
			free_double_array(sub_params);
			scene->lights[n].intensity = ft_atof(params[2]);
			sub_params = ft_split(params[3], ',');
			if (double_array_len(sub_params) != 3)
			{
				printf("Error on line %d : light color not valid\n", line_count);
				exit(0);
			}
			scene->lights[n].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
			free_double_array(sub_params);
			n++;
		}
		else if (params[0][0] == 'A' && !params[0][1])
		{
			scene->amb_light[0].intensity = ft_atof(params[1]);
			sub_params = ft_split(params[2], ',');
			scene->amb_light[0].color = rgb_to_int(ft_atoi(sub_params[0]), ft_atoi(sub_params[1]), ft_atoi(sub_params[2]));
			free_double_array(sub_params);
		}
		free_double_array(params);
		free(line);
		line_count++;
	}
	free(line);
	close(fd);
}
