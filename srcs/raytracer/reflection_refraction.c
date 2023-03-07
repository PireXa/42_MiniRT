/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_refraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vector	calc_reflected_ray(t_vector ray, t_vector normal)
{
	t_vector	reflected_ray;

	reflected_ray = vector_sub(ray, vector_scale(normal,
				2 * dot_product(ray, normal)));
	return (reflected_ray);
}

t_vector	calc_refracted_ray(float n1, float n2, t_vector ray, t_vector n)
{
	float		r;
	float		c1;
	float		c2;
	t_vector	refracted_ray;

	r = n1 / n2;
	c1 = dot_product(n, ray);
	c2 = (float)sqrt(1 - r * r * (1 - c1 * c1));
	refracted_ray = vector_add(vector_scale(ray, r),
			vector_scale(n, r * c1 - c2));
	normalize_vector(&refracted_ray);
	return (refracted_ray);
}

//fresnel = reflectance
//1 - fresnel = transmittance

t_hit_obj	reflection(t_data *data, t_hit_obj h, float *l_int, t_ray rflct_ray)
{
	t_hit_obj	reflected_hit;

	reflected_hit = get_reflect_color(data, rflct_ray, h, l_int);
	reflected_hit.color = blend_colors(reflected_hit.color, h.color, *l_int);
	return (reflected_hit);
}

t_hit_obj	refraction(t_data *data, t_ray ray, t_hit_obj hit, float l_int)
{
	float		beer_lambert;
	t_ray		refracted_ray;
	t_hit_obj	refracted_hit;

	refracted_ray.direction = calc_refracted_ray(1.0f,
			hit.refraction_index, ray.direction, hit.normal);
	refracted_ray.origin = vector_add(hit.hit_point,
			vector_scale(hit.normal, -0.0001f));
	refracted_hit = get_refract_color(data, refracted_ray, hit, &beer_lambert);
	refracted_hit.color = blend_colors(hit.color,
			refracted_hit.color, beer_lambert);
	refracted_hit.color = blend_colors(refracted_hit.color, hit.color, l_int);
	return (refracted_hit);
}

int	reflection_refraction(t_data *data, t_ray ray, t_hit_obj h, t_ref_cap cap)
{
	float		fresnel_ratio;
	t_ray		reflected_ray;
	t_hit_obj	reflected_hit;
	t_hit_obj	refracted_hit;

	fresnel_ratio = fresnel(h.refraction_index, ray.direction,
			h.normal, 1.0f - h.light_absorb_ratio);
	reflected_ray.direction = calc_reflected_ray(ray.direction, h.normal);
	normalize_vector(&reflected_ray.direction);
	reflected_ray.origin = vector_add(h.hit_point,
			vector_scale(h.normal, 0.001f));
	reflected_hit = reflection(data, h, &cap.light_int, reflected_ray);
	refracted_hit = refraction(data, ray, h, cap.light_int);
	reflected_hit.color = blend_colors(reflected_hit.color,
			refracted_hit.color, fresnel_ratio);
	cap.light_int = cap.light_int - h.light_absorb_ratio;
	if (cap.depth > 1 && cap.light_int > 0.001f)
	{
		cap.depth--;
		return (reflection_refraction(data, reflected_ray, reflected_hit, cap));
	}
	return (reflected_hit.color);
}
