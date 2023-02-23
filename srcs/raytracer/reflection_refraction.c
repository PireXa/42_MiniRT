#include "../../inc/minirt.h"

t_vector	calc_reflected_ray(t_vector ray, t_vector normal)
{
	t_vector	reflected_ray;

	reflected_ray = vector_sub(ray, vector_scale(normal, 2 * dot_product(ray, normal)));
	return (reflected_ray);
}

t_vector	calc_refracted_ray(float n1, float n2, t_vector ray, t_vector normal)
{
	float		n;
	float		c1;
	float		c2;
	t_vector	refracted_ray;

	n = n1 / n2;
	c1 = dot_product(normal, ray);
	c2 = (float)sqrt(1 - n * n * (1 - c1 * c1));
	refracted_ray = vector_add(vector_scale(ray, n), vector_scale(normal, n * c1 - c2));
	return (refracted_ray);
}

t_vector	calc_refracted_ray2(float n1, float n2, t_vector ray, t_vector normal)
{
	float	n;
	float	c1;
	float 	sqrt_term;
	t_vector v1;
	t_vector v2;
	t_vector refracted_ray;

	n = n1 / n2;
	c1 = dot_product(normal, ray);
	v1 = vector_scale(normal, c1);
	v1 = vector_add(ray, v1);
	v1 = vector_scale(v1, n); //finished v1

	sqrt_term = 1 - n * n * (1 - c1 * c1);
	v2 = vector_scale(normal, sqrtf(sqrt_term));
	refracted_ray = vector_sub(v1, v2);
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

t_hit_obj get_refracted_color(t_data *data, t_ray inc_ray, t_ray refract_ray, t_hit_obj hit, float *beer_lambert, float n1)
{
	t_hit_obj	refract_hit;

	refract_hit = get_closest_intersection(data, refract_ray);
	if (refract_hit.t_min == 4535320)
	{
		refract_hit.color = hit.color;
		return (refract_hit);
	}
	if (refract_hit.t_min < 0.001f)
	{
		refract_ray.origin = vector_add(hit.hit_point, vector_scale(refract_ray.direction, refract_hit.t_min + 0.01f));
		refract_hit = get_closest_intersection(data, refract_ray);
	}
//	*beer_lambert = 1.0f - exp(-MATERIAL_TRANSPARENCY * refract_hit.t_min);
	*beer_lambert = 1.0f - exp(-hit.light_absorb_distance * refract_hit.t_min);
//	printf("beer_lambert = %f\n", *beer_lambert);
	refract_ray.origin = vector_add(hit.hit_point, vector_scale(refract_ray.direction, refract_hit.t_min + 0.001f));
	refract_ray.direction = calc_refracted_ray(hit.refraction_index, n1, refract_ray.direction, vector_scale(hit.normal, -1));
//	refract_ray.direction = calc_refracted_ray(n1, hit.refraction_index, refract_ray.direction, vector_scale(hit.normal, -1));
//	refract_ray.direction = inc_ray.direction;
	normalize_vector(&refract_ray.direction);
	refract_hit = get_closest_intersection(data, refract_ray);
	if (refract_hit.t_min < 4535321)
	{
//		refract_hit.color = refract_hit.color;
		refract_hit.color = shading(refract_hit, refract_ray, data);
	}
	else
		refract_hit.color = hit.color;
	return (refract_hit);
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

float	fresnel(float n1, float n2, t_vector incident_dir, t_vector normal, float material_light_reflection)
{
	float	r0 = pow((n1 - n2) / (n1 + n2), 2);
	float	cos_theta = -dot_product(normal, incident_dir);
	if (n1 > n2)
	{
		float n = n1 / n2;
		float sin_theta = n * n * (1 - cos_theta * cos_theta);
		if (sin_theta > 1)
			return (1.0f);
		cos_theta = sqrt(1 - sin_theta);
	}
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
	reflected_hit.color = blend_colors(reflected_hit.color, hit.color, light_intensity);
	return (reflected_hit);
}

t_hit_obj	refraction(t_data *data, t_ray ray, t_hit_obj hit, int depth, float light_intensity, float fresnel_ratio, float ref_index)
{
	t_ray refracted_ray;
	t_hit_obj refracted_hit;
	float beer_lambert;

	refracted_ray.direction = calc_refracted_ray(ref_index, hit.refraction_index, ray.direction, hit.normal);
	normalize_vector(&refracted_ray.direction);
	refracted_ray.origin = vector_add(hit.hit_point, vector_scale(refracted_ray.direction, 0.0001f));
	refracted_hit = get_refracted_color(data, ray, refracted_ray, hit, &beer_lambert, ref_index);
	refracted_hit.color = blend_colors(hit.color, refracted_hit.color, beer_lambert);
	refracted_hit.color = blend_colors(refracted_hit.color, hit.color, light_intensity);
	return (refracted_hit);
}

int reflection_refraction(t_data *data, t_ray ray, t_hit_obj hit, int depth, float light_intensity, float ref_index)
{
	t_ray		reflected_ray;
	t_hit_obj 	reflected_hit;
	t_hit_obj 	refracted_hit;
	float		fresnel_ratio;
	int			flag;

	flag = 1;
	fresnel_ratio = fresnel(ref_index, hit.refraction_index, ray.direction, hit.normal, 1.0f - hit.light_absorb_ratio);
	reflected_ray.direction = calc_reflected_ray(ray.direction, hit.normal);
//	vector_rand(&reflected_ray, 0.1f);
	normalize_vector(&reflected_ray.direction);
	reflected_ray.origin = vector_add(hit.hit_point, vector_scale(reflected_ray.direction, 0.01f));

	reflected_hit = reflection(data, ray, hit, depth, light_intensity, fresnel_ratio, reflected_ray, &flag);
	refracted_hit = refraction(data, ray, hit, depth, light_intensity, fresnel_ratio, ref_index);
	reflected_hit.color = blend_colors(reflected_hit.color, refracted_hit.color, fresnel_ratio);
//	reflected_hit.color = refracted_hit.color;
	light_intensity = light_intensity - hit.light_absorb_ratio;
	if (depth > 1 && light_intensity > 0.01f && flag)
		return (reflection_refraction(data, reflected_ray, reflected_hit, depth - 1, light_intensity, 1.0f));
	return (reflected_hit.color);
}
