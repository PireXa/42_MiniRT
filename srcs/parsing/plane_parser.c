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

int		plane_parser(char **params, t_scene *scene, int j, int line_count)
{
	char	**sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		printf("Error on line %d : plane point coordinates not valid\n", line_count);
		exit(0);
	}
	scene->planes[j].point.x = ft_atof(sub_params[0]);
	scene->planes[j].point.y = ft_atof(sub_params[1]);
	scene->planes[j].point.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
	sub_params = ft_split(params[2], ',');
	if (double_array_len(sub_params) != 3)
	{
		printf("Error on line %d : plane normal not valid\n", line_count);
		exit(0);
	}
	scene->planes[j].normal.x = ft_atof(sub_params[0]);
	scene->planes[j].normal.y = ft_atof(sub_params[1]);
	scene->planes[j].normal.z = ft_atof(sub_params[2]);
	normalize_vector(&scene->planes[j].normal);
	free_double_array(sub_params);
	sub_params = ft_split(params[3], ',');
	if (double_array_len(sub_params) != 3)
	{
		printf("Error on line %d : plane color not valid\n", line_count);
		exit(0);
	}
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
		scene->planes[j].light_absorb_distance = 200.0f;
		scene->planes[j].ks = 0.4f;
		scene->planes[j].kd = 0.3f;
		scene->planes[j].roughness = 0.0f;
	}
	if (params[4] && params[5])
		scene->planes[j].texture = ft_atoi(params[5]);
	else
		scene->planes[j].texture = 0;
	return (1);
}
