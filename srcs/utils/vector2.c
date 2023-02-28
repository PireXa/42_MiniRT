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

t_vector	vector_from_points(t_vector point1, t_vector point2)
{
	t_vector	vector;

	vector.x = point2.x - point1.x;
	vector.y = point2.y - point1.y;
	vector.z = point2.z - point1.z;
	return (vector);
}

float	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross_product(t_vector vector1, t_vector vector2)
{
	t_vector	vector;

	vector.x = vector1.y * vector2.z - vector1.z * vector2.y;
	vector.y = vector1.z * vector2.x - vector1.x * vector2.z;
	vector.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (vector);
}

float	get_random_number(float min, float max)
{
	float	random;
	float	diff;
	float	r;
	float	signed_random;

	random = (float)rand() / (float)RAND_MAX;
	diff = max - min;
	r = random * diff;
	signed_random = (float)rand() / (float)RAND_MAX;
	if (signed_random < 0.5)
		return (min - r);
	else
		return (min + r);
}

void	vector_rand(t_vector *vector, float randomness)
{
	if (randomness > 0)
	{
		vector->x += get_random_number(0, randomness);
		vector->y += get_random_number(0, randomness);
		vector->z += get_random_number(0, randomness);
	}
}
