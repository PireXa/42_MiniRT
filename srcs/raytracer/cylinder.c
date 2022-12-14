#include "../../inc/minirt.h"

float	define_cylinder_height(t_cylinder  cylinder, t_ray ray, float t)
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

float intersect_ray_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	oc = vector_from_points(cylinder.base_center, ray.origin);
	a = dot_product(ray.direction, ray.direction) - pow(dot_product(ray.direction, cylinder.normal), 2);
	b = 2 * (dot_product(ray.direction, oc) - dot_product(ray.direction, cylinder.normal) * dot_product(oc, cylinder.normal));
	c = dot_product(oc, oc) - pow(dot_product(oc, cylinder.normal), 2) - pow(cylinder.diameter / 2, 2);
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

float	intersect_ray_cylinder_top(t_ray ray, t_cylinder cylinder)
{
	float t;
	float denom;
	t_vector p0l0;
	t_vector top;
	t_vector hit_point;

	top = vector_add(cylinder.base_center, vector_scale(cylinder.normal, cylinder.height));
	denom = dot_product(cylinder.normal, ray.direction);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, top);
		t = dot_product(p0l0, cylinder.normal) / denom;
		if (t > 0.0001f)
		{
			hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
			if (vector_length(vector_from_points(top, hit_point)) <= cylinder.diameter / 2)
				return (t);
		}
	}
	return (0);
}

float	intersect_ray_cylinder_bottom(t_ray ray, t_cylinder cylinder)
{
	float t;
	float denom;
	t_vector p0l0;
	t_vector bottom;
	t_vector hit_point;

	bottom = cylinder.base_center;
	denom = dot_product(cylinder.normal, ray.direction);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, bottom);
		t = dot_product(p0l0, cylinder.normal) / denom;
		if (t > 0.0001f)
		{
			hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
			if (vector_length(vector_from_points(bottom, hit_point)) <= cylinder.diameter / 2)
				return (t);
		}
	}
	return (0);
}