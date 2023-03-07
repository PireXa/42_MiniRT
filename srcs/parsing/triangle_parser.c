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

void	triangle_parser1(char **params, t_data *data, int l, int lcnt)
{
	char	**sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d :"
				" triangle point 1 not valid\033[0m\n", lcnt));
	}
	data->scene->triangles[l].p1.x = ft_atof(sub_params[0]);
	data->scene->triangles[l].p1.y = ft_atof(sub_params[1]);
	data->scene->triangles[l].p1.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
	sub_params = ft_split(params[2], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d :"
				" triangle point 2 not valid\033[0m\n", lcnt));
	}
	data->scene->triangles[l].p2.x = ft_atof(sub_params[0]);
	data->scene->triangles[l].p2.y = ft_atof(sub_params[1]);
	data->scene->triangles[l].p2.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
}

void	triangle_parser2(char **params, t_data *data, int l, int lcnt)
{
	char	**sub_params;

	sub_params = ft_split(params[3], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d :"
				" triangle point 3 not valid\033[0m\n", lcnt));
	}
	data->scene->triangles[l].p3.x = ft_atof(sub_params[0]);
	data->scene->triangles[l].p3.y = ft_atof(sub_params[1]);
	data->scene->triangles[l].p3.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
	sub_params = ft_split(params[4], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d :"
				" triangle color not valid\033[0m\n", lcnt));
	}
	data->scene->triangles[l].color = rgb_to_int(ft_atoi(sub_params[0]),
			ft_atoi(sub_params[1]),
			ft_atoi(sub_params[2]));
	free_double_array(sub_params);
}

void	triangle_parser3(char **params, t_scene *s, int l)
{
	if (params[5])
	{
		s->triangles[l].light_absorb_ratio = get_material_data(params[5], 1);
		s->triangles[l].refraction_index = get_material_data(params[5], 2);
		s->triangles[l].light_absorb_distance = get_material_data(params[5], 3);
		s->triangles[l].ks = get_material_data(params[5], 4);
		s->triangles[l].kd = get_material_data(params[5], 5);
		s->triangles[l].roughness = get_material_data(params[5], 6);
	}
	else
	{
		s->triangles[l].light_absorb_ratio = 0.9f;
		s->triangles[l].refraction_index = 1.2f;
		s->triangles[l].light_absorb_distance = 1000.0f;
		s->triangles[l].ks = 0.4f;
		s->triangles[l].kd = 0.3f;
		s->triangles[l].roughness = 0.0f;
	}
}

int	triangle_parser(char **params, t_data *data, int l, int line_count)
{
	if (params[0][0] == 't' && params[0][1] == 'r')
	{
		triangle_parser1(params, data, l, line_count);
		triangle_parser2(params, data, l, line_count);
		triangle_parser3(params, data->scene, l);
		return (1);
	}
	return (0);
}
