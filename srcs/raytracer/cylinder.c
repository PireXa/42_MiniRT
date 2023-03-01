/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	define_cylinder_height(t_cylinder cylinder, t_ray ray, float t)
{
	float		height;
	t_vector	hit_axis_proj;
	t_vector	hit_point;
	t_vector	aux;

	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	aux = vector_from_points(cylinder.base_center, hit_point);
	height = dot_product(aux, cylinder.normal);
	if (height < 0)
		return (0);
	hit_axis_proj = vector_scale(cylinder.normal, height);
	if (vector_length(hit_axis_proj) > cylinder.height)
		return (0);
	return (t);
}

float	intersect_ray_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_2nd_equation	eq;

	eq.oc = vector_from_points(cylinder.base_center, ray.origin);
	eq.a = dot_product(ray.direction, ray.direction)
		- pow(dot_product(ray.direction, cylinder.normal), 2);
	eq.b = 2 * (dot_product(ray.direction, eq.oc)
			- dot_product(ray.direction, cylinder.normal)
			* dot_product(eq.oc, cylinder.normal));
	eq.c = dot_product(eq.oc, eq.oc)
		- pow(dot_product(eq.oc, cylinder.normal), 2)
		- pow(cylinder.diameter / 2, 2);
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

float	intersect_ray_cylinder_top(t_ray ray, t_cylinder cylinder)
{
	float		t;
	float		denom;
	t_vector	p0l0;
	t_vector	top;
	t_vector	hit_point;

	top = vector_add(cylinder.base_center,
			vector_scale(cylinder.normal, cylinder.height));
	denom = dot_product(cylinder.normal, ray.direction);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, top);
		t = dot_product(p0l0, cylinder.normal) / denom;
		if (t > 0.0001f)
		{
			hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
			if (vector_length(vector_from_points(top, hit_point))
				<= cylinder.diameter / 2)
				return (t);
		}
	}
	return (0);
}

float	intersect_ray_cylinder_bottom(t_ray ray, t_cylinder cylinder)
{
	float		t;
	float		denom;
	t_vector	p0l0;
	t_vector	bottom;
	t_vector	hit_point;

	bottom = cylinder.base_center;
	denom = dot_product(cylinder.normal, ray.direction);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, bottom);
		t = dot_product(p0l0, cylinder.normal) / denom;
		if (t > 0.0001f)
		{
			hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
			if (vector_length(vector_from_points(bottom, hit_point))
				<= cylinder.diameter / 2)
				return (t);
		}
	}
	return (0);
}
