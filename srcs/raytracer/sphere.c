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

float	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_2nd_equation eq;
	float		radius;

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
