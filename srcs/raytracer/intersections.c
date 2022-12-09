
#include "../../inc/minirt.h"

float	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_vector oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	oc = vector_from_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	return (0);
}

float intersect_ray_plane(t_ray ray, t_plane plane)
{
	float t;
	float denom;
	t_vector p0l0;

	denom = dot_product(plane.normal, ray.direction);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, plane.point);
		t = dot_product(p0l0, plane.normal) / denom;
		if (t > 0.0001f)
			return (t);
	}
	return (0);
}

float intersect_ray_cylinder(t_ray ray, t_cylinder cylinder)
{
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	a = pow(ray.direction.x, 2) + pow(ray.direction.y, 2);
	b = 2 * (ray.direction.x * (ray.origin.x - cylinder.center.x) + ray.direction.y * (ray.origin.y - cylinder.center.y));
	c = pow(ray.origin.x - cylinder.center.x, 2) + pow(ray.origin.y - cylinder.center.y, 2) - pow(cylinder.diameter / 2, 2) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	return (0);
}
