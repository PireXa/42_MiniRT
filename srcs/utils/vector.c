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

t_vector	vector_scale(t_vector v, float scale)
{
	t_vector	result;

	result.x = v.x * scale;
	result.y = v.y * scale;
	result.z = v.z * scale;
	return (result);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

void	normalize_vector(t_vector *v)
{
	float	magnitude;

	magnitude = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= magnitude;
	v->y /= magnitude;
	v->z /= magnitude;
}

float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
