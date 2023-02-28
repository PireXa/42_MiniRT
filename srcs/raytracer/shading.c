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
	return (intensity + AMBIENT_LIGHT);
}

int check_shadow(t_data *data, t_ray ray, t_vector hit_point, t_light light)
{
	float	light_dist;
	t_ray	shadow_ray;
	t_hit_obj	hit;

	shadow_ray.origin = vector_add(hit_point, vector_scale(ray.direction, -0.001f));
//	shadow_ray.origin = vector_add(hit_point, vector_scale(hit.normal, 0.00001f));
	shadow_ray.direction = vector_from_points(shadow_ray.origin, light.origin);
	normalize_vector(&shadow_ray.direction);
	light_dist = get_light_dist(light, shadow_ray.origin);
	hit = get_closest_intersection(data, shadow_ray);
	if (hit.t_min > 0.0001f && hit.t_min < light_dist)
		return (1);
	return (0);
}

float phong_shading(t_hit_obj hit, t_vector light_dir, t_vector view_dir)
{
	float	diffuse;
	float	specular;
	float	phong;
	t_vector	half_vector;

	diffuse = hit.kd * (float)fmax(0, dot_product(hit.normal, light_dir));
	half_vector = vector_add(light_dir, view_dir);
	normalize_vector(&half_vector);
	specular = hit.ks * (float)pow(fmax(0, dot_product(hit.normal, half_vector)), 250);
	phong = diffuse + specular;
	return (phong);
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

t_vector	normal_triangle(t_triangle triangle)
{
	t_vector	normal;

	normal = cross_product(vector_from_points(triangle.p1, triangle.p2), vector_from_points(triangle.p1, triangle.p3));
	normalize_vector(&normal);
	return (normal);
}

int shading(t_hit_obj hit, t_ray ray, t_data *data)
{
	t_vector light_dir;
	t_vector view_dir;
	float	intensity;
	int i;

	i = -1;
	intensity = 0;
	view_dir = vector_from_points(hit.hit_point, ray.origin);
	normalize_vector(&view_dir);
	while (++i < data->nb_objs->nb_lights)
	{
		light_dir = vector_from_points(hit.hit_point, data->scene->lights[i].origin);
		normalize_vector(&light_dir);
		if (check_shadow(data, ray, hit.hit_point, data->scene->lights[i]) == 0)
			intensity += light_intens_by_dist(data->scene->lights[i], hit.hit_point) * phong_shading(hit, light_dir, view_dir);
	}
	intensity += AMBIENT_LIGHT;
	if (intensity >= 1)
		intensity = 1;
	return (calc_color_intensity(hit.color, intensity));
}
