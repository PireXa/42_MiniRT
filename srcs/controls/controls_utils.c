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

void	clean_slate(t_data *g)
{
	ft_bzero(g->img.addr, WIND_H * WIND_W * (g->img.bi_per_pxl / 8));
}

char	checkcode(char *line)
{
	if (ft_strncmp(line, "sp", 3) == 0)
		return ('1');
	else if (ft_strncmp(line, "pl", 3) == 0)
		return ('2');
	else if (ft_strncmp(line, "cy", 3) == 0)
		return ('3');
	else if (ft_strncmp(line, "l", 2) == 0)
		return ('4');
	else if (ft_strncmp(line, "c", 2) == 0)
		return ('5');
	else
		return ('-');
}

void	transform_cameras2(t_data *data, char code[3], int n)
{
	if (code[1] == '3')
	{
		if (code[2] == '1')
			data->scene->cameras[n].normal
				= rotater(data->scene->cameras[n].normal, 'x', 1);
		else if (code[2] == '2')
			data->scene->cameras[n].normal
				= rotater(data->scene->cameras[n].normal, 'y', 1);
		else if (code[2] == '3')
			data->scene->cameras[n].normal
				= rotater(data->scene->cameras[n].normal, 'z', 1);
		else if (code[2] == '4')
			data->scene->cameras[n].normal
				= rotater(data->scene->cameras[n].normal, 'x', -1);
		else if (code[2] == '5')
			data->scene->cameras[n].normal
				= rotater(data->scene->cameras[n].normal, 'y', -1);
		else if (code[2] == '6')
			data->scene->cameras[n].normal
				= rotater(data->scene->cameras[n].normal, 'z', -1);
		normalize_vector(&data->scene->cameras[n].normal);
		data->scene->cameras[n].view_matrix
			= set_cam_wrld_mtrx(
				data->scene->cameras[n], (t_vector){0, 1, 0});
	}
}

void	transform_cameras(t_data *data, char code[3], int n, float value)
{
	transform_cameras1(data, code, n, value);
	transform_cameras2(data, code, n);
}

void	transform(t_data *data, char code[3], int n, float value)
{
	if (code[0] == '1')
		transform_sphere(data, code, n, value);
	else if (code[0] == '2')
		transform_plane(data, code, n, value);
	else if (code[0] == '3')
		transform_cylinders(data, code, n, value);
	else if (code[0] == '4')
		transform_lights(data, code, n, value);
	else if (code[0] == '5')
		transform_cameras(data, code, n, value);
}
