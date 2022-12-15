#include "../../inc/minirt.h"

t_vector	vector_scale(t_vector v, float scale)
{
	t_vector result;

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

void	normalize_vector(t_vector *vector)
{
	float	magnitude;

	magnitude = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}

float	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vector_from_points(t_vector point1, t_vector point2)
{
	t_vector	vector;

	vector.x = point2.x - point1.x;
	vector.y = point2.y - point1.y;
	vector.z = point2.z - point1.z;
	return (vector);
}


//make function that returns true if the ray intersects the sphere
//if true, return the point of intersection
//if false, return nothing

float dot_product(t_vector vector1, t_vector vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

t_vector	point_at_parameter(t_ray ray, float t)
{
	t_vector	point;

	point.x = ray.origin.x + t * ray.direction.x;
	point.y = ray.origin.y + t * ray.direction.y;
	point.z = ray.origin.z + t * ray.direction.z;
	return (point);
}

t_vector	cross_product(t_vector vector1, t_vector vector2)
{
	t_vector	vector;

	vector.x = vector1.y * vector2.z - vector1.z * vector2.y;
	vector.y = vector1.z * vector2.x - vector1.x * vector2.z;
	vector.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (vector);
}