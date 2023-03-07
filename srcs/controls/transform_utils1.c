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

void	transform_sphere(t_data *data, char code[3], int n, float value)
{
	if (code[1] == '1')
	{
		if (code[2] == '1')
			data->scene->spheres[n].diameter += value;
		else if (code[2] == '2' && data->scene->spheres[n].diameter > 1)
			data->scene->spheres[n].diameter -= value;
	}
	else if (code[1] == '2')
	{
		if (code[2] == '1')
			data->scene->spheres[n].center.x += value;
		else if (code[2] == '2')
			data->scene->spheres[n].center.x -= value;
		else if (code[2] == '3')
			data->scene->spheres[n].center.z += value;
		else if (code[2] == '4')
			data->scene->spheres[n].center.z -= value;
		else if (code[2] == '5')
			data->scene->spheres[n].center.y += value;
		else if (code[2] == '6')
			data->scene->spheres[n].center.y -= value;
	}
	re_render(data);
}

void	transform_plane1(t_data *data, char code[3], int n, float value)
{
	if (code[2] == '1')
		data->scene->planes[n].point.x += value;
	else if (code[2] == '2')
		data->scene->planes[n].point.x -= value;
	else if (code[2] == '3')
		data->scene->planes[n].point.z += value;
	else if (code[2] == '4')
		data->scene->planes[n].point.z -= value;
	else if (code[2] == '5')
		data->scene->planes[n].point.y += value;
	else if (code[2] == '6')
		data->scene->planes[n].point.y -= value;
}

void	transform_plane2(t_data *data, char code[3], int n)
{
	if (code[2] == '1')
		data->scene->planes[n].normal
			= rotater(data->scene->planes[n].normal, 'x', 1);
	else if (code[2] == '2')
		data->scene->planes[n].normal
			= rotater(data->scene->planes[n].normal, 'y', 1);
	else if (code[2] == '3')
		data->scene->planes[n].normal
			= rotater(data->scene->planes[n].normal, 'z', 1);
	else if (code[2] == '4')
		data->scene->planes[n].normal
			= rotater(data->scene->planes[n].normal, 'x', -1);
	else if (code[2] == '5')
		data->scene->planes[n].normal
			= rotater(data->scene->planes[n].normal, 'y', -1);
	else if (code[2] == '6')
		data->scene->planes[n].normal
			= rotater(data->scene->planes[n].normal, 'z', -1);
	normalize_vector(&data->scene->planes[n].normal);
}

void	transform_plane(t_data *data, char code[3], int n, float valute)
{
	if (code[1] == '2')
		transform_plane1(data, code, n, valute);
	else if (code[1] == '3')
		transform_plane2(data, code, n);
	re_render(data);
}

void	transform_lights(t_data *data, char code[3], int n, float value)
{
	if (code[1] == '1')
	{
		if (code[2] == '1')
			data->scene->lights[n].intensity += value;
		else if (code[2] == '2' && data->scene->lights[n].intensity > 0)
			data->scene->lights[n].intensity -= value;
	}
	else if (code[1] == '2')
	{
		if (code[2] == '1')
			data->scene->lights[n].origin.x += value;
		else if (code[2] == '2')
			data->scene->lights[n].origin.x -= value;
		else if (code[2] == '3')
			data->scene->lights[n].origin.z += value;
		else if (code[2] == '4')
			data->scene->lights[n].origin.z -= value;
		else if (code[2] == '5')
			data->scene->lights[n].origin.y += value;
		else if (code[2] == '6')
			data->scene->lights[n].origin.y -= value;
	}
	re_render(data);
}
