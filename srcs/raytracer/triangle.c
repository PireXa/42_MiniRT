/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

typedef struct s_moller
{
	t_vector	edge1;
	t_vector	edge2;
	t_vector	pvec;
	t_vector	tvec;
	t_vector	qvec;
	t_vector	p0l0;
	float		denom;
	float		inv_det;
	float		u;
	float		v;
	float		t;
}				t_moller;

t_vector	normal_triangle(t_triangle triangle)
{
	t_vector	normal;

	normal = cross_product(vector_from_points(triangle.p1,
				triangle.p2), vector_from_points(triangle.p1, triangle.p3));
	normalize_vector(&normal);
	return (normal);
}

void	check_hit_triangles(t_data *data, t_ray ray, t_hit_obj *hit)
{
	int			i;
	float		t;

	i = -1;
	while (++i < data->nb_objs->nb_triangles)
	{
		t = intersect_ray_triangle(ray, data->scene->triangles[i]);
		if (t)
		{
			if (t < hit->t_min)
			{
				hit->t_min = t;
				hit->closest_triangle = i;
				hit->closest_sphere = -1;
				hit->closest_plane = -1;
				hit->closest_cylinder = -1;
			}
		}
	}
}

//Möller Trumbore Algorithm
float	intersect_ray_triangle(t_ray ray, t_triangle triangle)
{
	t_moller	moller;

	moller.edge1 = vector_from_points(triangle.p1, triangle.p2);
	moller.edge2 = vector_from_points(triangle.p1, triangle.p3);
	moller.pvec = cross_product(ray.direction, moller.edge2);
	moller.denom = dot_product(moller.edge1, moller.pvec);
	if (fabs(moller.denom) > 0.0001f)
	{
		moller.p0l0 = vector_from_points(triangle.p1, ray.origin);
		moller.tvec = cross_product(moller.p0l0, moller.edge1);
		moller.u = dot_product(moller.pvec, moller.p0l0) / moller.denom;
		moller.v = dot_product(moller.tvec, ray.direction) / moller.denom;
		moller.t = dot_product(moller.tvec, moller.edge2) / moller.denom;
		if (moller.t > 0.0001f && moller.u >= 0
			&& moller.v >= 0 && moller.u + moller.v <= 1)
			return (moller.t);
	}
	return (0);
}
