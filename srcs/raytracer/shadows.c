/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	get_light_dist(t_light light, t_vector hit_point)
{
	return (vector_length(vector_from_points(light.origin, hit_point)));
}

float	light_intens_by_dist(t_light light, t_vector hit_point)
{
	float	intensity;

	intensity = LUMENS / (get_light_dist(light, hit_point)
			* get_light_dist(light, hit_point));
	if (intensity > 1)
		intensity = 1;
	return (intensity);
}

int	check_shadow(t_data *data, t_ray ray, t_vector hit_point, t_light light)
{
	float		light_dist;
	t_ray		shadow_ray;
	t_hit_obj	hit;

	shadow_ray.origin = vector_add(hit_point,
			vector_scale(ray.direction, -0.001f));
	shadow_ray.direction = vector_from_points(shadow_ray.origin, light.origin);
	normalize_vector(&shadow_ray.direction);
	light_dist = get_light_dist(light, shadow_ray.origin);
	hit = get_closest_intersection(data, shadow_ray);
	if (hit.t_min > 0.0001f && hit.t_min < light_dist)
		return (1);
	return (0);
}
