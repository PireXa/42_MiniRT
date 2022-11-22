#include "../../inc/minirt.h"

int	calc_color_intensity(int color, float intensity)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r *= intensity;
	g *= intensity;
	b *= intensity;
	return ((r << 16) | (g << 8) | b);
}

float light_intens_by_dist(t_light light, t_plane plane, t_ray ray, float t)
{
	float intensity;
	t_vector hit_point;

	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	intensity = dot_product(vector_from_points(light.origin, hit_point), plane.normal) / (vector_length(vector_from_points(light.origin, hit_point)) * vector_length(plane.normal));
	if (intensity < 0)
		intensity = 0;
	return (intensity);
}

int check_shadow(t_data *data, t_ray ray, float t, t_light light)
{
	int		i;
	t_ray	shadow_ray;

	i = -1;
	shadow_ray.origin = vector_add(ray.origin, vector_scale(ray.direction, t));
	shadow_ray.direction = vector_from_points(shadow_ray.origin, light.origin);
	normalize_vector(&shadow_ray.direction);
	while (++i < data->nb_objs->nb_spheres)
	{
		if (intersect_ray_sphere(shadow_ray, data->scene->spheres[i]))
			return (1);
	}
	return (0);
}

int shading_sphere(t_sphere sphere, t_ray ray, float t, t_light light)
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
	return (calc_color_intensity(sphere.color, intensity));
}