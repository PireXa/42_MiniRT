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

void	cylinder_parser1(char **params, t_data *data, int k, int line_count)
{
	char		**sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d : "
				"cylinder base center not valid\033[0m\n", line_count));
	}
	data->scene->cylinders[k].base_center.x = ft_atof(sub_params[0]);
	data->scene->cylinders[k].base_center.y = ft_atof(sub_params[1]);
	data->scene->cylinders[k].base_center.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
}

void	cylinder_parser2(char **params, t_data *data, int k, int line_count)
{
	char		**sub_params;
	t_vector	v1;

	sub_params = ft_split(params[2], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d : "
				"cylinder axis not valid\033[0m\n", line_count));
	}
	v1.x = ft_atof(sub_params[0]);
	v1.y = ft_atof(sub_params[1]);
	v1.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
	normalize_vector(&v1);
	data->scene->cylinders[k].normal = v1;
	data->scene->cylinders[k].diameter = ft_atof(params[3]);
	data->scene->cylinders[k].height = ft_atof(params[4]);
}

void	cylinder_parser3(char **params, t_scene *scene, int k)
{
	if (params[6])
	{
		scene->cylinders[k].light_absorb_ratio = get_material_data(
				params[6], 1);
		scene->cylinders[k].refraction_index = get_material_data(params[6], 2);
		scene->cylinders[k].light_absorb_distance = get_material_data(
				params[6], 3);
		scene->cylinders[k].ks = get_material_data(params[6], 4);
		scene->cylinders[k].kd = get_material_data(params[6], 5);
		scene->cylinders[k].roughness = get_material_data(params[6], 6);
	}
	else
	{
		scene->cylinders[k].light_absorb_ratio = 1;
		scene->cylinders[k].refraction_index = 1.2f;
		scene->cylinders[k].light_absorb_distance = 100.0f;
		scene->cylinders[k].ks = 0.4f;
		scene->cylinders[k].kd = 0.3f;
		scene->cylinders[k].roughness = 0.0f;
	}
}

int	cylinder_parser(char **params, t_data *data, int k, int line_count)
{
	char	**sub_params;

	if (params[0][0] == 'c' && params[0][1] == 'y')
	{
		cylinder_parser1(params, data, k, line_count);
		cylinder_parser2(params, data, k, line_count);
		sub_params = ft_split(params[5], ',');
		if (double_array_len(sub_params) != 3)
			exit(printf("\033[31mError\nLine %d : cylinder color "
					"not valid\033[0m\n", line_count));
		data->scene->cylinders[k].color = rgb_to_int(ft_atoi(sub_params[0]),
				ft_atoi(sub_params[1]),
				ft_atoi(sub_params[2]));
		free_double_array(sub_params);
		cylinder_parser3(params, data->scene, k);
		return (1);
	}
	return (0);
}
