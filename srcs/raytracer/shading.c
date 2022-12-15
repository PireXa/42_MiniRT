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
	intensity = LUMENS / (get_light_dist(light, hit_point) * get_light_dist(light, hit_point));
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
	t_near_obj	hit;

	i = -1;
	shadow_ray.origin = vector_add(ray.origin, vector_scale(ray.direction, t - 0.001f));
	shadow_ray.direction = vector_from_points(shadow_ray.origin, light.origin);
	normalize_vector(&shadow_ray.direction);
	light_dist = get_light_dist(light, shadow_ray.origin);
	hit = get_closest_intersection(data, shadow_ray);
	if (hit.t_min > 0.0001 && hit.t_min < light_dist)
		return (1);
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
	specular = 0.3 * pow(fmax(0, dot_product(normal, half_vector)), 50);
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

t_vector normal_cylinder(t_cylinder cylinder, t_vector hit_point)
{
	float		m;
	t_vector	normal;
	t_vector	axis_point;

	m = dot_product(vector_from_points(cylinder.base_center, hit_point), cylinder.normal);
	axis_point = vector_add(cylinder.base_center, vector_scale(cylinder.normal, m));
	normal = vector_from_points(axis_point, hit_point);
	normalize_vector(&normal);
	return (normal);
}

int shading_cylinder(t_cylinder cylinder, t_ray ray, float t, t_light light)
{
	t_vector hit_point;
	t_vector normal;
	t_vector light_dir;
	t_vector view_dir;

	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	normal = normal_cylinder(cylinder, hit_point);
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	light_dir = vector_from_points(hit_point, light.origin);
	normalize_vector(&light_dir);
	return (calc_color_intensity(cylinder.color, light_intens_by_dist(light, ray, t) * phong_shading(normal, light_dir, view_dir)));

}

int	shading_cylinder_top(t_cylinder cylinder, t_ray ray, float t, t_light light)
{
	t_vector light_dir;
	t_vector view_dir;
	t_vector normal;
	t_vector hit_point;

	normal = cylinder.normal;
	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	light_dir = vector_from_points(hit_point, light.origin);
	normalize_vector(&light_dir);
	return(calc_color_intensity(cylinder.color, light_intens_by_dist(light, ray, t) * phong_shading(normal, light_dir, view_dir)));
}

int	shading_cylinder_bottom(t_cylinder cylinder, t_ray ray, float t, t_light light)
{
	t_vector light_dir;
	t_vector view_dir;
	t_vector normal;
	t_vector hit_point;

	normal = vector_scale(cylinder.normal, -1);
	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	light_dir = vector_from_points(hit_point, light.origin);
	normalize_vector(&light_dir);
	return(calc_color_intensity(cylinder.color, light_intens_by_dist(light, ray, t) * phong_shading(normal, light_dir, view_dir)));
}

t_vector	normal_triangle(t_triangle triangle)
{
	t_vector	normal;

	normal = cross_product(vector_from_points(triangle.p1, triangle.p2), vector_from_points(triangle.p1, triangle.p3));
	normalize_vector(&normal);
	return (normal);
}

int	shading_triangle(t_triangle triangle, t_ray ray, float t, t_light light)
{
	t_vector hit_point;
	t_vector normal;
	t_vector light_dir;
	t_vector view_dir;

	hit_point = vector_add(ray.origin, vector_scale(ray.direction, t));
	normal = normal_triangle(triangle);
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	light_dir = vector_from_points(hit_point, light.origin);
	normalize_vector(&light_dir);
	return (calc_color_intensity(triangle.color, light_intens_by_dist(light, ray, t) * phong_shading(normal, light_dir, view_dir)));
}