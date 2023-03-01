/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	intersect_ray_triangle(t_ray ray, t_triangle triangle) //Möller Trumbore Algorithm
{
	float t;
	float denom;
	t_vector p0l0;
	t_vector edge1;
	t_vector edge2;
	t_vector pvec;
	t_vector qvec;
	t_vector tvec;
	float u;
	float v;
	edge1 = vector_from_points(triangle.p1, triangle.p2);
	edge2 = vector_from_points(triangle.p1, triangle.p3);
	pvec = cross_product(ray.direction, edge2);
	denom = dot_product(edge1, pvec);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(triangle.p1, ray.origin);
		tvec = cross_product(p0l0, edge1);
		u = dot_product(pvec, p0l0) / denom;
		v = dot_product(tvec, ray.direction) / denom;
		t = dot_product(tvec, edge2) / denom;
		if (t > 0.0001f && u >= 0 && v >= 0 && u + v <= 1)
			return (t);
	}
	return (0);
}
