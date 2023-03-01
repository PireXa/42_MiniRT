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

int	sphere_parser(char **params, t_scene *scene, int i, int line_count)
{
	char **sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		printf("Error on line %d : sphere center coordinates not valid\n", line_count);
		exit(0);
	}
	scene->spheres[i].center.x = ft_atof(sub_params[0]);
	scene->spheres[i].center.y = ft_atof(sub_params[1]);
	scene->spheres[i].center.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
	scene->spheres[i].diameter = ft_atof(params[2]);
	sub_params = ft_split(params[3], ',');
	if (double_array_len(sub_params) != 3)
	{
		printf("Error on line %d : sphere color not valid\n", line_count);
		exit(0);
	}
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
		scene->spheres[i].light_absorb_distance = 100.0f;
		scene->spheres[i].ks = 0.4f;
		scene->spheres[i].kd = 0.3f;
		scene->spheres[i].roughness = 0.0f;
	}
	if (params[4] && params[5])
		scene->spheres[i].texture = ft_atoi(params[5]);
	else
		scene->spheres[i].texture = 0;
	return (1);
}