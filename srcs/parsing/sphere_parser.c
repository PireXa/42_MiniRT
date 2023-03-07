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

void	sphere_parser1(char **params, t_data *data, int i, int linecount)
{
	char	**sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d : sphere center "
				"coordinates not valid\033[0m\n", linecount));
	}
	data->scene->spheres[i].center.x = ft_atof(sub_params[0]);
	data->scene->spheres[i].center.y = ft_atof(sub_params[1]);
	data->scene->spheres[i].center.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
	data->scene->spheres[i].diameter = ft_atof(params[2]);
	sub_params = ft_split(params[3], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d : sphere "
				"color not valid\033[0m\n", linecount));
	}
	data->scene->spheres[i].color = rgb_to_int(ft_atoi(sub_params[0]),
			ft_atoi(sub_params[1]),
			ft_atoi(sub_params[2]));
	free_double_array(sub_params);
}

void	sphere_parser2(char **params, t_scene *s, int i)
{
	if (params[4])
	{
		s->spheres[i].light_absorb_ratio = get_material_data(params[4], 1);
		s->spheres[i].refraction_index = get_material_data(params[4], 2);
		s->spheres[i].light_absorb_distance = get_material_data(params[4], 3);
		s->spheres[i].ks = get_material_data(params[4], 4);
		s->spheres[i].kd = get_material_data(params[4], 5);
		s->spheres[i].roughness = get_material_data(params[4], 6);
	}
	else
	{
		s->spheres[i].light_absorb_ratio = 1;
		s->spheres[i].refraction_index = 1.2f;
		s->spheres[i].light_absorb_distance = 100.0f;
		s->spheres[i].ks = 0.4f;
		s->spheres[i].kd = 0.3f;
		s->spheres[i].roughness = 0.0f;
	}
}

int	sphere_parser(char **params, t_data *data, int i, int line_count)
{
	if (params[0][0] == 's' && params[0][1] == 'p')
	{
		sphere_parser1(params, data, i, line_count);
		sphere_parser2(params, data->scene, i);
		if (params[4] && params[5])
			data->scene->spheres[i].texture = ft_atoi(params[5]);
		else
			data->scene->spheres[i].texture = 0;
		return (1);
	}
	return (0);
}
