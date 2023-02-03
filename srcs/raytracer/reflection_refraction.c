#include "../../inc/minirt.h"

t_vector	calc_reflected_ray(t_vector ray, t_vector normal)
{
	t_vector	reflected_ray;

	reflected_ray = vector_sub(ray, vector_scale(normal, 2 * dot_product(ray, normal)));
	return (reflected_ray);
}

t_vector	calc_refracted_ray(t_vector ray, t_vector normal)
{
	float		n;
	float		c1;
	float		c2;
	t_vector	refracted_ray;

	n = 1 / MATERIAL_REFRACTION;
	c1 = dot_product(normal, ray);
	c2 = sqrt(1 - n * n * (1 - c1 * c1));
	refracted_ray = vector_add(vector_scale(ray, n), vector_scale(normal, n * c1 - c2));
	return (refracted_ray);
}

t_hit_obj get_reflected_color(t_data *data, t_ray reflect_ray, t_hit_obj hit, int *flag)
{
	t_hit_obj	reflect_hit;

	reflect_hit = get_closest_intersection(data, reflect_ray);
	if (reflect_hit.t_min < 4535320)
		reflect_hit.color = shading(reflect_hit, reflect_ray, data);
	else
	{
		*flag = 0;
		reflect_hit.color = hit.color;
	}
	return (reflect_hit);
}

t_hit_obj get_refracted_color(t_data *data, t_ray refract_ray, t_hit_obj hit, float *beer_lambert)
{
	t_hit_obj	refract_hit;

	refract_hit = get_closest_intersection(data, refract_ray);
	*beer_lambert = 1.0f - exp(-MATERIAL_TRANSPARENCY * refract_hit.t_min);
	refract_ray.origin = vector_add(hit.hit_point, vector_scale(refract_ray.direction, refract_hit.t_min + 0.001f));
	refract_hit = get_closest_intersection(data, refract_ray);
	if (refract_hit.t_min < 4535320)
		refract_hit.color = shading(refract_hit, refract_ray, data);
	else
		refract_hit.color = hit.color;
	return (refract_hit);
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
	if (ratio >= 1)
		ratio = 1;
	if (ratio <= 0)
		ratio = 0;
	int r = (int)((float)((color1 >> 16) & 0xFF) * ratio + (float)((color2 >> 16) & 0xFF) * (1 - ratio));
	int g = (int)((float)((color1 >> 8) & 0xFF) * ratio + (float)((color2 >> 8) & 0xFF) * (1 - ratio));
	int b = (int)((float)((color1) & 0xFF) * ratio + (float)((color2) & 0xFF) * (1 - ratio));
	return (r << 16 | g << 8 | b);
}

float	fresnel(t_vector incident_dir, t_vector normal, float material_light_reflection)
{
	float	r0 = pow((1.0f - MATERIAL_REFRACTION) / (1.0f + MATERIAL_REFRACTION), 2);
	float	cos_theta = -dot_product(normal, incident_dir);
	float 	x = 1.0f - cos_theta;
	float 	ret = r0 + (1.0f - r0) * pow(x, 5);
	ret = material_light_reflection + (1.0f - material_light_reflection) * ret;
	return (ret);
}

//fresnel = reflectance
//1 - fresnel = transmittance

t_hit_obj	reflection(t_data *data, t_ray ray, t_hit_obj hit, int depth, float light_intensity, float fresnel_ratio, t_ray reflected_ray, int *flag)
{
	t_hit_obj 	reflected_hit;

	reflected_hit = get_reflected_color(data, reflected_ray, hit, flag);
//	reflected_hit.color = blend_colors(hit.color, reflected_hit.color, 1.0f - fresnel_ratio);
	reflected_hit.color = blend_colors(reflected_hit.color, hit.color, fresnel_ratio);
	reflected_hit.color = blend_colors(reflected_hit.color, hit.color, light_intensity);
	return (reflected_hit);
}

t_hit_obj	refraction(t_data *data, t_ray ray, t_hit_obj hit, int depth, float light_intensity, float fresnel_ratio)
{
	t_ray refracted_ray;
	t_hit_obj refracted_hit;
	float beer_lambert;

	refracted_ray.direction = calc_refracted_ray(ray.direction, hit.normal);
	refracted_ray.origin = vector_add(hit.hit_point, vector_scale(refracted_ray.direction, 0.0001f));
	refracted_hit = get_refracted_color(data, refracted_ray, hit, &beer_lambert);
	refracted_hit.color = blend_colors(hit.color, refracted_hit.color, 1.0f - fresnel_ratio);
	refracted_hit.color = blend_colors(refracted_hit.color, hit.color, beer_lambert);
	refracted_hit.color = blend_colors(refracted_hit.color, hit.color, light_intensity);
	return (refracted_hit);
}

int reflection_refraction(t_data *data, t_ray ray, t_hit_obj hit, int depth, float light_intensity)
{
	t_ray		reflected_ray;
	t_hit_obj 	reflected_hit;
	t_ray		refracted_ray;
	t_hit_obj 	refracted_hit;
	float		fresnel_ratio;
	float 		beer_lambert;
	int			flag;

	flag = 1;
	fresnel_ratio = fresnel(ray.direction, hit.normal, 1.0f - hit.light_absorb_ratio);
	reflected_ray.direction = calc_reflected_ray(ray.direction, hit.normal);
//	vector_rand(&reflected_ray, 0.1f);
	normalize_vector(&reflected_ray.direction);
	reflected_ray.origin = vector_add(hit.hit_point, vector_scale(reflected_ray.direction, 0.0001f));
//	reflected_hit = get_reflected_color(data, reflected_ray, hit);
//	refracted_ray.direction = calc_refracted_ray(ray.direction, hit.normal);
//	refracted_ray.origin = vector_add(hit.hit_point, vector_scale(refracted_ray.direction, 0.0001f));
//	refracted_hit = get_refracted_color(data, refracted_ray, hit, &beer_lambert);
//	refracted_hit.color = blend_colors(hit.color, refracted_hit.color, fresnel_ratio);
//	refracted_hit.color = blend_colors(refracted_hit.color, hit.color, beer_lambert);
//	reflected_hit.color = refracted_hit.color;
//	reflected_hit.color = blend_colors(hit.color, reflected_hit.color, 1.0f - fresnel_ratio);
//	reflected_hit.color = blend_colors(reflected_hit.color, hit.color, light_intensity);

	reflected_hit = reflection(data, ray, hit, depth, light_intensity, fresnel_ratio, reflected_ray, &flag);
//	refracted_hit = refraction(data, ray, hit, depth, light_intensity, fresnel_ratio);
//	reflected_hit.color = blend_colors(reflected_hit.color, refracted_hit.color, fresnel_ratio);
	light_intensity = light_intensity - hit.light_absorb_ratio;
	if (depth > 1 && light_intensity > 0.01f && flag)
		return (reflection_refraction(data, reflected_ray, reflected_hit, depth - 1, light_intensity));
	return (reflected_hit.color);
}
