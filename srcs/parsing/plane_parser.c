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

void	plane_parser1(char **params, t_data *data, int j, int line_count)
{
	char	**sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d : plane point "
				"coordinates not valid\n", line_count));
	}
	data->scene->planes[j].point.x = ft_atof(sub_params[0]);
	data->scene->planes[j].point.y = ft_atof(sub_params[1]);
	data->scene->planes[j].point.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
	sub_params = ft_split(params[2], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d : plane normal "
				"not valid\n", line_count));
	}
	data->scene->planes[j].normal.x = ft_atof(sub_params[0]);
	data->scene->planes[j].normal.y = ft_atof(sub_params[1]);
	data->scene->planes[j].normal.z = ft_atof(sub_params[2]);
	normalize_vector(&(data->scene)->planes[j].normal);
	free_double_array(sub_params);
}

void	plane_parser2(char **params, t_scene *s, int j)
{
	if (params[4])
	{
		s->planes[j].light_absorb_ratio = get_material_data(params[4], 1);
		s->planes[j].refraction_index = get_material_data(params[4], 2);
		s->planes[j].light_absorb_distance = get_material_data(params[4], 3);
		s->planes[j].ks = get_material_data(params[4], 4);
		s->planes[j].kd = get_material_data(params[4], 5);
		s->planes[j].roughness = get_material_data(params[4], 6);
	}
	else
	{
		s->planes[j].light_absorb_ratio = 0.3f;
		s->planes[j].refraction_index = 1.2f;
		s->planes[j].light_absorb_distance = 200.0f;
		s->planes[j].ks = 0.4f;
		s->planes[j].kd = 0.3f;
		s->planes[j].roughness = 0.0f;
	}
	if (params[4] && params[5])
		s->planes[j].texture = ft_atoi(params[5]);
	else
		s->planes[j].texture = 0;
}

int	plane_parser(char **params, t_data *data, int j, int lcnt)
{
	char	**sub_params;

	if (params[0][0] == 'p' && params[0][1] == 'l')
	{
		plane_parser1(params, data, j, lcnt);
		sub_params = ft_split(params[3], ',');
		if (double_array_len(sub_params) != 3)
		{
			free_double_array(sub_params);
			free_all(data, printf("Error\nLine %d : plane "
					"color not valid\n", lcnt));
		}
		data->scene->planes[j].color = rgb_to_int(ft_atoi(sub_params[0]),
				ft_atoi(sub_params[1]),
				ft_atoi(sub_params[2]));
		free_double_array(sub_params);
		plane_parser2(params, data->scene, j);
		return (1);
	}
	return (0);
}
