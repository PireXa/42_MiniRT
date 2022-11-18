#include "../../inc/minirt.h"

int shading(t_sphere sphere, t_ray ray, float t, t_light light)
{
	t_vector hit_point;
	t_vector normal;
	t_vector light_dir;
	float intensity;

	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	normal = vector_from_points(sphere.center, hit_point);
	normalize_vector(&normal);
	light_dir = vector_from_points(hit_point, light.origin);
	normalize_vector(&light_dir);
	intensity = dot_product(normal, light_dir);
	if (intensity < 0)
		intensity = 0;
	return (intensity * 255);
}