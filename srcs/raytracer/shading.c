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

float get_light_dist(t_light light, t_vector hit_point)
{
	return (vector_length(vector_from_points(light.origin, hit_point)));
}

float light_intens_by_dist(t_light light, t_ray ray, float t)
{
	float intensity;
	t_vector hit_point;

	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	intensity = 800000 / (get_light_dist(light, hit_point) * get_light_dist(light, hit_point));
	if (intensity > 1)
		intensity = 1;
	return (intensity);
}

int check_shadow(t_data *data, t_ray ray, float t, t_light light)
{
	int		i;
	float	light_dist;
	float	intersect;
	t_ray	shadow_ray;

	i = -1;
	shadow_ray.origin = vector_add(ray.origin, vector_scale(ray.direction, t));
	shadow_ray.direction = vector_from_points(shadow_ray.origin, light.origin);
	normalize_vector(&shadow_ray.direction);
	light_dist = get_light_dist(light, shadow_ray.origin);
	while (++i < data->nb_objs->nb_spheres)
	{
		intersect = intersect_ray_sphere(shadow_ray, data->scene->spheres[i]);
		if (intersect > 0.0001 && intersect < light_dist)
			return (1);
	}
	return (0);
}

float phong_shading(t_vector normal, t_vector light_dir, t_vector view_dir)
{
	float	ambient;
	float	diffuse;
	float	specular;
	float	phong;
	t_vector	half_vector;

	ambient = 0.1;
	diffuse = 0.6 * fmax(0, dot_product(normal, light_dir));
	half_vector = vector_add(light_dir, view_dir);
	normalize_vector(&half_vector);
	specular = 0.3 * pow(fmax(0, dot_product(normal, half_vector)), 250);
	phong = ambient + diffuse + specular;
	return (phong);
}

int shading_sphere(t_sphere sphere, t_ray ray, float t, t_light light)
{
	t_vector hit_point;
	t_vector normal;
	t_vector light_dir;
	t_vector view_dir;

	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	normal = vector_from_points(sphere.center, hit_point);
	normalize_vector(&normal);
	light_dir = vector_from_points(hit_point, light.origin);
	normalize_vector(&light_dir);
	return (calc_color_intensity(sphere.color, light_intens_by_dist(light, ray, t) * phong_shading(normal, light_dir, view_dir)));
}