/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	intersect_ray_plane(t_ray ray, t_plane plane)
{
	float t;
	float denom;
	t_vector p0l0;
	denom = dot_product(plane.normal, ray.direction);
	if (fabsf(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, plane.point);
		t = dot_product(p0l0, plane.normal) / denom;
		if (t > 0.0001f)
			return (t);
	}
	return (0);
}