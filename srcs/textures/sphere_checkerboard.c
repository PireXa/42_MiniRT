/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	checkerboard_sphere(t_vector hit_point, t_sphere sphere)
{
	t_vector	hit_point_local;
	float		u;
	float		v;
	float		r;
	float		period;

	hit_point_local = vector_from_points(sphere.center, hit_point);
	period = 10.0f;
	r = sphere.diameter / 2;
	u = atan2(hit_point_local.z, hit_point_local.x) / (2 * M_PI) + 0.5;
	v = acos(hit_point_local.y / r) / M_PI;
	if ((int)(u * period) % 2 == (int)(v * period) % 2)
		return (1);
	return (0);
}
