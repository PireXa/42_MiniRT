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

void	camera_parser1(char **params, t_data *data, int m, int lcnt)
{
	char	**sub_params;

	sub_params = ft_split(params[1], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d :"
				" camera origin not valid\033[0m\n", lcnt));
	}
	data->scene->cameras[m].origin.x = ft_atof(sub_params[0]);
	data->scene->cameras[m].origin.y = ft_atof(sub_params[1]);
	data->scene->cameras[m].origin.z = ft_atof(sub_params[2]);
	free_double_array(sub_params);
}

void	camera_parser2(char **params, t_data *data, int m, int lcnt)
{
	char	**sub_params;

	sub_params = ft_split(params[2], ',');
	if (double_array_len(sub_params) != 3)
	{
		free_double_array(sub_params);
		free_all(data, printf("\033[31mError\nLine %d :"
				" camera normal not valid\033[0m\n", lcnt));
	}
	data->scene->cameras[m].normal.x = ft_atof(sub_params[0]);
	data->scene->cameras[m].normal.y = ft_atof(sub_params[1]);
	data->scene->cameras[m].normal.z = ft_atof(sub_params[2]);
	normalize_vector(&(data->scene)->cameras[m].normal);
	free_double_array(sub_params);
}

int	camera_parser(char **params, t_data *data, int m, int lcnt)
{
	if (params[0][0] == 'C' && !params[0][1])
	{
		camera_parser1(params, data, m, lcnt);
		camera_parser2(params, data, m, lcnt);
		if (!params[3] || ft_atof(params[3]) < 0 || ft_atof(params[3]) > 180)
		{
			free_all(data, printf("\033[31mError\nLine %d :"
					" camera fov not valid\033[0m\n", lcnt));
		}
		data->scene->cameras[m].fov = ft_atof(params[3]);
		data->scene->cameras[m].view_matrix
			= set_cam_wrld_mtrx(data->scene->cameras[m],
				(t_vector){0, 1, 0});
		return (1);
	}
	return (0);
}
