/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	phong_shading(t_hit_obj hit, t_vector light_dir, t_vector view_dir)
{
	float		diffuse;
	float		specular;
	float		phong;
	t_vector	half_vector;

	diffuse = hit.kd * (float)fmax(0, dot_product(hit.normal, light_dir));
	half_vector = vector_add(light_dir, view_dir);
	normalize_vector(&half_vector);
	specular = hit.ks * (float)pow(fmax(0,
				dot_product(hit.normal, half_vector)), 250);
	phong = diffuse + specular;
	return (phong);
}

int	shading(t_hit_obj hit, t_ray ray, t_data *data)
{
	int			i;
	float		intensity;
	t_vector	light_dir;
	t_vector	view_dir;

	i = -1;
	intensity = 0;
	view_dir = vector_from_points(hit.hit_point, ray.origin);
	normalize_vector(&view_dir);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit.hit_point,
				data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit.hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i],
					hit.hit_point) * phong_shading(hit, light_dir, view_dir)
				* data->scene->lights[i].intensity;
	}
	intensity += data->scene->amb_light->intensity;
	if (intensity >= 1)
		intensity = 1;
	return (calc_color_intensity(hit.color, intensity));
}
