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

t_vector	rotater(t_vector v, char e, float sign)
{
	t_vector	r;
	float		ang;

	ang = 0.5f;
	r = (t_vector){0, 0, 0};
	if (e == 'x')
	{
		r.x = v.x;
		r.y = v.y * cos(ang * sign) - v.z * sin(ang * sign);
		r.z = v.y * sin(ang * sign) + v.z * cos(ang * sign);
	}
	else if (e == 'y')
	{
		r.x = v.x * cos(ang * sign) + v.z * sin(ang * sign);
		r.y = v.y;
		r.z = -v.x * sin(ang * sign) + v.z * cos(ang * sign);
	}
	else if (e == 'z')
	{
		r.x = v.x * cos(ang * sign) - v.y * sin(ang * sign);
		r.y = v.x * sin(ang * sign) + v.y * cos(ang * sign);
		r.z = v.z;
	}
	return (r);
}

void	transform_cylinders1(t_data *data, char code[3], int n, float value)
{
	if (code[1] == '1')
	{
		if (code[2] == '1')
			data->scene->cylinders[n].diameter += value;
		else if (code[2] == '2' && data->scene->cylinders[n].diameter > 0)
			data->scene->cylinders[n].diameter -= value;
	}
	else if (code[1] == '2')
	{
		if (code[2] == '1')
			data->scene->cylinders[n].base_center.x += value;
		else if (code[2] == '2')
			data->scene->cylinders[n].base_center.x -= value;
		else if (code[2] == '3')
			data->scene->cylinders[n].base_center.z += value;
		else if (code[2] == '4')
			data->scene->cylinders[n].base_center.z -= value;
		else if (code[2] == '5')
			data->scene->cylinders[n].base_center.y += value;
		else if (code[2] == '6')
			data->scene->cylinders[n].base_center.y -= value;
	}
}

void	transform_cylinders2(t_data *data, char code[3], int n)
{
	if (code[1] == '3')
	{
		if (code[2] == '1')
			data->scene->cylinders[n].normal
				= rotater(data->scene->cylinders[n].normal, 'x', 1);
		else if (code[2] == '2')
			data->scene->cylinders[n].normal
				= rotater(data->scene->cylinders[n].normal, 'y', 1);
		else if (code[2] == '3')
			data->scene->cylinders[n].normal
				= rotater(data->scene->cylinders[n].normal, 'z', 1);
		else if (code[2] == '4')
			data->scene->cylinders[n].normal
				= rotater(data->scene->cylinders[n].normal, 'x', -1);
		else if (code[2] == '5')
			data->scene->cylinders[n].normal
				= rotater(data->scene->cylinders[n].normal, 'y', -1);
		else if (code[2] == '6')
			data->scene->cylinders[n].normal
				= rotater(data->scene->cylinders[n].normal, 'z', -1);
		normalize_vector(&data->scene->cylinders[n].normal);
	}
}

void	transform_cylinders(t_data *data, char code[3], int n, float value)
{
	transform_cylinders1(data, code, n, value);
	transform_cylinders2(data, code, n);
	if (code[1] == '4')
	{
		if (code[2] == '1')
			data->scene->cylinders[n].height += value;
		else if (code[2] == '2' && data->scene->cylinders[n].height > 0)
			data->scene->cylinders[n].height -= value;
	}
}

void	transform_cameras1(t_data *data, char code[3], int n, float value)
{
	if (code[1] == '2')
	{
		if (code[2] == '1')
			data->scene->cameras[n].origin.x += value;
		else if (code[2] == '2')
			data->scene->cameras[n].origin.x -= value;
		else if (code[2] == '3')
			data->scene->cameras[n].origin.z += value;
		else if (code[2] == '4')
			data->scene->cameras[n].origin.z -= value;
		else if (code[2] == '5')
			data->scene->cameras[n].origin.y += value;
		else if (code[2] == '6')
			data->scene->cameras[n].origin.y -= value;
	}
	else if (code[1] == '4')
	{
		if (code[2] == '1' && data->scene->cameras[n].fov < 170.0f)
			data->scene->cameras[n].fov += 10;
		else if (code[2] == '2' && data->scene->cameras[n].fov > 10.0f)
			data->scene->cameras[n].fov -= 10;
	}
}
