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

float light_intens_by_dist(t_light light, t_vector hit_point)
{
	float intensity;

	intensity = LUMENS / (get_light_dist(light, hit_point) * get_light_dist(light, hit_point));
	if (intensity > 1)
		intensity = 1;
	return (intensity);
}

int check_shadow(t_data *data, t_ray ray, t_vector hit_point, t_light light)
{
	float	light_dist;
	t_ray	shadow_ray;
	t_near_obj	hit;

	shadow_ray.origin = vector_add(hit_point, vector_scale(ray.direction, -0.001f));
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
	float	diffuse;
	float	specular;
	float	phong;
	t_vector	half_vector;

	diffuse = 0.3 * fmax(0, dot_product(normal, light_dir));
	half_vector = vector_add(light_dir, view_dir);
	normalize_vector(&half_vector);
	specular = 0.3 * pow(fmax(0, dot_product(normal, half_vector)), 50);
	phong = diffuse + specular;
	return (phong);
}

int shading_sphere(t_sphere sphere, t_ray ray, t_vector hit_point, t_data *data)
{
	t_vector normal;
	t_vector light_dir;
	t_vector view_dir;
	float intensity;
	int i;

	i = -1;
	intensity = 0;
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	normal = vector_from_points(sphere.center, hit_point);
	normalize_vector(&normal);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit_point, data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i], hit_point) * phong_shading(normal, light_dir, view_dir);
	}
	return (calc_color_intensity(sphere.color, intensity));
}

int shading_plane(t_plane plane, t_ray ray, t_vector hit_point, t_data *data)
{
	t_vector normal;
	t_vector light_dir;
	t_vector view_dir;
	float intensity;
	int i;

	i = -1;
	intensity = 0;
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	normal = plane.normal;
	normalize_vector(&normal);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit_point, data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i], hit_point) * phong_shading(normal, light_dir, view_dir);
	}
	if (intensity >= 1)
		intensity = 1;
	return (calc_color_intensity(plane.color, intensity));
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

int shading_cylinder(t_cylinder cylinder, t_ray ray, t_vector hit_point, t_data *data)
{
	t_vector normal;
	t_vector light_dir;
	t_vector view_dir;
	float intensity;
	int i;

	i = -1;
	intensity = 0;
	normal = normal_cylinder(cylinder, hit_point);
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit_point, data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i], hit_point) * phong_shading(normal, light_dir, view_dir);
	}
	return (calc_color_intensity(cylinder.color, intensity));
}

int	shading_cylinder_top(t_cylinder cylinder, t_ray ray, t_vector hit_point, t_data *data)
{
	t_vector light_dir;
	t_vector view_dir;
	t_vector normal;
	float intensity;
	int i;

	i = -1;
	intensity = 0;
	normal = cylinder.normal;
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit_point, data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i], hit_point) * phong_shading(normal, light_dir, view_dir);
	}
	return (calc_color_intensity(cylinder.color, intensity));
}

int	shading_cylinder_bottom(t_cylinder cylinder, t_ray ray, t_vector hit_point, t_data *data)
{
	t_vector light_dir;
	t_vector view_dir;
	t_vector normal;
	float intensity;
	int i;

	i = -1;
	intensity = 0;
	normal = vector_scale(cylinder.normal, -1);
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit_point, data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i], hit_point) * phong_shading(normal, light_dir, view_dir);
	}
	return (calc_color_intensity(cylinder.color, intensity));
}

t_vector	normal_triangle(t_triangle triangle)
{
	t_vector	normal;

	normal = cross_product(vector_from_points(triangle.p1, triangle.p2), vector_from_points(triangle.p1, triangle.p3));
	normalize_vector(&normal);
	return (normal);
}

int	shading_triangle(t_triangle triangle, t_ray ray, t_vector hit_point, t_data *data)
{
	t_vector normal;
	t_vector light_dir;
	t_vector view_dir;
	float intensity;
	int i;

	i = -1;
	intensity = 0;
	view_dir = vector_from_points(hit_point, ray.origin);
	normalize_vector(&view_dir);
	normal = normal_triangle(triangle);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit_point, data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i], hit_point) * phong_shading(normal, light_dir, view_dir);
	}
	if (intensity >= 1)
		intensity = 1;
	return (calc_color_intensity(triangle.color, intensity));
}
