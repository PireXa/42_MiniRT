#include "../../inc/minirt.h"

t_vector	calc_reflected_ray(t_vector ray, t_vector normal)
{
	t_vector	reflected_ray;

	reflected_ray = vector_sub(ray, vector_scale(normal, 2 * dot_product(ray, normal)));
	return (reflected_ray);
}

int get_reflected_color(t_data *data, t_ray reflect_ray, t_hit_obj hit)
{
	t_hit_obj	reflect_hit;
	int			color;

	reflect_hit = get_closest_intersection(data, reflect_ray);
	if (reflect_hit.t_min < 4535320)
		color = shading(reflect_hit, reflect_ray, data);
	else
		color = hit.color;
	return (color);
}

float get_random_number(float min, float max)
{
	float random = (float)rand() / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return (min + r);
}

void	vector_rand(t_vector *reflect_dir, float randomness)
{
	reflect_dir->x += get_random_number(0, randomness);
	reflect_dir->y += get_random_number(0, randomness);
	reflect_dir->z += get_random_number(0, randomness);
}

int blend_colors(int color1, int color2, float ratio)
{
	int r = (int)((float)((color1 >> 16) & 0xFF) * ratio + (float)((color2 >> 16) & 0xFF) * (1 - ratio));
	int g = (int)((float)((color1 >> 8) & 0xFF) * ratio + (float)((color2 >> 8) & 0xFF) * (1 - ratio));
	int b = (int)((float)((color1) & 0xFF) * ratio + (float)((color2) & 0xFF) * (1 - ratio));
	return (r << 16 | g << 8 | b);
}

int reflection_refraction(t_data *data, t_ray ray, t_hit_obj hit)
{
	t_vector	normal;
	t_ray		reflected_ray;
	int			reflected_color;
	int 		blended_color;

	reflected_ray.direction = calc_reflected_ray(ray.direction, hit.normal);
//	vector_rand(&reflected_ray, 0.1f);
	normalize_vector(&reflected_ray.direction);
	reflected_ray.origin = hit.hit_point;
	reflected_color = get_reflected_color(data, reflected_ray, hit);
	blended_color = blend_colors(hit.color, reflected_color, 0.6f);
	return (blended_color);
}