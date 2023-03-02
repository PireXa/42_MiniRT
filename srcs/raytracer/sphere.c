/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	check_hit_spheres(t_data *data, t_ray ray, t_hit_obj *hit)
{
	int			i;
	float		t;

	i = -1;
	while (++i < data->nb_objs->nb_spheres)
	{
		t = intersect_ray_sphere(ray, data->scene->spheres[i]);
		if (t)
		{
			if (t < hit->t_min)
			{
				hit->t_min = t;
				hit->closest_sphere = i;
			}
		}
	}
}

float	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	float			radius;
	t_2nd_equation	eq;

	radius = sphere.diameter / 2;
	eq.oc = vector_from_points(sphere.center, ray.origin);
	eq.a = dot_product(ray.direction, ray.direction);
	eq.b = 2.0 * dot_product(eq.oc, ray.direction);
	eq.c = dot_product(eq.oc, eq.oc) - radius * radius;
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (0);
	eq.t = (-eq.b - sqrt(eq.discriminant)) / (2.0 * eq.a);
	if (eq.t > 0.0001f)
		return (eq.t);
	eq.t = (-eq.b + sqrt(eq.discriminant)) / (2.0 * eq.a);
	if (eq.t > 0.0001f)
		return (eq.t);
	return (0);
}
